#include "connect.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address) {//getaddrinfo, socket, connect

  //getaddrinfo
  struct addrinfo * hints, * results;//results is allocated in getaddrinfo
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo(server_address, PORT, hints, &results); 
  //create the socket
  int serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(serverd, "socket not created client");
  //connect to the server
  bind(serverd, results->ai_addr, results->ai_addrlen);
  connect(serverd, results->ai_addr, results->ai_addrlen);
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){//accept
    int client_socket;
    //listen_socket is clientd of server_setup
    //accept the client connection
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    err(client_socket, "socket not accepted server");
    return client_socket;
}

/*Create and bind a socket.
* Place the socket in a listening state.
*/
int server_setup() {//getaddrinfo, socket, bind, listen

  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, PORT, hints, &results);  //Server sets node to NULL

  //create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);//socket descriptor
  err(clientd, "socket not created server");

  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt error");
  
  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);
  //set socket to listen state
  listen(clientd, 10);
  // int client_socket;
  // socklen_t sock_size;
  // struct sockaddr_storage client_address;
  // sock_size = sizeof(client_address);
  // client_socket = accept(clientd,(struct sockaddr *)&client_address, &sock_size);

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
