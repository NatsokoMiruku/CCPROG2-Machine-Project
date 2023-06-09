#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
#include <time.h>

/*
Description: a 2d board game, Scrabble, placing letters on the board to complete a word
Programmed by: Angela Dominique C. Miguel S15
Last modified: 12/5/2022
Version: <version number>
[Acknowledgements: Stackoverflow for bugs and errors, ccprog files, previous own mp]
*/


typedef char String[10];

struct PlayerStatTag
{
	String longword;
	int highscore;
	int gameplay;
	int ave;
	int totalpoints;
};

struct PlayerTag
{
	String name;
	int points;
	char tiles[8];
	struct PlayerStatTag playerstat;
};


struct CoordinateTag
{
	int x;
	int y;
};

typedef struct CoordinateTag Cords;
typedef struct PlayerTag PlayerData;

PlayerData player1;
PlayerData player2;
PlayerData player3;
PlayerData player4;

//to clear screen 
void Pause(void)
{
    int c;
    do
    {
        c = getchar();
    } while((c != '\n') && (c != EOF));
}


/*
This function select which one they want to do 
@return the result of the choice
*/
int MainMenu()
{
	int choice;
	
	printf("Scrabble:\n");
	printf("[1]Start\n");
	printf("[2]Exit\n");
	scanf("%d", &choice);
	
		while(choice < 1 || choice > 2)
			{
				printf("Please Enter Correct Choice\n");
				scanf("%d", &choice);
			}

	return choice;	
}



/*
This function selects on how many players they want to play
@return the result of the player
*/
int SelectPlayer()
{
	int player;
	
	printf("Select Number of Players:\n");
	printf("[1]2 Players\n");
	printf("[2]3 Players\n");
	printf("[3]4 Players\n");
	scanf("%d", &player);
	
		while(player < 1 || player > 3)
		{
			printf("Please Enter Correct Choice\n");
			scanf("%d", &player);
		}

	return player;	
	
}




/*
This function Displays the 11x11 board
@param board 2d array to put characters in
*/
void Display_Board(char board[][11]) 
{									
  int i;
  int j;
  int k;
  
        for(i=0; i<11; i++) 
        printf("----");
        printf("---\n");
        for(i=0; i<11; i++)
        {	
        	if(i+1 > 9)
        	{
        		printf("%d", i+1);
			}
        	else 
        	{
        		printf(" %d", i+1);	
			}
        	
        	
	            for(j=0; j<11; j++)
	            {
	            	printf("| %c ", board[i][j]);
	            }
	            
		            printf("|\n");
		            for(k=0; k<11; k++) 
		            printf("----");
		            printf("---\n");
        }
      }



/*
This function Displays players' tiles
@param tiles array to put random characters for the player
*/
void Display_Tiles(char tiles[7])
{
	printf("     TILES: | %c | %c | %c | %c | %c | %c | %c | \n", tiles[1], tiles[2], tiles[3], tiles[4], tiles[5], tiles[6], tiles[7]);
	printf("\n");			
}


/*
This function Displays the players' name and points 
@param name the name of the player 
@param points the points of the player
*/
void Display_Player(int points, char* name)
{
	printf("Player name: %s\n", name);
	printf("Points: %d\n", points);	
}


/*
This function Randomizes numbers from 0 - 27
@return the result of the random number generator
*/
int Randomizer()
{
	
	int RndTiles;
    RndTiles = 0 + rand()%27;
    return RndTiles;	
}


/*
This function Gets randomized tiles and displays it Display_Tiles function
@param letters the initialized array with the alphabet
@param amount the initialized array of amount of each letter of the alphabet
@param tiles array to put random characters for the player
*/
void StartTiles(char tiles[], char letters[], int amount[])
{
	int i = 1;
	int k;
			
	
		while(i != 8)
		{	
			k = Randomizer();
		
				if(amount[k] > 0)
				{
				    tiles[i] = letters[k];
				    amount[k]--;
				}
				else
				{
				    while(amount[k] < 1)
					{
				        k = Randomizer();
			        	if(amount[k] != 0)
			            {
				            tiles[i] = letters[k];
				            amount[k]--;
				        }
				    }
				}
			
			i++;
		}		
		
		
	/*	tiles[1] = 'C';
		tiles[2] = '\0';
		tiles[3] = 'T';
		tiles[4] = 'A';
		tiles[5] = '\0';
		tiles[6] = 'E';*/
		
		
		
}

