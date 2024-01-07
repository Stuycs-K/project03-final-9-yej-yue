#include "connect.h"
#include "lib.h"
#include "list.h"

void subserver_logic(int client_socket, struct node** lib) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));

    if (strncmp(input, "ADD", 3) == 0) {
        char* song = strtok(input + 4, ",");
        char* artist = strtok(NULL, "\n");

        add_song(makesong(song, artist, NULL), lib);

        snprintf(input, sizeof(input), "song added: %s, %s", song, artist);
    } 
    else {
        snprintf(input, sizeof(input), "invalid command");
    }

    write(client_socket, input, sizeof(input));
}

int main(int argc, char* argv[]) {
    int listen_socket = server_setup();
    struct node** lib = makelib();

    while (1) {
        int client_socket = server_tcp_handshake(listen_socket);

        if (fork() == 0) {
            subserver_logic(client_socket, lib);
            exit(0);
        } 
        else {
            close(client_socket);
        }
    }
}