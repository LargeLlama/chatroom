#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void start_conversation(int client_sockfd, int convofd, struct user* usr){
  char string[BUFFER_SIZE];
  char to_send[200];
  recv(client_sockfd, string, BUFFER_SIZE,0);
  
  while(strncmp(string, "/quit", 5)){
    if(strcmp(string,"\n")){
      // lseek(convofd, -200, SEEK_END);
      read(convofd, to_send, 200);
    }
    write(convofd, string, BUFFER_SIZE);
    // lseek(convofd, -200, SEEK_END);
    read(convofd, to_send, 200);
    send(client_sockfd, to_send, BUFFER_SIZE,0);
    recv(client_sockfd, string, BUFFER_SIZE,0);
    
  }
}

void get_convo(int client_sockfd, struct user* usr){
  printf("in get convo\n");
  char string[USER_INFO_SIZE];
  char *first;
  char *last;
  
  recv(client_sockfd, string, USER_INFO_SIZE,0);

  for(int i=0; strncmp(usr->friends[i], string, USER_INFO_SIZE); i++){
    if(i==usr->num_friends-1){
        send(client_sockfd, ERR, BUFFER_SIZE,0);
	printf("bad name\n");
	return;
    }
  }
  send(client_sockfd, PASS, BUFFER_SIZE,0);
      
  if(strncmp(usr->name, string, USER_INFO_SIZE)<0){
    first = usr->name;
    last = string;
  }
  else{
    last = usr->name;
    first = string;
  }

  char convo_name[strlen(first) + strlen(last)];
  strncpy(convo_name, first, strlen(first));
  strncpy(convo_name+strlen(first), last, strlen(last)+1);
  printf("convo: %s\n", convo_name);
  int convo = open(convo_name, O_CREAT | O_RDWR | O_APPEND, 0666);
 
  start_conversation(client_sockfd, convo, usr);
  
}

void list_friends(int client_sockfd, struct user* usr){
  for(int i=0; i<usr->num_friends; i++){
    send(client_sockfd, usr->friends[i], BUFFER_SIZE,0);
  }
  send(client_sockfd, PASS, BUFFER_SIZE,0);
}

void check_requests(int client_sockfd, struct user* usr){
  char string[BUFFER_SIZE];

  for(int i=0; i<usr->num_requests; i++){
    send(client_sockfd, usr->requests[i], BUFFER_SIZE,0);
    recv(client_sockfd, string, BUFFER_SIZE,0);
    if(!strncmp(string, "y", 1)){
      strcpy(usr->friends[usr->num_friends], usr->requests[i]);
      usr->num_friends++;
    }
  }
  usr->num_requests = 0;
  send(client_sockfd, PASS, BUFFER_SIZE,0);
  update_account(usr);
}

void add_friend(int client_sockfd, struct user* usr){
  printf("in add friend");
  char string[BUFFER_SIZE];
  struct user friend;
  recv(client_sockfd, string, BUFFER_SIZE,0);
  int unreg = lookup_account(string, &friend);
  if(unreg){
    printf("Friend add fail, user doesn't exist\n");
    send(client_sockfd, ERR, BUFFER_SIZE,0);
    return; 
  }
  
  printf("Sending request %s\n", usr->name);
  send(client_sockfd, PASS, BUFFER_SIZE,0);

  strcpy(friend.requests[friend.num_requests], usr->name);
  friend.num_requests++;
  update_account(&friend);
  printf("num: %d\n", friend.num_requests);
  printf("Sending request\n");
  printf("%s fdsk\n", friend.requests[friend.num_requests-1]);
  send(client_sockfd, friend.name, BUFFER_SIZE,0);
  return;
}

void dashboard_main(int client_sockfd, struct user* _usr){
  struct user* usr= _usr;
  int logged_in = 1;
  char string[BUFFER_SIZE];

  while(logged_in){
    recv(client_sockfd, string, BUFFER_SIZE,0);
    if(!strncmp(string, "add friend", 10)){
      add_friend(client_sockfd, usr);
    }

    if(!strncmp(string, "check reqs", 10)){
      check_requests(client_sockfd, usr);
    }

    
    if(!strncmp(string, "show friends", 12)){
      list_friends(client_sockfd, usr);
    }

    if(!strncmp(string, "get convo", 9)){
      get_convo(client_sockfd, usr);
    }

  }
}