/*
This function Restocks the blank tiles of the player after they end their turn
@param letters the initialized array with the alphabet
@param amount the initialized array of amount of each letter of the alphabet
@param tiles array to put random characters for the player
*/
void Restock_Tiles(char tiles[], char letters[], int amount[])
{
	int i = 1;
	int k;
			
	
		while(i != 8)
		{	
			if(tiles[i] == ' ') 
			{
				
				k = Randomizer();
		
				if(amount[k] > 0)
				{
				    tiles[i] = letters[k];
				    amount[k]--;
				}
				else
				{
				    while(amount[k] < 1)
					{
				        k = Randomizer();
				        if(amount[k] != 0)
				        {
				            tiles[i] = letters[k];
				            amount[k]--;
				        }
				    }
				}
				
				i++;
			}
			
			else
			{
				i++;
			}
		}		
	
}

/*
This function is for players to place their tile on the coordinate of the board
@param Coordinate is an array for storing the coordinate data to be used in Valid_Word function
@param placecount is to move the element of Coordinate for each coordinate data
*/
void Place_Tiles(char tiles[], char board[][11], Cords Coordinate[], int placecount)
{
	int a;
	int c = 0;
	int d = 0;
	char input;
	
    printf("Select Tile: ");			
    scanf("%d", &a);
		  
	  	while (a < 1 || a > 7|| tiles[a] == ' ')
	    {
	    	printf("no tile\n");
	    	scanf("%d", &a);
		}
		
	  		if(tiles[a] == '\0')
	  		{
	  			printf("Enter letter you want for the blank tile:\n");
				scanf("%c", &input);
				
	  			while (input < 'A' || a > 'Z')
	    		{
			    	printf("Please enter capital.\n");
			    	scanf("%c", &input);	
				}
				
				tiles[a] = input;
			}
			
			
		        printf("Enter Where to Put Tile (X , Y Coordinate): ");			
		        scanf("%d%d", &c,&d);
		
		        c--;
		        d--;
		        	
		        	while ((c < 0 || c > 11) || (d < 0 || d > 11))
			        {
			        	printf("out of board\n");
			        	printf("Enter Where to Put Tile (X , Y Coordinate): ");	
			        	scanf("%d%d", &c,&d);
					}
			
			        while (board[c][d] != ' ')
			        {
			        	printf("there is a tile\n");
			        	printf("Enter Where to Put Tile (X , Y Coordinate): ");	
			        	scanf("%d%d", &c,&d);
					}
			
				
					board[c][d] = tiles[a];
					tiles[a] = ' ';		
					Coordinate[placecount].x = c;
			    	Coordinate[placecount].y = d;
			    	
			    	printf("Place: %d", placecount);
			    	Pause();Pause();	    
}

/*
This function is for players to place their tile on the CENTER of the board
@param Coordinate is an array for storing the coordinate data to be used in Valid_Word function
@param placecount is to move the element of Coordinate for each coordinate data
*/
void Place_Center(char tiles[], char board[][11], Cords Coordinate[], int placecount)
{
	int a;
	int c = 6;
	int d = 6;
	char input;
		
	printf("Select Tile to place in the center of the board: ");			
    scanf("%d", &a);
    		
    		
    	while (a < 1 || a > 7|| tiles[a] == ' ')
	    {
	    	printf("no tile\n");
	    	scanf("%d", &a);
		}
		
    		if(tiles[a] == '\0')
	  		{
	  			printf("Enter letter you want for the blank tile:\n");
				scanf("%c", &input);
				
	  			while (input < 'A' || a > 'Z')
	    		{
			    	printf("Please enter capital.\n");
			    	scanf("%c", &input);
				}
				
				tiles[a] = input;
			}
			
    			c--;
		        d--;
		  
				board[c][d] = tiles[a];
				tiles[a] = ' ';		
				Coordinate[placecount].x = c;
		    	Coordinate[placecount].y = d;
		    	
		    	printf("Place: %d", placecount);
		    	Pause();Pause();	    
}


