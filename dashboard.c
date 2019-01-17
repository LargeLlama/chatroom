#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void add_friend(int client_sockfd, struct user usr){
  char string[BUFFER_SIZE];
  struct user friend;
  recv(client_sockfd, string, BUFFER_SIZE,0);
  int unreg = lookup_acount(string, &friend);
  if(unreg){
    printf("Friend add fail, user doesn't exist\n");
    send(client_sockfd, ERR, BUFFER_SIZE,0);
    return;
  }

  printf("Sending request %s\n", friend.name);
  send(client_sockfd, PASS, BUFFER_SIZE,0);
  
  friend.requests[friend.num_requests] = usr.name;
  friend.num_requests++;
  
}

void dashboard_main(int client_sockfd){
  int logged_in = 1;
  char string[BUFFER_SIZE];
  
  while(logged_in){
    recv(client_sockfd, string, BUFFER_SIZE,0);
    if(!strncmp(string, "add friend", 10)){
      add_friend(client_sockfd);p
    }
  }
}
