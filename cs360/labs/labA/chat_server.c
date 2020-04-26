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

void* chat_rooms(void *cr);
void* client_process(void *name);

int main (int argc, char *argv[]) {
	int port, sock, i, num;	
	pthread_t* rooms; 
	pthread_t* people;
	JRB tmp;

	rooms = (pthread_t*) malloc(sizeof(pthread_t) * (argc-2));

	//error checks
	if(argc < 3) {
		fprintf(stderr, "not enough arguments\n");
		exit(1);
	}

	chats = make_jrb();

	for(i = 2; i < argc; i++) {	
		ChatRoom cr = (ChatRoom) malloc(sizeof(struct ChatRoom));	
		cr->room_name = (char*) (strdup(argv[i]));

		//created dllist
		cr->messages = new_dllist();
		cr->clients = new_dllist();

		//malloced for pthreads
		cr->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		cr->cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));

		pthread_create(&rooms[i-2], NULL, chat_rooms, (void*) cr);	
		jrb_insert_str(chats, cr->room_name, new_jval_v((void*) cr)); 
	}

	//obtained port number
	port = atoi(argv[1]);

	//served socket and accepts connection
	sock = serve_socket(port);

	if(sock < 0) {
		perror("serve_socket");
		exit(1);
	}

	while(1) {
		Client* name = (Client*) malloc(sizeof(struct Client));

		name->fd = accept_connection(sock);

		//passed in socket and opened fin for read and fout for write
		name->fin = fdopen(name->fd, "r");
		name->fout = fdopen(name->fd, "w");

		people = (pthread_t*) malloc(sizeof(pthread_t));

		pthread_create(people, NULL, client_process, (void*) name);

	}//end of while
} //end of main

void* chat_rooms(void *cr) {
	Client* person;
	char m[1000];
	Dllist tmp, tmp1;
	ChatRoom chat;
	chat = (ChatRoom) cr;


	while(1) {

		pthread_cond_wait(chat->cond, chat->mutex);

		while(!dll_empty(chat->messages)) {
			if(!dll_empty(chat->clients)) {	
				dll_traverse(tmp, chat->messages) {				
					dll_traverse(tmp1, chat->clients) {
						Client* p = (void*) tmp1->val.v;

						fputs(tmp->val.s, p->fout);
						fflush(p->fout);
					}
				}

				free_dllist(chat->messages);
				chat->messages = new_dllist();
			}
		}
	}
}

void* client_process(void *name) {
	JRB tmp, chk;
	ChatRoom cr;
	Client* person;
	person = (Client*) name;
	Dllist tmp1;
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

	jrb_traverse(tmp, chats) {
		cr = (ChatRoom) tmp->val.v;
		fputs(cr->room_name, person->fout);
		fflush(person->fout);
		fputs(": ", person->fout);

		dll_traverse(tmp1, cr->clients) {
			Client* tmp2;
			tmp2 = (Client*) tmp1;
			//printf("tmp2: %s\n", tmp2->client_name);
			fputs(tmp2->client_name, person->fout);		
			fflush(person->fout);
			fputs(" ", person->fout);
			fflush(person->fout);
		}

		fputs("\n", person->fout);
	}

	fputs("\nEnter your chat name (no spaces):\n", person->fout);	
	fflush(person->fout);
	fgets(s, 1000, person->fin);
	size_t lnt = strlen(s);
	s[lnt-1] = '\0';

	do {
		fputs("Enter chat room:\n", person->fout);
		fflush(person->fout);	
		fgets(c, 1000, person->fin);
		size_t ln = strlen(c);
		c[ln-1] = '\0';

		chk = jrb_find_str(chats, c);

	} while (chk == NULL);

	cr = chk->val.v;	

	pthread_mutex_lock(cr->mutex);
	person->client_name = strdup(s);
	dll_append(cr->clients, new_jval_v(person));
	pthread_mutex_unlock(cr->mutex);

	pthread_mutex_lock(cr->mutex);
	strcpy(client, person->client_name);
	strcpy(join, " has joined\n");
	strcat(client, join);
	printf("joined: %s\n", client);
	dll_append(cr->messages, new_jval_v(strdup(client)));	
	pthread_cond_signal(cr->cond);
	pthread_mutex_unlock(cr->mutex);

	while(1) {

		 if(fgets(m, 1000, person->fin) != NULL) {
			size_t lne = strlen(m);
			strcpy(client, person->client_name);
			strcpy(colon, ": ");
			strcat(sentence, client);
			strcat(sentence, colon);
			strcat(sentence, m);	
			printf("sentence: %s\n", sentence);
	
			pthread_mutex_lock(cr->mutex);
			dll_append(cr->messages, new_jval_v(strdup(sentence)));
			pthread_cond_signal(cr->cond);
			pthread_mutex_unlock(cr->mutex);
		}

		else {
			strcpy(client, person->client_name);
			strcpy(exiting, " has left\n");
			strcat(final_exit, client);
			strcat(final_exit, exiting);
			printf("%s\n", final_exit);	
			
			pthread_mutex_lock(cr->mutex);
			dll_append(cr->messages, new_jval_v(strdup(final_exit)));	
			pthread_cond_signal(cr->cond);
			pthread_mutex_unlock(cr->mutex);
		}
	}
}