/*
This function is for players to replace their existing tiles or blank tile for a random letter one
@param isReplaced is an array to check if the element of the array tile is already been replaced otherwise its not going to replace anymore 
*/
 void Replace_Tiles(char tiles[], char letters[], int amount[], int isReplaced[])
{
	int j;
	int a;
	int k;
	
		
	printf("Select Tile to Replace : ");			
    scanf("%d", &a);
    
	   		
		while (a < 1 || a > 7)
	    {
	    	printf("no tile\n");
	    	scanf("%d", &a);
		}
		
		k = Randomizer();
	
		if(isReplaced[a] != 1)
		{
				
			for(j = 0; j < 26; j++)
			{
				if(tiles[a] == letters[j] && tiles[a] != ' ')
				{
					amount[j] = amount[j] + 1;
				}
			}
			
		
				if(amount[k] > 0)
				{
				    tiles[a] = letters[k];
				    amount[k]--;
				}
				else
				{
				    while(amount[k] < 1)
					{
				        k = Randomizer();
				        if(amount[k] != 0)
				        {
				            tiles[a] = letters[k];
				            amount[k]--;
				        }
				    }
				}
				
				isReplaced[a] = 1;	
		}
		else
		{
			printf("You already replaced that slot.");
			Pause();Pause();
		}
			
	}
		

/*
This function select which one they want to do on their turn
@return the result of the turn
*/
int Turn()
{
	int turn;
	
	printf("Choose Turn:\n");
	printf("[1]Place Tile\n");
	printf("[2]Replace Tile\n");
	printf("[3]Exit\n");
	scanf("%d", &turn);
		
		
		while(turn < 1 || turn > 3)
		{
			printf("Please Enter Correct Choice\n");
			scanf("%d", &turn);
		}
		
	return turn;	
	
}

/*
This function scans the words.txt file and puts all of the words in a string array
@param wordlist contains all of the words in the file
*/
void Word_List(String wordlist[])
{
	FILE *dictionary;
	int i = 0;
	
	dictionary = fopen("words.txt", "r");
	
		if((dictionary = fopen("words.txt", "r")) == NULL)
		{	
			printf("Error: Dictionary file not found.\n");
		}
		
		else if(!((dictionary = fopen("words.txt", "r")) == NULL))
		{	
			while(!feof(dictionary) && i != 100)
			{
				fscanf(dictionary, "%s", wordlist[i]);
				i++;
			}
		}
	
	fclose(dictionary);
}


