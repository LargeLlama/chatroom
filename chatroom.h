#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>



#define PORTNUM "9928"
#define ACK "HELLO"
#define BUFFER_SIZE 10
#define HANDSHAKE_BUFFER_SIZE 10

int sub_main(int client_sockfd);

struct user{
  char name[20];
  char pass[20];
  int convo_ids[100];
};
