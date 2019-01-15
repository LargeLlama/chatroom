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
#define BUFFER_SIZE 10
#define HANDSHAKE_BUFFER_SIZE 10
#define USER_INFO_SIZE 10
int sub_main(int client_sockfd);

struct user{
  char name[10];
  char pass[10];
  int convo_ids[100];
};
