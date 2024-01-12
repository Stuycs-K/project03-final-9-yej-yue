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
    if (signo == SIGCONT){//ctrl q
        char song[BUFFER_SIZE];
        printf("enter the song title: ");
        fgets(song, sizeof(song), stdin);
        strtok(song, "\n");
        play(song);    
        sendSong(server_socket, song);
    }
    // if (signo == SIGSTOP){//ctrl s
    //     rrewind(currSong);
    // }
}
void clientLogic(int server_socket) {
    char input[BUFFER_SIZE];
    char song[BUFFER_SIZE];
    char artist[BUFFER_SIZE];
    char playlist[BUFFER_SIZE];
    char* str;
    char out[32];
    printf("enter command:\n");
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
        str = malloc(strlen(song)+strlen(artist)+4);
        if (str != NULL){
            strcat(str, song);
            strcat(str, ", ");
            strcat(str, artist);
        }
        // printf("input: %s\n", str);
        write(server_socket, str, strlen(str)+1);
        read(server_socket, str, strlen(str)+1);
        // printf("modified: %s \n", str);
    }
    else if (strncmp(out, "vplaylist", 9)==0){
        printf("enter playlist name:\n");
        fgets(playlist, sizeof(playlist), stdin);
        printf("VIEWING %s\n", playlist);
        write(server_socket, playlist, sizeof(playlist));
    }
    else if (strncmp(out, "d", 1)==0){
        
    }
    else if (strncmp(out, "m", 1)==0){
        printf("name for playlist: \n");
        fgets(playlist, sizeof(playlist), stdin);
        printf("how many songs? \n");
        fgets(input, sizeof(input), stdin);
        int num = atoi(input);
        str = malloc(BUFFER_SIZE);
        if (str != NULL){
            strcat(str, playlist);
            // strcat(str, ", ");
            strcat(str, input);
            // strcat(str, "\n");
        }
        for (int i = 0; i<num; i++){
            printf("enter song name: ");
            fgets(song, sizeof(song), stdin);
            strtok(song, "\n"); 

            printf("enter artist name: ");
            fgets(artist, sizeof(artist), stdin);
            strtok(artist, "\n"); 

            strcat(str, song);
            strcat(str, ", ");
            strcat(str, artist);
            strcat(str, "\n");
        }
        write(server_socket, str, strlen(str)+1);

    }
    else if (strncmp(out, "vlib", 4)==0){

    }
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);
    
    int clientCount = 1;

    while (1) {
        char* IP = "127.0.0.1";
        if (argc > 1) {
            IP = argv[1];
        }
        int server_socket = client_tcp_handshake(IP);
        printf("client [%d] %d connected \n", clientCount, getpid());
        clientLogic(server_socket);
    }
    int currClientCount = clientCount++;
}