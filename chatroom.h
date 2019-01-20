#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PORTNUM "9949"
#define ACK "HELLO"
#define ERR "ERRO"
#define PASS "PASS"
#define SUCCESS_SIG_SIZE 4
#define BUFFER_SIZE 15
#define CONVO_BUFFER_SIZE 30
#define HANDSHAKE_BUFFER_SIZE 10
#define USER_INFO_SIZE 10
#define CONVO_SAVE_SIZE 500

struct user{
  char name[10];
  char pass[10];
  int convo_ids[100];
  int num_friends;
  int num_requests;
  char friends[100][10];
  char requests[100][10];
};

union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
			      (Linux-specific) */
};


int sub_main(int client_sockfd);
int lookup_account(char* name, struct user* buf);
int update_account(struct user* buf);
void dashboard_main(int client_sockfd, struct user* usr);
void user_home(int sockfd);
