#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int client_handshake(int sockfd){
  char string[HANDSHAKE_BUFFER_SIZE];
  recv(sockfd, string, HANDSHAKE_BUFFER_SIZE, 0);
  printf("%s", string);
}

int main(int argc, char * argv[]) {
  int sockfd;
  struct addrinfo hints, *serverinfo;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(argv[1], PORTNUM, &hints, &serverinfo);
  sockfd = socket(serverinfo->ai_family, serverinfo->ai_socktype,
		  serverinfo->ai_protocol);
  
  printf("[CLIENT] Attempting to connect to argv[1]... ");
  connect(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen);

  printf("[CLIENT] Connected! ");

  client_handshake(sockfd);

  /*
  char response[BUFFER_SIZE];
  while(1){
    printf("[CLIENT]: ");
    fgets(string, BUFFER_SIZE, stdin);
    write(to_server, string, BUFFER_SIZE);
    read(from_server, response, BUFFER_SIZE);
    printf("[SERVER] %s", response);
  }
  */
}
