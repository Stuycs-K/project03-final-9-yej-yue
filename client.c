#include "connect.h"

void clientLogic(int server_socket){
  char input[BUFFER_SIZE];
  printf("Enter input: ");
  fgets(input, sizeof(input), stdin);
  write(server_socket, input, sizeof(input));
  read(server_socket, input, sizeof(input));
  printf("Modified: %s\n", input);
}

int main(int argc, char *argv[] ) {
  while(1){
    char* IP = "127.0.0.1";
    if(argc>1){
      IP=argv[1];
    }
    int server_socket = client_tcp_handshake(IP);
    printf("client connected.\n");
    clientLogic(server_socket);
  }
}
