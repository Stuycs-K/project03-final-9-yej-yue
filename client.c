#include "connect.h"
#include "lib.h"
#include "list.h"

void clientLogic(int server_socket) {
    char input[BUFFER_SIZE];
    char song[BUFFER_SIZE];
    char artist[BUFFER_SIZE];

    printf("enter song name: ");
    fgets(song, sizeof(song), stdin);
    strtok(song, "\n"); 

    printf("enter artist name: ");
    fgets(artist, sizeof(artist), stdin);
    strtok(artist, "\n"); 

    snprintf(input, sizeof(input), "ADD %s, %s", song, artist);

    write(server_socket, input, sizeof(input));
    read(server_socket, input, sizeof(input));
    printf("modified: %s \n", input);
}

int main(int argc, char* argv[]) {
    while (1) {
        char* IP = "127.0.0.1";
        if (argc > 1) {
            IP = argv[1];
        }
        int server_socket = client_tcp_handshake(IP);
        printf("client connected \n");
        clientLogic(server_socket);
    }
}