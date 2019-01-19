#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void get_friend_list(int sockfd){
  char string[BUFFER_SIZE];
  printf("Friends:\n");
  recv(sockfd, string, BUFFER_SIZE, 0);
  while(strncmp(string, PASS, SUCCESS_SIG_SIZE)){
    printf("%s\n", string);
    recv(sockfd, string, BUFFER_SIZE, 0);
  }
}

void check_request_form(int sockfd){
  char string[BUFFER_SIZE];
  recv(sockfd, string, BUFFER_SIZE, 0);
  while(strncmp(string, PASS, SUCCESS_SIG_SIZE)){
    if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
      printf("Bad answer\n");
      return;
    }
    
    printf("Add %s as friend? y/n: ", string);
    fgets(string, BUFFER_SIZE, stdin);
    string[strlen(string)-1] = 0;
    
    send(sockfd, string, BUFFER_SIZE, 0);
    recv(sockfd, string, BUFFER_SIZE, 0);
  }
  printf("No more requests! \n");

}

void add_friend_form(int sockfd){
  char string[BUFFER_SIZE];
  printf("Which friend?: ");
  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = 0;
  
  send(sockfd, string, BUFFER_SIZE, 0);
  recv(sockfd, string, BUFFER_SIZE, 0);

  if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
    printf("user doesn't exist");
    return;
  }
  if(!strncmp(string, PASS, SUCCESS_SIG_SIZE)){
    recv(sockfd, string, BUFFER_SIZE, 0);
    printf("request sent to %s\n",string );
    return;
  }


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

    if(!strncmp(string, "check reqs", 10)){
      send(sockfd, string, BUFFER_SIZE, 0);
      check_request_form(sockfd);
    }

    if(!strncmp(string, "show friends", 12)){
      send(sockfd, string, BUFFER_SIZE, 0);
      get_friend_list(sockfd);
    }

  } 


}
