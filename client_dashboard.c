#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

void enter_convo(int sockfd){

  char string[CONVO_SAVE_SIZE];
  char input[CONVO_BUFFER_SIZE];
  time_t s_time;
  char * time;
  printf("\n====================================\n");
 
  recv(sockfd, &s_time, sizeof s_time, 0);
  time = ctime(&s_time);
  printf("Last active %s", time);
  printf("====================================\n");

  while(strncmp(input, "/quit", 5)){
    printf("[ENTER to update feed]:");
  
    fgets(input, CONVO_BUFFER_SIZE, stdin);    
    send(sockfd, input, CONVO_BUFFER_SIZE, 0);
    recv(sockfd, string, CONVO_SAVE_SIZE, 0);
    
    printf("\e[1;1H\e[2J");
    printf("%s", string);
  }
}

void start_convo(int sockfd){
  char string[BUFFER_SIZE];
  printf("Choose a recepient:\n");
  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = 0;
  send(sockfd, string, USER_INFO_SIZE, 0);
  recv(sockfd, string, BUFFER_SIZE, 0);
  if(!strncmp(string, ERR, BUFFER_SIZE)){
    printf("That person isn't one of your friends\n");
    return;
  }

  enter_convo(sockfd);
  
}

void get_friend_list(int sockfd){
  char string[BUFFER_SIZE];
  printf("============\n");
  printf("Friends list\n");
  printf("============\n");

  recv(sockfd, string, BUFFER_SIZE, 0);
  while(strncmp(string, PASS, SUCCESS_SIG_SIZE)){
    printf("  %s\n", string);
    recv(sockfd, string, BUFFER_SIZE, 0);
  }

  printf("============\n");
}

void check_request_form(int sockfd){
  char string[BUFFER_SIZE];
  recv(sockfd, string, BUFFER_SIZE, 0);
  while(strncmp(string, PASS, SUCCESS_SIG_SIZE)){
    if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
      printf("Bad answer. Please answer with y/n\n");
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

    if(!strncmp(string, "messaging", 9)){
      send(sockfd, "show friends", BUFFER_SIZE, 0);
      get_friend_list(sockfd);
      send(sockfd, "get convo", BUFFER_SIZE, 0);
      start_convo(sockfd);
    }


  } 


}
