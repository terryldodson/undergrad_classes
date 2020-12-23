//Lab Synopsis: Creating a game using dynamic memory. User can only go north, south, east, and west, and they're goal
//is to make it to the last room. The main objective was learning how to store information into dynamic memory
//Students and TA's I worked with: Daniel (TA), Daniel (Student), Camille, Brent
//Name: Terryl Dodson

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//structure for the data for each room
struct Data{
	string title;
	string info;
	int north = 0;
	int south = 0;
	int east = 0;
	int west = 0;
};//end of Data struct

//structure for rooms
struct Game{
	Data **p; //array of data
	int rooms;
};//end of Game struct

int main (int argc, char **argv) {
	char *buff;
	FILE *f;
	Data *d;
	Game *g;
	int count = 0;
	ifstream fin;
	istringstream sin;
	istringstream sin1;
	char direction;

	g = new Game;

	g->rooms = 1;
	g->p = new Data *[g->rooms];

	//exits if there aren't two command arguments
	if(argc != 2) {
		exit(1);
	}//end of if

	buff = new char[256];
	f = fopen(argv[1], "r");

	//reads in title, description, and exits
	while(1) {
		//title section
		if(fgets(buff,255,f) == NULL)
			break;
		d = new Data();
		d->north = -1;
		d->south = -1;
		d->east = -1;
		d->west = -1;
		d->title = string(buff);
		g->p[count] = d;
		fgets(buff, 255, f);
		count++;
		g->rooms++;
		g->p = (Data **)realloc(g->p, g->rooms * sizeof(Data *)); //number of rooms x size of one pointer

		//description section
		//assigns the direction
		while(1) {
			if(fgets(buff, 255, f) == NULL)
				break;
			if(strcmp(buff, "~\n") == 0)
				break;
			d->info = string(buff);
		}//end of description while loop

		/*exits*/
		//reads in the exits for each room and stores them into the assigned direction
		while(1) {
            if(fgets(buff, 255, f) == NULL)
                break;
            if(strcmp(buff, "~\n") == 0)
                break;
			char a;
			int b;
			sscanf(buff, "%c %d", &a, &b);
			switch(a){
				case 'n':
					d->north = b;
				break;
				case 'e':
					d->east = b;
				break;
				case 's':
					d->south = b;
				break;
				case 'w':
					d->west = b;
				break;
			}//end of switch
        }//end of exit while loop
	}//end of outer while loop
	
		//start of user interface
		printf("%s", "q - Quit (closes the program)\n");
		printf("%s", "l - Look (looks at the room the player is in)\n");
		printf("%s", "n, e, s, w - Moves the user in the given cardinal direction (north, east, south, or west)\n");
	
		//starts room at index 0
		d = g->p[0];
	
		//continues to run the game until user enters q
		while(1){
			direction = getchar();
			getchar();
			switch(direction){
				case 'n':
					if(d->north != -1) {
						d = g->p[d->north];
					}//end of if
					if(d->north == -1) {
						printf("You can't go north.\n");
					}//end of if
				break;
				case 'e':	
					if(d->east != -1) {
                        d = g->p[d->east];
                    }//end of if
                    if(d->east == -1) {
                        printf("You can't go east.\n");
                    }//end of if
				break;
				case 's':
					 if(d->south != -1) {
                        d = g->p[d->south];
                    }//end of if
                    if(d->south == -1) {
                        printf("You can't go south.\n");
                	}//end of if
				break;
				case 'w':
					 if(d->west != -1) {
                        d = g->p[d->west];
                    }//end of if
                    if(d->west == -1) {
                        printf("You can't go west.\n");
                    }//end of if
				break;
				case 'l':
					printf("\n%s",d->title.c_str());
					printf("%s", d->info.c_str());
					printf("Exits:");
					if(d->north != -1)
						printf("n ");
					if(d->east != -1)
						printf("e ");
					if(d->south != -1)
						printf("s ");
					if(d->west != -1)
						printf("w ");

					printf("\n");
					break;
				case 'q':
					return -1;
				break;
			}//end of switch
		}//end of while		
	
	//closes file and deletes dynamic memory
	fclose(f);
	delete[] buff;

	return 0;
}//end of main
