#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"

static void sighandler(int signo) {
    if (signo == SIGINT){//ctrl c
        printf("\n %d exiting music player\n", getpid());
        exit(0);
    }
    // if (signo == SIGTSTP){//ctrl z
    //     pause();
    // }
    // if (signo == SIGQUIT){//ctrl '\'
    //     skip(nextSong);
    // }
    // if (signo == SIGCONT){//ctrl q
    //     play(currSong);
    // }
    // if (signo == SIGSTOP){//ctrl s
    //     rrewind(currSong);
    // }
}
void clientLogic(int server_socket) {
    char input[BUFFER_SIZE];
    char song[BUFFER_SIZE];
    char artist[BUFFER_SIZE];
    char out[32];
    printf("enter letter:\n");
    fgets(out, sizeof(out), stdin);
    write(server_socket, out, sizeof(out));
    if (strncmp(out, "a", 1)==0){
        printf("enter song name: ");
        fgets(song, sizeof(song), stdin);
        strtok(song, "\n"); 

        printf("enter artist name: ");
        fgets(artist, sizeof(artist), stdin);
        strtok(artist, "\n"); 

        printf("ADDED %s, %s\n", song, artist);

        write(server_socket, input, sizeof(input));
        read(server_socket, input, sizeof(input));
        printf("modified: %s \n", input);
    }
    else if (strncmp(in, "v", 1)==0){
        printf("viewing playlist:\n");
    }
    else if (strncmp(in, "d", 1)==0){
        
    }
    else if (strncmp(in, "s", 1)==0){
        
    }
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);
    while (1) {
        char* IP = "127.0.0.1";
        if (argc > 1) {
            IP = argv[1];
        }
        int server_socket = client_tcp_handshake(IP);
        printf("client %d connected \n", getpid());
        clientLogic(server_socket);
    }
}