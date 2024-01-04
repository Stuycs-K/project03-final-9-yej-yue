#include "connect.h"

void subserver_logic(int client_socket){
  char input[BUFFER_SIZE];
  read(client_socket, input, sizeof(input));
  printf("modifying %s(rot13)\n", input);
  for (int i = 0; i < strlen(input); i++) {//rot13
    if (input[i] - 13 < 'a') input[i] += 13;
    else input[i] -= 13;
  }
  printf("sending modified: %s\n", input);
  write(client_socket, input, sizeof(input));
}

int main(int argc, char *argv[] ) { 
  int listen_socket = server_setup(); 
  while (1) {
    int client_socket = server_tcp_handshake(listen_socket);


    if (fork() == 0) {
      subserver_logic(client_socket);
      exit(0);
    }
    else {
      close(client_socket);

    }
  }
}
