#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define BACKLOG 10

static void on_close(int signo){
  printf("[SERVER] Closing server...");
  remove("sub.log");
  //remove("USERS");
  exit(0);
}


int main() {
  struct sockaddr_storage their_addr;
  socklen_t addr_size;
  struct addrinfo hints, *res;
  int server_sockfd;
  int users;

  users = open("USERS", O_CREAT | O_RDWR, 0666);
  
  memset(&hints, 0,sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  getaddrinfo(NULL, PORTNUM, &hints, &res);
  
  server_sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  int yes=1;
  if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes)==-1){
    perror("setsockopt");
    exit(1);
  }
  bind(server_sockfd, res->ai_addr, res->ai_addrlen);
  listen(server_sockfd, BACKLOG);
  
  signal(SIGINT, on_close);
  
  while(1){
    int sin_size = sizeof their_addr;
    printf("[SERVER] Waiting for new client...\n");
    int client_sockfd = accept(server_sockfd,
			       (struct sockaddr *) &their_addr,
			       &sin_size);

    printf("[SERVER] New client has connected\n");

    int f = fork();

    if(!f){
      sub_main(client_sockfd);


      /*
      while(read(from_client, received, BUFFER_SIZE)>0){
	printf("[SERVER] Message received: %s", received);
	strcpy(to_send, received);
	int i=0;
	while(to_send[i]){
	  if(!strncmp(&to_send[i], "c", 1))
	    to_send[i] = 'b';
	  i++;
	}
	
	write(to_client, to_send, BUFFER_SIZE);
      }
      */
      //close(to_client);
      printf("[SERVER] Client disconnected\n");
    }
  }
}
