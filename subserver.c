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

void handle_client_requests(int client_sockfd){
  while(1){
    char string[BUFFER_SIZE];
    recv(client_sockfd, string, BUFFER_SIZE,0);

    if(!strcmp(string, "new user"))
      send(client_sockfd, "making user", BUFFER_SIZE, 0);
    else if (!strcmp(string, "login"))
      send(client_sockfd, "loggin in", BUFFER_SIZE, 0);
  }
}

int sub_main(int client_sockfd){
  handshake(client_sockfd);
  handle_client_requests(client_sockfd);
  
}
