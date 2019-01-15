#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void handshake(int client_sockfd){
  char string[HANDSHAKE_BUFFER_SIZE];
  send(client_sockfd, ACK, HANDSHAKE_BUFFER_SIZE, 0);
  recv(client_sockfd, string, HANDSHAKE_BUFFER_SIZE,0);
  printf("[SERVER] Message received %s\n", string);
  send(client_sockfd, "RECIEVED", HANDSHAKE_BUFFER_SIZE, 0);
}

void make_new_user(int client_sockfd){
  int users = open("USERS", O_RDWR);
  struct user new_usr;
  printf("in mkuser");
  char msg[BUFFER_SIZE];

  recv(client_sockfd, msg, BUFFER_SIZE,0);
  strncpy(msg, new_usr.name, USER_INFO_SIZE);
  
  recv(client_sockfd, msg, BUFFER_SIZE,0);
  strncpy(new_usr.pass, msg, USER_INFO_SIZE);
  write(users, &new_usr, sizeof new_usr);
  struct user old_usr;
  read(users, &old_usr, sizeof new_usr);
  printf("%s", old_usr.name);
}

void handle_client_requests(int client_sockfd){
  while(1){
    char string[BUFFER_SIZE];
    recv(client_sockfd, string, BUFFER_SIZE,0);
    printf("msg: %s", string);
    if(!strncmp(string, "new_usr", 7))
      make_new_user(client_sockfd);

    else if (!strcmp(string, "login"))
      send(client_sockfd, "loggin in", BUFFER_SIZE, 0);
  }
}

int sub_main(int client_sockfd){
  int err = open("sub.err", O_CREAT||O_RDWR, 0666);

  dup2(err, 1);
  printf("dfks;");
  handshake(client_sockfd);
  handle_client_requests(client_sockfd);
  
}
