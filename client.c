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
  send(sockfd, ACK, HANDSHAKE_BUFFER_SIZE, 0);
  recv(sockfd, string, HANDSHAKE_BUFFER_SIZE, 0);
}

void new_usr_form(int sockfd){
  char string[BUFFER_SIZE];

  printf("   What's your name?:");
  fgets(string, BUFFER_SIZE, stdin);

  string[strlen(string)-1] = 0;
  send(sockfd, string, BUFFER_SIZE, 0);

  printf("   Enter new password:");

  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = 0;
  send(sockfd, string, BUFFER_SIZE, 0);

  printf("   User created!\n");
}

void login_form(int sockfd){
  char string[BUFFER_SIZE];
  char name[BUFFER_SIZE]; 

  printf("   Enter username: ");
  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = 0;

  send(sockfd, string, BUFFER_SIZE, 0);
  recv(sockfd, string, BUFFER_SIZE, 0);

  if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
    printf("   User does not exist\n");
    return;
  }

  printf("   Enter password: ");

  fgets(string, BUFFER_SIZE, stdin);
  string[strlen(string)-1] = 0;

  send(sockfd, string, BUFFER_SIZE, 0);
  recv(sockfd, string, BUFFER_SIZE, 0);
  if(!strncmp(string, ERR, SUCCESS_SIG_SIZE)){
    printf("   Incorrect password\n");
    return;
  }

  printf("   Login successful!\n");
  user_home(sockfd);

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

  printf("Thank you for choosing CoderzConnect Lite\n");
  if(connect(sockfd, serverinfo->ai_addr, serverinfo->ai_addrlen)){
    printf("Unable to connect. Verify the address provided is correct\n");
    printf("Usage:\n");
    printf("        ./client addr\n");
    printf("                 ^ ip address of server\n");
    return 1;
  }
  
  printf("[CLIENT] Connected!\n");
  
  printf("Welcome to CoderzConnect--The back page of the internet:\n");
  printf("Here are some commands to get you started:\n");
  printf("    new user -- follow the prompts to make a new account with us\n");
  printf("    login ----- follow prompts to sign in and go to your dashboard\n");
  printf("    quit ------ our way of saying farewell\n\n" );
  
  printf("[CLIENT] Connected!\n");
  client_handshake(sockfd);

  char string[BUFFER_SIZE];
  char receive[BUFFER_SIZE];

  while(1){
    printf("[CLIENT] ");
    fgets(string, BUFFER_SIZE, stdin);

    if(!strncmp(string, "new user", 8)){
      send(sockfd, string, BUFFER_SIZE, 0);
      new_usr_form(sockfd);
    }

    if(!strncmp(string, "login", 5)){
      send(sockfd, string, BUFFER_SIZE, 0);
      login_form(sockfd);
    }

    if(!strncmp(string, "quit", 4)){
      send(sockfd, string, BUFFER_SIZE, 0);
      printf("Goodbye!\n");
      return 0;
    }


  }

}
