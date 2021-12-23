#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

struct stepping
{
	char rotor1;
	char rotor2;
	char rotor3;
};

struct stepping key_generator();
int map_r_to_l(int index_input, struct stepping s1);
int map_l_to_r(int index_refl, struct stepping s1);
int map_refl(int index);
int map_r_to_l_rotor(char start, int input, char wiring[]);
int map_l_to_r_rotor(char start, int input, char wiring[]);
char cipher_char(char input, struct stepping s1);
char Goto_A(char input);
struct stepping step(struct stepping s1);
char plugboard(char input);
void cipher(char message[], struct stepping s1, int size);


int main()
{
	int size, choice, choice1;
	struct stepping s1;
	char message[50], x, fname[50], fname_2[50];
	
	printf("=================== Welcome to the Enigma ==================\n");
	printf("1. Encryption\n2. Decryption\nSelect the operation you want to perform: ");
	scanf("%d", &choice);
	
	switch (choice)
	{
		case 1:
		{
			printf("\nDo you want to encrypt a File? (Y/N): ");
			fflush(stdin);
			choice1 = getchar();
			
			if (choice1 == 'Y' || choice1 == 'y')
			{
				s1 = key_generator();
				
				printf("\nEnter the filname you want to encrypt: ");
				fflush(stdin);
				fgets(fname, 50, stdin);
				fname[strcspn(fname, "\n")] = '\0';
				strcat(fname, ".txt");
				
				printf("\nEnter the filname you want to make: ");
				fflush(stdin);
				fgets(fname_2, 50, stdin);
				fname_2[strcspn(fname_2, "\n")] = '\0';
				strcat(fname_2, ".txt");				
				
				printf("\nYour Key is : %c%c%c", s1.rotor1, s1.rotor2, s1.rotor3);
				
				FILE *fp, *fp1;
	
				fp = fopen(fname, "r");
				if (fp == NULL)
				{
					printf("\nFile unavaliable.");
					exit(0);
				}
				
				fp1 = fopen(fname_2, "w");			
				
				while ( (x = fgetc(fp)) != EOF)
				{
					if(x >= 65 && x <= 90)
					{
						x = toupper(x);
						x = plugboard(x);
						s1 = step(s1);
						x =	cipher_char(x, s1);
						x = plugboard(x);
						putc(x, fp1);
					}
					else
					{
						putc(x, fp1);					
					}
				}
	
				fclose(fp);
				fclose(fp1);
				printf("\nThe file has been successfully encrypted!");
			}
			else
			{
				s1 = key_generator();
				printf("\nYour Key is : %c%c%c", s1.rotor1, s1.rotor2, s1.rotor3);
				printf("\nEnter the message you want to encrypt: ");
				fflush(stdin);
				fgets(message, 50, stdin);
				message[strcspn(message, "\n")] = '\0';
				size = strlen(message);
			
				printf("\nYour Encrypted message is: ");
				cipher(message, s1, size);					
			}
			
			break;
		}
		case 2:
		{
			printf("\nDo you want to Decrypt a File? (Y/N): ");
			fflush(stdin);
			choice1 = getchar();
			
			if (choice1 == 'Y' || choice1 == 'y')
			{
				printf("Enter Your Key: ");
				fflush(stdin);
				scanf("%c%c%c", &s1.rotor1, &s1.rotor2, &s1.rotor3);
				
				printf("\nEnter the filname you want to decrypt: ");
				fflush(stdin);
				fgets(fname, 50, stdin);
				fname[strcspn(fname, "\n")] = '\0';
				strcat(fname, ".txt");

				printf("\nEnter the filname you want to make: ");
				fflush(stdin);
				fgets(fname_2, 50, stdin);
				fname_2[strcspn(fname_2, "\n")] = '\0';
				strcat(fname_2, ".txt");				
				
				FILE *fp, *fp1;
	
				fp = fopen(fname, "r");
				
				if (fp == NULL)
				{
					printf("\nFile unavaliable.");
					exit(0);
				}
				
				fp1 = fopen(fname_2, "w");
				
				while ( (x = fgetc(fp)) != EOF)
				{
					if(x >= 65 && x <= 90)
					{
						x = toupper(x);
						x = plugboard(x);
						s1 = step(s1);
						x =	cipher_char(x, s1);
						x = plugboard(x);
						putc(x, fp1);
					}
					else
					{
						putc(x, fp1);					
					}
				}
	
				fclose(fp);
				fclose(fp1);
				printf("\nThe file has been successfully decrypted!");
			}
			else
			{
				printf("Enter Your Key: ");
				fflush(stdin);
				scanf("%c %c %c", &s1.rotor1, &s1.rotor2, &s1.rotor3);
				printf("\nEnter the message you want to decrypt: ");
				fflush(stdin);
				fgets(message, 50, stdin);
				message[strcspn(message, "\n")] = '\0';
				size = strlen(message);

				printf("\nYour Decrypted message is: ");
				cipher(message, s1, size);				
			}

			break;
		}
	}
	
	return 0;
}