/*
This function checks if the player placed a correct word in the board
@param wordlist contains all of the words in the file
@param yes is adds + 1 if its a valid word on the board
@param word is to collect the character input of the player into a word
@param point is initialized array of numbers equal to the element of the letters array
*/
void Valid_Word(String wordlist[], char tiles[], char board[][11], Cords Coordinate[], char word[], int point[], int* points, char letters[], int* yes, int* playerhigh, PlayerData player)
{
	int j = 0;
	int compare = -1;
	int valid = 1;	
	int i = 0;
	int same = 0;
	char temp;
	int k = 0;
	int h = 0;
	int l = 0;
	int m = 1;
	char letr;
	int temppoint;
	
		printf("%s\n", wordlist[0]);
				Pause();Pause();
	
	
	if(Coordinate[0].x != -1 || Coordinate[0].y != -1)
	{
		    while(Coordinate[i].x != -1 || Coordinate[i].y != -1)
			{	
					if(Coordinate[0].x == Coordinate[i].x)
					{
						same = 1;
					}
					else if(Coordinate[0].y == Coordinate[i].y)
					{
						same = 2;
					}
					else
					{
						same = 0;
						valid = 0;
					}
				
				i++;
			}
	}

	if(same == 1)
	{
			while(j < 12)
			{
				temp = board[Coordinate[0].x][j];
					if(temp == 32 || temp == 0)
					{
						j++;
					}
					else
					{
						strncat(word, &temp, 1);	
						j++;
					}
			}
				printf("%s\n", wordlist[0]);
				Pause();Pause();
		
			while(k < 100 && compare != 0 && valid)	
			{
				compare = strcmp(wordlist[k], word);
					if(strlen(wordlist[k]) == 0)
					{
						valid = 0;
					}
				k++;
			}
	}
	
	
	else if (same == 2)
	{
			while(j < 12)
			{
				temp = board[j][Coordinate[0].y];
					if(temp == 32 || temp == 0)
					{
						j++;
					}
					else
					{
						strncat(word, &temp, 1);	
						j++;
					}
			}
			
			while(compare != 0 && valid)	
			{
				compare = strcmp(wordlist[k], word);
					if(strlen(wordlist[k]) == 0)
					{
						valid = 0;
					}
				k++;
			}
	}
	

	
	if(valid == 1 && same != 0)
	{
		printf("Valid word\n");
			for(h = 0; h < 26; h++)
			{
				for(l = 0; l < 8 ; l++)
				{	
					if(word[l] == letters[h] && word[l] != ' ')
					{
						temppoint = point[h];
						*points = point[h] + temppoint;
						if(temppoint > *playerhigh)
						{
							*playerhigh = temppoint;
						}
						printf("point: %d\n", *points);
					}
				}
			}
			
			if(strlen(player.playerstat.longword) < strlen(word))
			{ 
				strcpy(player.playerstat.longword, word);
			}
  

		*yes = *yes + 1;
	}
	
	else 
	{
		printf("not a valid word\n");	
	
			for(i=0; i<11; i++)
	        {	
	            for(j=0; j<11; j++)
	            {
	            	if(board[j][i] != ' ')
	        		{
	        			while(m < 7)
	        			{
		        			if(tiles[m] == ' ')
		        			{
			        			letr = board[j][i];
			        			tiles[m] = letr;
			     				board[j][i] = ' ';	
			     				m++;
							}
							else
							{
								m++;	
							}
						}
					}
					else
					{
						m = 1;
					}
					
	            }
            }
	}
}

//Notes:
//can't: error check same coordinate words
//point system record da stats
//scan file if player name is the same
// if same update if greater stats at the end of game
//longest word check
// games playes = +1 is=f same player
//keep track of sum of total points of player
//to get average divide by number of games played


/*
This function resets the coordinate data from the player into -1 so that it doesnt go garbage value
@param wordlist contains all of the words in the file
*/
void Reset_Placecount(Cords Coordinate[])
{
	int i = 0;
	for(i = 0; i < 9; i++)
	{
		Coordinate[i].x = -1;
		Coordinate[i].y = -1;
	}
}

/*
This function For ending a turn, value of isReplaced with all go back to zero for the next player, Points for player is placed if the word is valid, restock the tiles for the first player
*/
void EndTurn(int isReplaced[], char tiles[], char letters[], int amount[], Cords Coordinate[], String wordlist[], char board[][11], char word[], int point[], int* points, int* yes, int* playerhigh, PlayerData player)
{
	int i;
	
		for(i = 1; i < 8; i++)
	    {
	        isReplaced[i] = 0;
	    }
    		printf("end turn: %s\n", wordlist[0]);
			Pause();Pause();
    
	  	Valid_Word(wordlist, tiles, board, Coordinate, word, point, points, letters, yes, playerhigh, player);
	  	Reset_Placecount(Coordinate);
	  	Restock_Tiles(tiles, letters, amount);
	  	strcpy(word, "");
	  

}


