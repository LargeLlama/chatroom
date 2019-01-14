#include "chatroom.h"
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void handshake(int client_sockfd){
  send(client_sockfd, ACK, HANDSHAKE_BUFFER_SIZE, 0);
}
