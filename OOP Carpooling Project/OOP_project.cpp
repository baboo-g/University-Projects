#include <iostream>
#include <fstream>
// #include <cctype>
#include <cstdlib>
#include <string>

using  namespace std;

class Registeration
{
    protected:
        string f_name, l_name, email;
        char gender;
        long long int cnic;

    public:
        Registeration(string f, string l, string e, char g, int c)
        {
            f_name = f;
            l_name = l;
            email = e;
            gender = g;
            cnic = c;
        }
        Registeration() { }

        void input()
        {
            cout << "Enter the details\n";
            cout << "Enter your first name: ";
            cin >> f_name;
            cout << "Enter your last name: ";
            cin >> l_name;
            cout << "Enter your email: ";
            cin >> email;
            cout << "Enter your Gender (M/F)?: ";
            cin >> gender;
            cout << "Enter your CNIC: ";
            cin >> cnic; 
        }

        void writing_data(string file_name = "Passenger.txt")
        {
            ofstream file;
            
            file.open(file_name, ios :: app);
            if(file.is_open())
            {
            	file << endl;
                file << f_name << " " << l_name << " " << email << " " << gender << " " << cnic;
            }
            else
            {
                cout << "Error! File cannot be opened.";
            }

            file.close();
        }

        int reading_data(string n, string file_name = "Passenger.txt")
        {
            ifstream file;
            char check;

            file.open(file_name, ios :: in);
            if(file.is_open())
            {
                while (file >> f_name >> l_name >> email >> gender >> cnic)
                {
                    if(n == (f_name+ " " +l_name))
                    {
                        cout << "You have successfully logged in!\n";
                        check = 'Y';
                        system("PAUSE");
                    }
                }

                if(check != 'Y')
                {
                    cout << "Error! You have not registered on this app.\n";
                    system("PAUSE");
                }   
            }
            else
            {
                cout << "Error! File cannot be opened.";
            }

            file.close();

            if(check == 'Y')
            {
                return 1;
            }
            else
            {
                return 0;
            }          
        }

        void display()
        {
            cout << "Your name is " << f_name << " " << l_name << ".\n";
            cout << "Your email is " << email << ".\n" << "Your CNIC number is " << cnic << ".\n";
            cout << "You are a " << gender;
        }
};

class Driver : public Registeration
{
    protected:
        string car_name, colour, number_plate, pickup, dropoff, time;

    public:
    	Driver()
    	{
    		
		}
        void input()
        {
            Registeration :: input();
            cout << "Enter your car name: ";
            fflush(stdin);
            getline(cin, car_name);
            cout << "Enter the colour of your car: ";
            fflush(stdin);
            getline(cin, colour);
            cout << "Enter the number plate of the car: ";
            fflush(stdin);
            getline(cin, number_plate);
            cout << "Enter your Pickup point: ";
            fflush(stdin);
            getline(cin, pickup);
            cout << "Enter your dropoff point: ";
            fflush(stdin);
            getline(cin, dropoff);
            cout << "Enter your start time: ";
            fflush(stdin);
            getline(cin, time);
        }

        string get_pickup()
        {
            return pickup;
        }
        string get_dropoff()
        {
            return dropoff;
        }
        string get_time()
        {
            return time;
        }


        void display()
        {
            // Registeration :: display();
            cout << "Your car is " << car_name << ".\n";
        }

        void display_car_details()
        {
            system("CLS");

        	cout << "\nYour driver is found! The Details of the car are as follows: \n";
            cout << "The name of the driver is " << f_name + " " + l_name << ".\n";
            cout << "The car is a " << colour << " " << car_name << ".\n";
            cout << "The number plate of the car is " << number_plate << "\nYour pick up time is " << time << endl;
            system("PAUSE");
        }

        void writing_data(string file_name = "Driver.txt")
        {
            ofstream file;
            
            file.open(file_name, ios :: app);
            if(file.is_open())
            {
            	file << endl;
                file <<  f_name << " " << l_name << " " << email << " " << gender << " " << cnic << " " << car_name << " " << colour << " " << 
                number_plate << " " << pickup << " " << dropoff << " " << time;
            }
            else
            {
                cout << "Error! File cannot be opened.";
            }

            file.close();
        }