/*
This function is for a player, chooses if they want to place a tile or replace a tile or exit te game,, they can only choose one 
*/
void PlayerScreen(char tiles[], char board[][11], char letters[], int amount[], int isReplaced[], int points, char* name, int* exit, Cords Coordinate[], int *placecount)
{
	int turn;
	int end = 1;

		
				system("cls");    
				Display_Board(board); 
				printf("\n");	
				Display_Tiles(tiles);
				Display_Player(points, name);
				turn = Turn();
				
				switch(turn)
				{
					case 1:
						while(end != 0)
						{
							
							Place_Tiles(tiles, board, Coordinate, *placecount);
							system("cls");    
							Display_Board(board); 
							printf("\n");	
							Display_Tiles(tiles);
							Display_Player(points, name);
							
							printf("[0]End Turn\n");
							printf("[1]Place\n");
							scanf("%d", &end);
							
								if(end == 1)
								{
									*placecount = *placecount + 1;
								}
								else
								{
									*placecount = 0;
								}
						}
						
					break;
					
					case 2:
						while(end != 0)
						{
							Replace_Tiles(tiles, letters, amount, isReplaced);
							system("cls");    
							Display_Board(board); 
							printf("\n");	
							Display_Tiles(tiles);
							Display_Player(points, name);
							printf("[0]End Turn\n");
							printf("[1]Replace\n");
							scanf("%d", &end);
						}
					break;
					
					case 3:
						*exit = 1;
					break;
				}
				
}

/*
This function is for a player, chooses if they want to place a tile or replace a tile or exit te game,, they can only choose one but the difference is 
the Place_center is here fro the first player
*/
void PlayerScreenFirst(char tiles[], char board[][11], char letters[], int amount[], int isReplaced[], int points, char* name, int* exit, Cords Coordinate[], int* placecount)
{
	int turn;
	int end = 1;
		
				system("cls");    
				Display_Board(board); 
				printf("\n");	
				Display_Tiles(tiles);
				Display_Player(points, name);
				turn = Turn();
				switch(turn)
				{
					case 1:
						if(end != 0)
						{
							Place_Center(tiles, board, Coordinate, *placecount);
							system("cls");    
							Display_Board(board); 
							printf("\n");	
							Display_Tiles(tiles);
							Display_Player(points, name);
							
							printf("[0]End Turn\n");
							printf("[1]Place\n");
							scanf("%d", &end);
							
								if(end == 1)
								{
									*placecount = *placecount + 1;
								}
								else
								{
									*placecount = 0;
								}
							
						}
					
							while(end != 0)
							{
								Place_Tiles(tiles, board, Coordinate, *placecount);
								system("cls");    
								Display_Board(board); 
								printf("\n");	
								Display_Tiles(tiles);
								Display_Player(points, name);
								
								printf("[0]End Turn\n");
								printf("[1]Place\n");
								scanf("%d", &end);
								
									if(end == 1)
									{
										*placecount = *placecount + 1;
									}
									else
									{
										*placecount = 0;
									}
							}
						
					break;
					
					case 2:
						while(end != 0)
						{
							Replace_Tiles(tiles, letters, amount, isReplaced);
							system("cls");    
							Display_Board(board); 
							printf("\n");	
							Display_Tiles(tiles);
							Display_Player(points, name);
							printf("[0]End Turn\n");
							printf("[1]Replace\n");
							scanf("%d", &end);
						}
					break;
					
					case 3:
						*exit = 1;
					break;
				}
				
		}
		

/*
This function scans if the player struct has the same record in the file struct 
the Place_center is here fro the first player
*/
void RecordStats(PlayerData* player, PlayerData Stats)
{
    if(strlen((*player).playerstat.longword) < strlen(Stats.playerstat.longword))
    {
        strcpy((*player).playerstat.longword, Stats.playerstat.longword);
    }
    if((*player).playerstat.highscore < Stats.playerstat.highscore)
    {
        (*player).playerstat.highscore = Stats.playerstat.highscore;
    }
    (*player).playerstat.gameplay++;
    (*player).playerstat.totalpoints += (*player).points;
    (*player).playerstat.ave = (*player).playerstat.totalpoints / (*player).playerstat.gameplay;
}

		

