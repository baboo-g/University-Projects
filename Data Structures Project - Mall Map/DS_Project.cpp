#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <fstream>
#include <string>
#include <set>
#include <utility>

using namespace std;

class Edge
{
    public:
        int Destination_Vertex_id;
        string Destination_Vertex_name;
        int weight;

        Edge()
        {

        }
        
        Edge(int i, int w, string n)
        {
            Destination_Vertex_name = n;
            Destination_Vertex_id = i;
            weight = w;
        }
};


class Vertex
{
    public:
        int shop_id;
        string shop_name;
        list <Edge> Edgelist;

        Vertex()
        {

        }

        Vertex(int i, string s)
        {
            shop_id = i;
            shop_name = s;
        }

        void input_data()
        {
            cout << "Enter a unique Shop ID: ";
            cin >> shop_id;
            fflush(stdin);
            cout << "Enter your shop name: ";
            getline(cin, shop_name);
        }

        void print_edge_list()
        {
            Vertex v;
            cout << "[";

            for(auto i=Edgelist.begin(); i != Edgelist.end(); i++)
            {
                
                cout << i->Destination_Vertex_id << ". " << i->Destination_Vertex_name << "(" << i->weight << " "  << ") -->";
            }
            cout << "]\n";
        }
};


class Graph
{
    public:
        vector <Vertex> vertices;

        bool vertex_exists(int id, string &s)
        {
            for(int i=0; i<vertices.size(); i++)
            {
                if(vertices.at(i).shop_id == id)
                {
                    s = vertices.at(i).shop_name;
                    return true;
                }
            }
            return false;
        }

        Vertex get_vertex(int id)
        {
            Vertex v;
            for(auto i = 0; i < vertices.size(); i++)
            {
                if(vertices.at(i).shop_id == id)
                {
                    return vertices.at(i);
                }
            }
            return v;
        }

        bool edge_exists(int id1, int id2)
        {
            Vertex v = get_vertex(id1);

            for(auto i=v.Edgelist.begin(); i != v.Edgelist.end(); i++)
            {
                if(i->Destination_Vertex_id == id2)
                {
                    return true;
                }
            }
            return false;
        }

        void Add_Vertex(Vertex new_vertex)
        {
            string str;
            if(vertex_exists(new_vertex.shop_id, str))
            {
                cout << "Error! Shop Already exists.\n";
            }
            else
            {
                vertices.push_back(new_vertex);
                cout << "\nNew Shop added successfully.\n";
            }
        }

        void Add_Edge()
        {
            int source, destination, dist;
            string s_name, d_name;

            cout << "Enter the source shop ID: ";
            cin >> source;
            cout << "Enter Destination shop ID: ";
            cin >> destination;
            cout << "Enter Distance: ";
            cin >> dist;

            if(vertex_exists(source, s_name) && vertex_exists(destination, d_name))
            {
                if(edge_exists(source, destination))
                {
                    cout << "Error! Edge already exists.\n";
                }
                else
                {
                    for(int i=0; i<vertices.size(); i++)
                    {
                        if(vertices.at(i).shop_id == source)
                        {
                            Edge e(destination, dist, d_name);
                            vertices.at(i).Edgelist.push_back(e);
                        }
                        else if(vertices.at(i).shop_id == destination)
                        {
                            Edge e(source, dist, s_name);
                            vertices.at(i).Edgelist.push_back(e);
                        }
                    }

                    cout << "\nEdge added Successfully.\n";
                }
            }
        }

        void storegraphinfo()
        {
            ofstream graph_obj; int count=1;
            graph_obj.open("Mall.dat", ios :: out|ios :: binary);
            
            for(int i=0; i<vertices.size(); i++)
            {
                count=1;
                graph_obj << vertices.at(i).shop_id << " " << vertices.at(i).shop_name << " ";
                for(auto j=vertices.at(i).Edgelist.begin(); j != vertices.at(i).Edgelist.end(); j++)
                {
                    graph_obj << j->Destination_Vertex_id << " " << j->weight << " " << j->Destination_Vertex_name << " ";
                    
                    if(count != vertices.at(i).Edgelist.size())
                    {   
                        graph_obj << "e ";
                    }
                    count++;
                }
                graph_obj << "end" << endl;
            }
            graph_obj.close();
        }

