#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void add_friend_form(int sockfd){
  char string[BUFFER_SIZE];
  printf("Which friend?: ");
  fgets(string, BUFFER_SIZE, stdin);

  send(sockfd, string, BUFFER_SIZE, 0);
  recv(sockfd, string, BUFFER_SIZE, 0);

  if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
    printf("user doesn't exist");
    return;
  }
  recv(sockfd, string, BUFFER_SIZE, 0);
  printf("found user: %s", string);

}

void user_home(int sockfd){
  int logged_in = 1;
  char string[BUFFER_SIZE];
  while(logged_in){
    printf("[DASHBOARD] ");
    fgets(string, BUFFER_SIZE, stdin);

    if(!strncmp(string, "add friend", 10)){
      send(sockfd, string, BUFFER_SIZE, 0);
      add_friend_form(sockfd);
    }
  }


}
