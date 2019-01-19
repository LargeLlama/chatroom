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
  int users = open("USERS", O_RDWR|O_APPEND);
  struct user new_usr;
  printf("in mkuser\n");
  char msg[BUFFER_SIZE];

  recv(client_sockfd, msg, BUFFER_SIZE,0);
  printf("Recieved %s", msg);
  strncpy(new_usr.name, msg, USER_INFO_SIZE);
  
  new_usr.name[strlen(new_usr.name)] = 0;
  new_usr.num_friends = 0;
  new_usr.num_requests = 0;

  recv(client_sockfd, msg, BUFFER_SIZE,0);
  strncpy(new_usr.pass, msg, USER_INFO_SIZE);

  write(users, &new_usr, sizeof new_usr);
  close(users);

}

int update_account(struct user* buf){
  int users = open("USERS", O_RDWR);
  struct user usr;
  int r, i;
  for(r=read(users, &usr, sizeof usr), i=0; strncmp(usr.name, buf->name, USER_INFO_SIZE) && r; r=read(users, &usr, sizeof usr), i++);
  printf("i: %d", i);
  lseek(users, i*sizeof usr, SEEK_SET);
  if(write(users, buf, sizeof usr)==-1){
    return -1;
  }
  else{
    printf("good");
    return 0;
  }
  
}

int lookup_account(char* name, struct user* buf){
  int users = open("USERS", O_RDWR);
  struct user usr;
  int r;
  for(r=read(users, &usr, sizeof usr); strncmp(usr.name,name, USER_INFO_SIZE) && r; r=read(users, &usr, sizeof usr));
  close(users);
  if(!r)
    return -1;
  *buf = usr;
  return 0;
}
  

void login(int client_sockfd){
  printf("in login\n");
  char msg[BUFFER_SIZE];
  recv(client_sockfd, msg, BUFFER_SIZE,0);

  struct user usr;
  int unreg = lookup_account(msg, &usr);
  if(unreg){
    printf("User '%s' does not exist", msg);
    send(client_sockfd, ERR, BUFFER_SIZE,0);
    return;
  }

  send(client_sockfd, PASS, BUFFER_SIZE,0);
  printf("found %s", usr.name);

  recv(client_sockfd, msg, BUFFER_SIZE,0);
  if(!strncmp(usr.pass,msg, USER_INFO_SIZE)){
    send(client_sockfd, PASS, BUFFER_SIZE,0);
    dashboard_main(client_sockfd, &usr);
  }
  else{
    printf("incorrect password\n");
    send(client_sockfd, ERR, BUFFER_SIZE,0);
  }
}

void handle_client_requests(int client_sockfd){
  char string[BUFFER_SIZE];
  while(1){
    recv(client_sockfd, string, BUFFER_SIZE,0);
    printf("msg: %s", string);
    if(!strncmp(string, "new_usr", 7)){
      make_new_user(client_sockfd);
      *string = 0;
    }
    else if (!strncmp(string, "login", 5)){
      login(client_sockfd);
      *string = 0;
    }
  }
}

int sub_main(int client_sockfd){
  int err = open("sub.log", O_CREAT|O_RDWR, 0666);

  dup2(err, 1);
  printf("dfks;");
  handshake(client_sockfd);
  handle_client_requests(client_sockfd);
  
}
