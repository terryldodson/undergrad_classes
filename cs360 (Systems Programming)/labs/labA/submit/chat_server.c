/*Name: Terryl Dodson
 * Date: 4/26/20
 * Description: Had to make a chat server using
 * pthreads, mutexes and conditionals. Also had to use 
 * fgets and fputs*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#include "jrb.h"
#include "dllist.h"
#include "fields.h"
#include "sockettome.h"

//global jrb tree for chats
JRB chats;

typedef struct Client
{
	char *client_name;
	FILE *fin;
	FILE *fout;
	int fd;
	char *exiting;
}Client;

typedef struct ChatRoom
{
	char *room_name;
	Dllist messages;
	Dllist clients;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
}*ChatRoom;

//initializing functions
void* chat_rooms(void *cr);
void* client_process(void *name);

int main (int argc, char *argv[]) {
	int port, sock, i, num;	
	pthread_t* rooms; 
	pthread_t* people;
	JRB tmp;

	//malloc for each chat room
	rooms = (pthread_t*) malloc(sizeof(pthread_t) * (argc-2));

	//error checks
	if(argc < 3) {
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}//end of if

	//create jrb for chats
	chats = make_jrb();

	//for loop in order to take care of each room 
	for(i = 2; i < argc; i++) {	
		//malloc for a ChatRoom object
		ChatRoom cr = (ChatRoom) malloc(sizeof(struct ChatRoom));	
		cr->room_name = (char*) (strdup(argv[i]));

		//created dllist
		cr->messages = new_dllist();
		cr->clients = new_dllist();

		//malloced for pthreads
		cr->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		cr->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));

		//create thread and call chat_rooms function
		//inserted each chat room in the tree
		pthread_create(&rooms[i-2], NULL, chat_rooms, (void*) cr);	
		jrb_insert_str(chats, cr->room_name, new_jval_v((void*) cr)); 
	} //end of for

	//obtained port number
	port = atoi(argv[1]);

	//served socket and accepts connection
	sock = serve_socket(port);

	//error checking for sock
	if(sock < 0) {
		perror("serve_socket");
		exit(1);
	} //end of if

	while(1) {
		Client* name = (Client*) malloc(sizeof(struct Client));

		//waiting for connection and accepting the connection 
		name->fd = accept_connection(sock);

		//passed in socket and opened fin for read and fout for write
		name->fin = fdopen(name->fd, "r");
		name->fout = fdopen(name->fd, "w");

		//malloc for thread
		people = (pthread_t*) malloc(sizeof(pthread_t));

		//call client function for all the clients
		pthread_create(people, NULL, client_process, (void*) name);
	
	}//end of while

	//freeing memory
	free(rooms);

	for(i = 2; i < argc; i++) {
		ChatRoom cr;
		free(cr);
	} //end of for

	while(1) {
		Client* name;
		free(name);
	} //end of while
} //end of main

void* chat_rooms(void *cr) {
	Client* person;
	char m[1000];
	Dllist tmp, tmp1;
	ChatRoom chat;
	chat = (ChatRoom) cr;


	while(1) {
		
		pthread_cond_wait(chat->cond, chat->mutex);

		//checking if clients list is empty
		if(!dll_empty(chat->clients)) {	
			//traverse through messages and clients list as long
			//as clients list isn't empty
			dll_traverse(tmp, chat->messages) {	
				dll_traverse(tmp1, chat->clients) {
					if(tmp1 == NULL) 
						continue;
					
					//created a new client and printed 
					//each message out to their server
					Client* p = (Client*) tmp1->val.v;

					fputs(tmp->val.s, p->fout);
					fflush(p->fout);
				} //end of inner dll_traverse
			} //end of outer dll_traverse
		} //end of if

		//free the message list and recreate
		free_dllist(chat->messages);
		chat->messages = new_dllist();
	} //end of while
} //end of chat_rooms function

void* client_process(void *name) {
	JRB tmp, chk;
	ChatRoom cr;
	Client* person;
	person = (Client*) name;
	Dllist tmp1;
	Dllist tmp2, tmp3;
	int return_value;
	char client[1000];
	char join[20];
	char colon[5];
	char statement[1000];
	char sentence[1000];
	char exiting[1000];
	char final_exit[1000];
	char s[1000];
	char c[1000];
	char m[1000];

	fputs("Chat Rooms:\n\n", person->fout);	
	fflush(person->fout);

	//listing all chat rooms and 
	//who's in each room
	jrb_traverse(tmp, chats) {
		cr = (ChatRoom) tmp->val.v;
		fputs(cr->room_name, person->fout);
		fflush(person->fout);
		fputs(":", person->fout);

		dll_traverse(tmp1, cr->clients) {
			Client* tmp2 = (Client*) tmp1->val.v;
			fputs(" ", person->fout);
			fflush(person->fout);
			fputs(tmp2->client_name, person->fout);		
			fflush(person->fout);
		} //end of dll_traverse

		fputs("\n", person->fout);
	} //end of jrb_traverse

	//prompts for chat name
	//and checks value
	return_value = fputs("\nEnter your chat name (no spaces):\n", person->fout);	
	
	//if value is end of file, then close
	//buffers and exit thread
	if(return_value == EOF) {
		fclose(person->fin);
		fclose(person->fout);
		pthread_exit(person);
	} //end of if

	//obtain the chat name
	fflush(person->fout);
	fgets(s, 1000, person->fin);
	size_t lnt = strlen(s);
	s[lnt-1] = '\0';

	//continuously as for chat room till
	//user enters a valid room name
	do {
		return_value = fputs("Enter chat room:\n", person->fout);
		
		//checks value returned from fputs
		//if end of file then close buffers
		//and exit thread
		if(return_value == EOF) {
			fclose(person->fin);
			fclose(person->fout);
			pthread_exit(person);
			continue;
		} //end of if

		//obtain chat room
		fflush(person->fout);	
		fgets(c, 1000, person->fin);
		size_t ln = strlen(c);
		c[ln-1] = '\0';

		//find chat room in tree
		//and obtain the pointer to that 
		//chat room
		chk = jrb_find_str(chats, c);

	} while (chk == NULL);

	cr = chk->val.v;	

	//append client to clients list
	pthread_mutex_lock(cr->mutex);
	person->client_name = strdup(s);
	dll_append(cr->clients, new_jval_v(person));
	pthread_cond_signal(cr->cond);
	pthread_mutex_unlock(cr->mutex);

	//created the joined string for each client
	//and appended it to messages list
	pthread_mutex_lock(cr->mutex);
	strcpy(client, person->client_name);
	strcpy(join, " has joined\n");
	strcat(client, join);
	dll_append(cr->messages, new_jval_v(strdup(client)));	
	strcpy(client, "");
	pthread_cond_signal(cr->cond);
	pthread_mutex_unlock(cr->mutex);

	//as long as the user enters a message
	//obtain the message and store it in the messages list
	while(fgets(m, 1000, person->fin) != NULL) {
		size_t lne = strlen(m);
		strcpy(client, person->client_name);
		strcpy(colon, ": ");
		strcat(sentence, client);
		strcat(sentence, colon);
		strcat(sentence, m);	
	
		pthread_mutex_lock(cr->mutex);
		dll_append(cr->messages, new_jval_v(strdup(sentence)));
		strcpy(sentence, "");
		pthread_cond_signal(cr->cond);
		pthread_mutex_unlock(cr->mutex);

	} //end of while loop

	//as soon as user exits
	//store exiting string in messages list
	strcpy(client, person->client_name);
	strcpy(exiting, " has left\n");
	strcat(final_exit, client);
	strcat(final_exit, exiting);
			
	pthread_mutex_lock(cr->mutex);
	dll_append(cr->messages, new_jval_v(strdup(final_exit)));	
	strcpy(final_exit, "");
	pthread_cond_signal(cr->cond);
	pthread_mutex_unlock(cr->mutex);

	//once user exits delete user from
	//client list
	dll_traverse(tmp2, cr->clients) {
		Client* tmp3 = (Client*) tmp2->val.v;
		if(person == tmp3) {
			dll_delete_node(tmp2);
			break;
		}
	}//end of dll_traverse

	//close buffers and exit thread
	fclose(person->fin);
	fclose(person->fout);
	pthread_exit(person);
} //end of client_process function