        void reading_data(string n, string file_name = "Driver.txt")
        {
            char check = 'N';
            ifstream file;

            file.open(file_name, ios :: in);
            if(file.is_open())
            {
                while (file >> f_name >> l_name >> email >> gender >> cnic >> car_name >> colour >> number_plate >> pickup >> dropoff >> time)
                {
//                	cout << endl << endl << f_name+ " " +l_name << endl;
                    if(n == (f_name+ " " +l_name))
                    {
                        cout << "\nYou have successfully logged in!\n\n";
                        check = 'Y';
                        system("PAUSE");
                    }
                }

                if(check != 'Y')
                {
                    cout << "\nError! You have not registered on this app.\n";
                    system("PAUSE");
                }   
            }
            else
            {
                cout << "Error! File cannot be opened.";
            }

            file.close();
        }
        void searching_driver(string p, string d, string t)
        {          
            ifstream file;
            char check = 'N';

            file.open("Driver.txt", ios :: in);
            if(file.is_open())
            {
                while(file >> f_name >> l_name >> email >> gender >> cnic >> car_name >> colour >> number_plate >> pickup >> dropoff >> time)
                {
                    if(pickup == p && dropoff == d && time == t)
                    {
                        display_car_details();
                        check = 'Y';
                    }                  
                }
                if(check == 'N')
                {
                    cout << "\nWe are sorry. No driver ride is currently avaliable according to your requirements.\nYou can always request a new ride!";
                    system("PAUSE");
                }                
            }
            else
            {
                cout << "Error! Cannot open file.";
            }

            file.close();    
        }
};

class Passenger : public Registeration
{
    private:    
        string pick, drop, time;
    
    public:
    	Passenger()
    	{
    		
		}
        void pickup_info()
        {
            cout << "Enter your pickup location: ";
            cin >> pick;
            cout << "Enter your dropoff location: ";
            cin >> drop;
            cout << "Enter your time: ";
            cin >> time;
        }

        void finding_ride()
        {
            Driver d1;
            
            d1.searching_driver(pick, drop, time);           
        }

        void new_ride()
        {
            Driver d;

            d.searching_driver("Any", "Any", "Any");
        }
};


int main()
{
    int choice, ret;
    char person;
    Driver D;
    Passenger P;
    string name;

    do
    {
    	system("CLS");
        cout << "Welcome to Risek Transportation and Carpooling system\n";
        cout << "1. Login\n2. Signup\n3. Exit\nPlease Select your desired choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
            	system("CLS");
                cout << "Are you a Driver or a Passenger (D/P)?: ";
                cin >> person;

                cout << "Enter your name: ";
                fflush(stdin);
                getline(cin, name);
//                cout << endl << endl << name << endl;

                if(person == 'D')
                {
                    D.reading_data(name);                   
                }
                else
                {
                	ret = P.reading_data(name);
                	
                    if(ret == 1)
                    {
                        system("CLS");
                	    cout << "1. Reserve a ride\n2. Request a ride\nSelect your choice: ";
                	    cin >> choice;
                	
                	    if(choice == 1)
                	    {	
                		    P.pickup_info();
                		    P.finding_ride();
					    }
					    else if(choice == 2)
					    {
                    	    P.pickup_info();
                    	    P.new_ride();
					    } 
                    }
                }
                break;
            }
            case 2:
            {
            	system("CLS");
                cout << "Do you want to register as a driver or Passenget(D/P)?: ";
                cin >> person;

                if(person =='D')
                {
                    D.input();
                    D.writing_data();                    
                }
                else
                {
                    P.input();
                    P.writing_data();
                }
                break;
            }
            case 3:
            {
            	system("CLS");
                cout << "Exiting the program. Thank you for using Risek Services!";
            }
        }
    }while(choice != 3);
    
	return 0;   
}


