#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define PORTNUM "9949"
#define ACK "HELLO"
#define ERR "ERRO"
#define PASS "PASS"
#define SUCCESS_SIG_SIZE 4
#define BUFFER_SIZE 15
#define HANDSHAKE_BUFFER_SIZE 10
#define USER_INFO_SIZE 10

int sub_main(int client_sockfd);
void dashboard_main(int client_sockfd);
void user_home(int sockfd);

struct user{
  char name[10];
  char pass[10];
  int convo_ids[100];
  int num_friends;
  char friends[100];
  char requests[100];
};