struct stepping key_generator()
{
	struct stepping s1;
	int i, j;
	char key_gen[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", arr[3], turnover[2];
	
	srand(time(NULL));
	
	for(i=0; i<3; i++)
	{
		j = rand()%(26-0) + 0;
		arr[i] = key_gen[j];
	}		
	
	s1.rotor1 = arr[0]; s1.rotor2 = arr[1], s1.rotor3 = arr[2];

	return s1;
}

int map_r_to_l(int index_input, struct stepping s1)
{
	char wiring1[26] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
	char wiring2[26] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	char wiring3[26] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
	
	int pass_3 = map_r_to_l_rotor(s1.rotor3, index_input, wiring3);
	int pass_2 = map_r_to_l_rotor(s1.rotor2, pass_3, wiring2);
	int pass_1 = map_r_to_l_rotor(s1.rotor1, pass_2, wiring1);
	
	return pass_1;
}

int map_l_to_r(int index_refl, struct stepping s1)
{
	char wiring1[26] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
	char wiring2[26] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	char wiring3[26] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
	
	int pass_1 = map_l_to_r_rotor(s1.rotor1, index_refl, wiring1);	
	int pass_2 = map_l_to_r_rotor(s1.rotor2, pass_1, wiring2);		
	int pass_3 = map_l_to_r_rotor(s1.rotor3, pass_2, wiring3);	
	
	return pass_3;
}	

int map_r_to_l_rotor(char start, int input, char wiring[])
{
	char rotor1[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	int i, index, offset, j, encryp1;
	char equal;
	for(i=0; i<26; i++)
	{
		if(start == rotor1[i])
		{
			offset = i;
			break;
		}
	}

	j = input + offset;
	if (j > 25)
	{
		j -= 26;
	}
	equal = wiring[j];	
	
	for(i=0; i<26; i++)
	{
		if(equal == rotor1[i])
		{
			encryp1 = i-offset;
			if (encryp1 < 0)
			{
				encryp1 += 26;
			}
			break;
		}
	}	
	return encryp1;
}

int map_l_to_r_rotor(char start, int input, char wiring[])
{
	char rotor1[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	int i, index, offset, j, encryp1;
	char equal;
	for(i=0; i<26; i++)
	{
		if(start == rotor1[i])
		{
			offset = i;
			break;
		}
	}

	j = input + offset;
	if (j > 25)
	{
		j -= 26;
	}
	equal = rotor1[j];	
	
	for(i=0; i<26; i++)
	{
		if(equal == wiring[i])
		{

			encryp1 = i-offset;
			if (encryp1 < 0)
			{
				encryp1 += 26;
			}
			break;
		}
	}
	return encryp1;	
}	

int map_refl(int index)
{
	char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char reflector[26] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
	char encryp;
	int i;
	
	char reflection = reflector[index];
	for(i=0; i<26; i++)
	{
		if (reflection == alphabets[i])
		{
			index = i;
			break;
		}	
	}

	return index;		
}
	
char cipher_char(char input, struct stepping s1)	
{
	char alphabets[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char encryp;
	int i, current_entry, encrypted;
	
	for(i=0; i<26; i++)
	{
		if (input == alphabets[i])
		{
			current_entry = i;
			break;
		}	
	}
	
	encrypted = map_r_to_l(current_entry, s1);
	encrypted = map_refl(encrypted);
	encrypted = map_l_to_r(encrypted, s1);
	
	for(i=0; i<26; i++)
	{
		if(encrypted == i)
		{
			encryp = alphabets[i];
			break;
		}
	}
	
	return encryp;
}

char Goto_A(char input)
{

	if (input == 91)
	{
		input = 'A';
	}
	
	return input;
}

struct stepping step(struct stepping s1)
{

	char turnover2 = 'E', turnover3 = 'V';
	
	if (s1.rotor3 == turnover3 && s1.rotor2 == turnover2)
	{
		s1.rotor1++;
		s1.rotor2++;
		s1.rotor3++;
		s1.rotor1 = Goto_A(s1.rotor1); s1.rotor2 = Goto_A(s1.rotor2); s1.rotor3 = Goto_A(s1.rotor3);
	}
	else if (s1.rotor3 == turnover3 || s1.rotor2 == turnover2)
	{
		if (s1.rotor3 == turnover3)
		{
			s1.rotor3++;
			s1.rotor2++;
			s1.rotor3 = Goto_A(s1.rotor3); s1.rotor2 = Goto_A(s1.rotor2);
		}
		else
		{
			s1.rotor1++;
			s1.rotor2++;
			s1.rotor3++;
			s1.rotor1 = Goto_A(s1.rotor1); s1.rotor2 = Goto_A(s1.rotor2); s1.rotor3 = Goto_A(s1.rotor3);
		}
	}
	else
	{
		s1.rotor3++;
		s1.rotor3 = Goto_A(s1.rotor3);
	}
	
	return s1;		
}

char plugboard(char input)
{
	char swap[13][2] = {'A','Q','B','E','C','R','D','H','F','M','L','Z','U','J','K','X','P','S','O','G','W','I','N','Y','T','V'};
	int i, j;
	
	for(i=0; i<13; i++)
	{
		for (j=0; j<2; j++)
		{

			if (input == swap[i][j])
			{
				if (j==0)
				{
					input = swap[i][1];
				}
				else
				{
					input = swap[i][0];
				}
				break;
			}
		}
	}

	return input;
}
	
void cipher(char message[], struct stepping s1, int size)
{
	int i;
	char c;
	
	for (i=0; i<size; i++)
	{
		c = message[i];
		c = toupper(c);
		c = plugboard(c);
		s1 = step(s1);
		c =	cipher_char(c, s1);
		c = plugboard(c);
		printf("%c", c);		
	}	
}


	
	
	
	
	
	