        void readgraphinfo()
        {
            ifstream Graph_obj; int count=0;
            Edge e; string check, name;; Vertex V;
            Graph_obj.open("Mall.dat", ios :: in|ios :: binary);
            
            if(!Graph_obj)
            {
                cout << "Error! Unable to open file.\n";
            }
            else
            {
                while(Graph_obj >> V.shop_id >> V.shop_name)
                {                  
                    while(Graph_obj >> e.Destination_Vertex_id >> e.weight >> e.Destination_Vertex_name >> check)
                    {
                        V.Edgelist.push_back(e);
                        if(check == "end")
                        {
                            break;
                        }
                    }
                    vertices.push_back(V);
                    V.Edgelist.clear();
                }
            }
            Graph_obj.close();
        }

			void printPath(int currentVertex, vector<int> parents)
			{
    			if (currentVertex == -1) 
				{
        			return;
    			}
    			
				printPath(parents[currentVertex], parents);
    			cout << currentVertex << " ";
			}

			void printsoln(int start, vector<int> distance, vector<int> parents)
			{
			    int nVertices = distance.size();
    			cout << "Vertex\t\t Distance\tPath";
 
    			for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) 
				{
        			if (vertexIndex != start) 
					{
            			cout << "\n" << start << " -> ";
            			cout << vertexIndex << " \t\t ";
            			cout << distance[vertexIndex] << "\t\t";
            			printPath(vertexIndex, parents);
        			}
    			}
			}

        void dijkstras(int start_id)
        {
            vector<int> distance(vertices.size());
            vector<bool> added(vertices.size());
            vector<int> parents(vertices.size());
            
            
            for(int i=0; i<vertices.size(); i++)
            {
                distance[i] = INT_MAX;
                added[i] = false;
            }

            distance[start_id] = 0;
            parents[start_id] = -1;
            
            
            for(int i=1; i<vertices.size(); i++)
            {
            	int nearest_vertex = -1;
            	int shortestdistance = INT_MAX;
            	
            	for(int index=0; index < vertices.size(); index++)
            	{
            		if(!added[index] && distance[index] < shortestdistance)
            		{
            			nearest_vertex = index;
            			shortestdistance = distance[index];
					}
				}
				
				added[nearest_vertex] = true;
				
				for(auto neighbours = vertices.at(nearest_vertex).Edgelist.begin(); neighbours != vertices.at(nearest_vertex).Edgelist.end(); neighbours++)
				{
					int edge_dist = neighbours->weight;
					
					if(edge_dist > 0 && ((shortestdistance + edge_dist) < distance[neighbours->Destination_Vertex_id]))
					{
						parents[neighbours->Destination_Vertex_id] = nearest_vertex;
						distance[neighbours->Destination_Vertex_id] = shortestdistance + edge_dist;	
					}
				}	
			}
        printsoln(start_id, distance, parents);	
    }

        void print_graph()
        {
            for(int i=0; i<vertices.size(); i++)
            {
                cout << vertices.at(i).shop_id << ". " << vertices.at(i).shop_name << " --> ";
                vertices.at(i).print_edge_list();
            }
        }
};

int options()
{
    int choice;

    cout << "1. Enter a new shop.\n2. Enter a link between two shops.\n3. Find the shortest distance between two shops.\n";
    cout << "4. Print the layout of Mall.\n5. Exit the Program\nEnter your choice: ";
    cin >> choice;

    return choice;
}

int main()
{   
    bool check = 1;
    int choice;
    Graph G1; Vertex V1;

    G1.readgraphinfo();
    
    do
    {
        system("CLS");
        choice = options();

        switch(choice)
        {
            case 1:
            {
                V1.input_data();
                G1.Add_Vertex(V1);
                system("PAUSE");
                break;
            }
            case 2:
            {
                G1.Add_Edge();
                system("PAUSE");
                break;
            }
            case 3:
            {
                G1.dijkstras(0);
                cout << endl;
                system("PAUSE");
                break;
            }
            case 4:
            {
                G1.print_graph();
                system("PAUSE");
                break;
            }
            case 5:
            {
                check = 0;
                break;
            }
        }
    }while(check != 0);

    G1.storegraphinfo();

    return 0;
}