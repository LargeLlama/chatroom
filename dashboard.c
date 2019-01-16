#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dashboard_main(int client_sockfd){
  int logged_in = 1;
  char string[BUFFER_SIZE];
  
  while(logged_in){
    recv(client_sockfd, string, BUFFER_SIZE,0);
    if
  }
}
