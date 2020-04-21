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

JRB chats;

typedef struct Client
{
	char *client_name;
	FILE *fin;
	FILE *fout;
	int fd;
}Client;

typedef struct ChatRoom
{
	char *room_name;
	Dllist messages;
	Dllist clients;
	pthread_mutex_t *mutex;
	pthread_cond_t *cond;
}*ChatRoom;

void* chat_rooms(void *cr);
void* client_process(void *name);

int main (int argc, char *argv[]) {
	int port, sock, i, num;	
	pthread_t* rooms; 
	pthread_t* clients;

	rooms = (pthread_t*) malloc(sizeof(pthread_t) * (argc-2));

	//error checks
	if(argc < 3) {
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}

/*	chats = make_jrb();

	for(i = 2; i < argc; i++) {	
		ChatRoom cr = (ChatRoom) malloc(sizeof(struct ChatRoom));
		cr->room_name = (char*) malloc(sizeof(char*) * (argc-2));	

		//created dllist
		cr->messages = new_dllist();
		cr->clients = new_dllist();

		//malloced for pthreads
		cr->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		cr->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
		cr->room_name = (char*) (strdup(argv[i]));
		pthread_create(&rooms[i-2], NULL, chat_rooms, (void*) cr);	
		jrb_insert_str(chats, cr->room_name, new_jval_v((void*) cr)); 
	}*/

	//obtained port number
	port = atoi(argv[1]);

	//served socket and accepts connection
	sock = serve_socket(port);

	/*if(sock < 0) {
		perror("serve_socket");
		exit(1);
	}*/

	while(1) {
		Client* name = (Client*) malloc(sizeof(struct Client));

		name->fd = accept_connection(sock);

		//passed in socket and opened fin for read and fout for write
		name->fin = fdopen(name->fd, "r");
		name->fout = fdopen(name->fd, "w");

		pthread_create(clients, NULL, client_process, (void*) name);

/*		if(pthread_create(&clients, NULL, client_process, (void*) name) != 0) {
			perror("pthread_create");
			exit(1);
		}*/
	}//end of while
} //end of main

void* chat_rooms(void *cr) {

	return NULL;
}

void* client_process(void *name) {
	JRB tmp, chk;
	ChatRoom cr;
	Client* person;
	char s[1000];
	char c[1000];

	fputs("Chat Rooms:\n\n", person->fout);	

	jrb_traverse(tmp, chats) {
		cr = (ChatRoom) tmp->val.v;
		fputs(cr->room_name, person->fout);
		fputs(":\n", person->fout);
	}

	fputs("\nEnter your chat name (no spaces):\n", person->fout);	
	fflush(person->fout);
	fgets(s, 1000, person->fin);

	fputs("Enter chat room:\n", person->fout);
	fflush(person->fout);	
	size_t ln = strlen(c);
	c[ln-1] = '\0';
	fgets(c, 1000, person->fin);
	printf("chat: %s", c);

	chk = jrb_find_str(chats, c);
	//printf("%s\n", chats);

	if(chk == NULL) {
		printf("%s", "not in tree\n");
		//continue;
	} else {
		printf("%s", "in tree\n");
	}
	//	dll_append(clients, new_jval_s(strdup(s)));
}

