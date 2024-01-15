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
        // play(song);    
        // sendSong(server_socket, song);
    }
    // if (signo == SIGSTOP){//ctrl s
    //     rrewind(currSong);
    // }
}
void clientLogic(int server_socket) {
    char input[2*BUFFER_SIZE];
    char song[BUFFER_SIZE];
    char artist[BUFFER_SIZE];
    char playlist[BUFFER_SIZE];
    char* str;
    char out[32];
    printf("enter command:\n");
    fgets(out, sizeof(out), stdin);
    if (out[strlen(out) - 1] == '\n') {
        out[strlen(out) - 1] = '\0';
    }
    write(server_socket, out, sizeof(out));
    if (strncmp(out, "a", 1)==0){
        printf("which playlist? ");
        fgets(playlist, sizeof(playlist), stdin);
        strtok(playlist, "\n");

        printf("enter song name: ");
        fgets(song, sizeof(song), stdin);
        strtok(song, "\n"); 

        printf("enter artist name: ");
        fgets(artist, sizeof(artist), stdin);
        strtok(artist, "\n"); 

        printf("ADDED %s, %s to %s\n", song, artist, playlist);
        str = malloc(strlen(song)+strlen(artist)+strlen(playlist)+4);
        if (str != NULL){
            strcat(str, song);
            strcat(str, ", ");
            strcat(str, artist);
            strcat(str, ", ");
            strcat(str, playlist);
        }
        // printf("input: %s\n", str);
        write(server_socket, str, strlen(str)+1);
        read(server_socket, str, strlen(str)+1);
        // printf("modified: %s \n", str);
    }
    if (strncmp(out, "vplaylist", 9)==0){
        printf("enter playlist name:\n");
        fgets(playlist, sizeof(playlist), stdin);
        printf("VIEWING %s\n", playlist);
        write(server_socket, playlist, sizeof(playlist));
    }
    if (strncmp(out, "d", 1)==0){
        char plist[BUFFER_SIZE];
        char songtodelete[BUFFER_SIZE];
        char singa[BUFFER_SIZE];
        printf("delete playlist or song?\n");
        fgets(input, sizeof(input), stdin);
        printf("(from) which playlist? \n");
        fgets(plist, sizeof(plist), stdin);
        str = malloc(strlen(input)+strlen(plist)+strlen(songtodelete)+strlen(singa)+4);
        if (str != NULL){
            strcat(str, input);
            // strcat(str, ", ");
            strcat(str, plist);
            // strcat(str, ", ");
            // printf("printing to server %s\n", str);
        }
        if (strncmp(input, "song", 4)==0){
            printf("which song? \n");
            fgets(songtodelete, sizeof(songtodelete), stdin);
            printf("by who? \n");
            fgets(singa, sizeof(singa), stdin);
            strcat(str, songtodelete);
            strcat(str, singa);
            // printf("new printing to server %s\n", str);
        }
        // fgets(songtodelete, sizeof(songtodelete), stdin);
        // str = malloc(strlen(input)+strlen(plist)+strlen(songtodelete)+4);
        write(server_socket, str, strlen(str)+1);
    }
    if (strncmp(out, "m", 1)==0){
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
    if (strncmp(out, "vlib", 4)==0){
        read(server_socket, input, sizeof(input));
        printf("%s\n", input);
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