//the main is where the turns are switching from player1 to player2, loops until the condition is satisfied
int main() 
{
int exit = 0;
int start_choice;	
int select;
String wordlist[100];
Cords Coordinate[9];
int placecount = 0;
char word[7];
int yes = 11;
int again = 1;
PlayerData Data[10];
PlayerData Temp;
int i = 0;
int player1played = 0;
int player2played = 0;
int player3played = 0;
int player4played = 0;
int player1found = 0;
int player2found = 0;
int player3found = 0;
int player4found = 0;




//Set of the letters in the alphabet 
char letters[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

//The amount of tiles each letter has 
//int amount[27] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1, 2};

//Where the player tile/letter will display
char tiles[8] = {'\0', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

//To check if the tile has already been replaced (function: Replace Tiles);
int isReplaced[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//Where the tiles and words will display
char board[11][11] = {{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},		
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
FILE *data;

	data = fopen("record.dat", "rb+");
		if(fopen("record.dat", "rb+") == NULL)
		{
			data = fopen("record.dat", "wb+");
		}
		         
    srand(time(NULL));
      
	start_choice = MainMenu();
	
		if (start_choice != 2)
		{        
			
			do
			{  	
			
			fseek(data, 0, SEEK_SET);// At the start of the loop, it will always check for the data that is stored in the "STATS.dat" file for the data of the people
			for(i = 0; i <= 10; i++)//	Who have already played, and assign it to the rankings that will be used for the statistics.
			{
				size_t result = fread(&Data[i], sizeof(PlayerData), 1, data);
				if(result == 0)
				{
					i = 10;
				}
			}
			
				exit = 0;  
				system("cls"); 
				select = SelectPlayer();
				Word_List(wordlist);
		
				printf("993: %s\n", wordlist[0]);
				Pause();Pause();
				
				system("cls");    
				Display_Board(board); 
				printf("\n");	
				Display_Tiles(tiles);
				
				
				switch(select)
				{
					case 1:
						
						printf("1006: %s\n", wordlist[0]);
						printf("Input Player Name: \n");
						printf("Player 1: \n");
						scanf("%9s", player1.name);
						printf("Player 2: \n");
						scanf("%9s", player2.name);
					
							printf("1014: %s\n", wordlist[0]);
							Pause();Pause();
							Reset_Placecount(Coordinate);	
							printf("180: %s\n", wordlist[0]);
								Pause();Pause();
							StartTiles(player1.tiles, letters, amount);
							StartTiles(player2.tiles, letters, amount);		
							
								PlayerScreenFirst(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								
								Pause();Pause();
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);      
								Pause();Pause();
								
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
							
							while((player1.points  != 88 || player2.points  != 88) && exit != 1 && yes != 12)
							{
								PlayerScreen(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);
								Pause();Pause();
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
							}
							
							
						
							if(player1.points > player2.points)
							{
								printf("%s Wins !\n", player1.name);
							}
							else if(player1.points < player2.points)
							{
								printf("%s Wins !\n", player2.name);
							}
							else
							{
								printf("Tie !\n");
							}
							
								printf("Play Again?\n");
								printf("[1]Yes\n");
								printf("[2]No\n");
								scanf("%d", &again);
								
									if(again == 2)
									{
										again = 0;
										exit = 1;
										
									}
									else
									{	
									}			
				
					break;
					
					
					case 2:
						
						printf("Input Player Name: \n");
						printf("Player 1: \n");
						scanf("%s", player1.name);
						printf("Player 2: \n");
						scanf("%s", player2.name);
						printf("Player 3: \n");
						scanf("%s", player3.name);
							
							Reset_Placecount(Coordinate);	
							StartTiles(player1.tiles, letters, amount);
							StartTiles(player2.tiles, letters, amount);	
							StartTiles(player3.tiles, letters, amount);	
							
							
							
								PlayerScreenFirst(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);
								Pause();Pause();
							
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
								
									if(exit != 1 && yes != 12)
									{
										PlayerScreen(player3.tiles, board, letters, amount, isReplaced, player3.points, player3.name, &exit, Coordinate, &placecount);
										EndTurn(isReplaced, player3.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player3.points, &yes, &player3.playerstat.highscore, player3);
										Pause();Pause();
									}
									
							while((player1.points != 88 || player2.points != 88) && exit != 1 && yes != 12)
							{
								PlayerScreen(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);
								Pause();Pause();
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
								
									if(exit != 1 && yes != 12)
									{
										PlayerScreen(player3.tiles, board, letters, amount, isReplaced, player3.points, player3.name, &exit, Coordinate, &placecount);
										EndTurn(isReplaced, player3.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player3.points, &yes, &player3.playerstat.highscore, player3);
										Pause();Pause();
									}
							}
							
							if(player1.points > player2.points && player3.points)
							{
								printf("%s Wins !\n", player1.name);
							}
							else if(player2.points > player1.points && player3.points)
							{
								printf("%s Wins !\n", player2.name);
							}
							else if(player3.points > player1.points && player2.points)
							{
								printf("%s Wins !\n", player3.name);
							}
							else
							{
								printf("Tie !\n");
							}
							
								printf("Play Again?\n");
								printf("[1]Yes\n");
								printf("[2]No\n");
								scanf("%d", &again);
								
									if(again == 2)
									{
										again = 0;
										exit = 1;
									}
									else
									{	
									}
						
					break;
					
					case 3:
						
						printf("Input Player Name: \n");
						printf("Player 1: \n");
						scanf("%s", player1.name);
						printf("Player 2: \n");
						scanf("%s", player2.name);
						printf("Player 3: \n");
						scanf("%s", player3.name);
						printf("Player 4: \n");
						scanf("%s", player4.name);
							
							Reset_Placecount(Coordinate);	
							StartTiles(player1.tiles, letters, amount);
							StartTiles(player2.tiles, letters, amount);	
							StartTiles(player3.tiles, letters, amount);	
							StartTiles(player4.tiles, letters, amount);	
							
						
								PlayerScreenFirst(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);
								Pause();Pause();
							
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
								
									if(exit != 1 && yes != 12)
									{
										PlayerScreen(player3.tiles, board, letters, amount, isReplaced, player3.points, player3.name, &exit, Coordinate, &placecount);
										EndTurn(isReplaced, player3.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player3.points, &yes, &player3.playerstat.highscore, player3);
										Pause();Pause();
									}
									
										if(exit != 1 && yes != 12)
										{
											PlayerScreen(player4.tiles, board, letters, amount, isReplaced, player4.points, player4.name, &exit, Coordinate, &placecount);
											EndTurn(isReplaced, player4.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player4.points, &yes, &player4.playerstat.highscore, player4);
											Pause();Pause();
										}
									
									
							while((player1.points != 88 || player2.points != 88) && exit != 1 && yes != 12)
							{
								PlayerScreen(player1.tiles, board, letters, amount, isReplaced, player1.points, player1.name, &exit, Coordinate, &placecount);
								EndTurn(isReplaced, player1.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player1.points, &yes, &player1.playerstat.highscore, player1);
								Pause();Pause();
							
								if(exit != 1 && yes != 12)
								{
									PlayerScreen(player2.tiles, board, letters, amount, isReplaced, player2.points, player2.name, &exit, Coordinate, &placecount);
									EndTurn(isReplaced, player2.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player2.points, &yes, &player2.playerstat.highscore, player2);
									Pause();Pause();
								}
								
									if(exit != 1 && yes != 12)
									{
										PlayerScreen(player3.tiles, board, letters, amount, isReplaced, player3.points, player3.name, &exit, Coordinate, &placecount);
										EndTurn(isReplaced, player3.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player3.points, &yes, &player3.playerstat.highscore, player3);
										Pause();Pause();
									}
									
										if(exit != 1 && yes != 12)
										{
											PlayerScreen(player4.tiles, board, letters, amount, isReplaced, player4.points, player4.name, &exit, Coordinate, &placecount);
											EndTurn(isReplaced, player4.tiles, letters, amount, Coordinate, wordlist, board, word, point, &player4.points, &yes, &player4.playerstat.highscore, player4);
											Pause();Pause();
										}
							}
							
							if(player1.points > player2.points && player3.points && player4.points)
							{
								printf("%s Wins !\n", player1.name);
							}
							else if(player2.points > player1.points && player3.points && player4.points)
							{
								printf("%s Wins !\n", player2.name);
							}
							else if(player3.points > player1.points && player2.points && player4.points)
							{
								printf("%s Wins !\n", player3.name);
							}
							else if(player4.points > player1.points && player2.points && player3.name) 
							{
								printf("%s Wins !\n", player4.name);
							}
							else
							{
								printf("Tie !\n");
							}
							
								printf("Play Again?\n");
								printf("[1]Yes\n");
								printf("[2]No\n");
								scanf("%d", &again);
								
									if(again == 2)
									{
										again = 0;
										exit = 1;
									}
									else
									{	
									}
					break;
					
				}		
				

				fseek(data, 0, SEEK_SET);
				for(i = 0; i < 10; i++)
				{
					fread(&Temp, sizeof(PlayerData), 1, data);
				    if(strcmp(player1.name, Temp.name) == 0)
				    {
				    	player1found = 1;
				    	RecordStats(&player1, Temp);
				        fseek(data, -52, SEEK_CUR);
				        fwrite(&player1, sizeof(PlayerData), 1, data);
					}
				       
				}
					if(player1played == 1 && player1found != 1) 
					{
						fwrite(&player1, sizeof(PlayerData), 1, data);
					}
				
				fseek(data, 0, SEEK_SET);
				for(i = 0; i < 10; i++)
				{
					fread(&Temp, sizeof(PlayerData), 1, data);
				    if(strcmp(player2.name, Temp.name) == 0)
				    {
				    	player2found = 1;
				    	RecordStats(&player2, Temp);
				        fseek(data, -52, SEEK_CUR);
				        fwrite(&player2, sizeof(PlayerData), 1, data);
					}
				   
				}
					if(player2played == 1 && player2found != 1) 
					{
						fwrite(&player2, sizeof(PlayerData), 1, data);
					}
				
				fseek(data, 0, SEEK_SET);
				for(i = 0; i < 10; i++)
				{
				    if(strcmp(player3.name, Temp.name) == 0)
				    {
				    	player3found = 1;
				    	RecordStats(&player3, Temp);
				        fseek(data, -52, SEEK_CUR);
				        fwrite(&player3, sizeof(PlayerData), 1, data);
					} 
				       
				}
				
					if(player3played == 1 && player3found != 1) 
					{
						fwrite(&player3, sizeof(PlayerData), 1, data);
					}
					
				fseek(data, 0, SEEK_SET);
				for(i = 0; i < 10; i++)
				{
					if(strcmp(player4.name, Temp.name) == 0)
					{
						player4found = 1;
						RecordStats(&player4, Temp);
				        fseek(data, -52, SEEK_CUR);
				        fwrite(&player4, sizeof(PlayerData), 1, data);
					} 
				
				}
					if(player4played == 1 && player4found != 1) 
					{
						fwrite(&player4, sizeof(PlayerData), 1, data);
					}
				fflush(data);
				fseek(data, 0, SEEK_SET);
				
				 player1played = 0;
				 player2played = 0;
				 player3played = 0;
				 player4played = 0;
				 player1found = 0;
				 player2found = 0;
				 player3found = 0;
				 player4found = 0;    
			}
			while(again != 0);
		}
	return 0;
}
		
		

					
	
/* letter amount checking 
	int i;
	
	for(i = 0; i < 27; i++)
	{
		printf("%d ", amount[i]);
	}         
*/
/*	turn = Turn();
					switch(turn)
					{
					case 1:   
						Place_Tiles(tiles, board); 
			        break;
			    		
			        
			        case 2: 
						Replace_Tiles(tiles, letters, amount, isReplaced);
					break;*/
           
		   
                    
                    
