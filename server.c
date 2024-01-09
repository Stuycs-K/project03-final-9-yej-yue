#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"

struct node* currSong;
struct node* nextSong;

static void sighandler(int signo) {
    if (signo == SIGINT){//ctrl c
        printf("\nexiting music player\n");
        exit(0);
    }
    if (signo == SIGTSTP){//ctrl z
        pause();
    }
    if (signo == SIGQUIT){//ctrl '\'
        skip(nextSong);
    }
    if (signo == SIGCONT){//ctrl q
        play(currSong);
    }
    if (signo == SIGSTOP){//ctrl s
        rrewind(currSong);
    }
}

void subserver_logic(int client_socket, struct node** lib) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));

    if (strncmp(input, "ADD", 3) == 0) {
        char* song = strtok(input + 4, ",");//change to strsep
        char* artist = strtok(NULL, "\n");

        add_song(makesong(song, artist, NULL), lib);

        printf("song added: %s, %s\n", song, artist);
    } 
    else if(strncmp(input, "VIEW", 4)==0){//view
        char* playlist = strtok(input+8, "\n");//connect playlist name w libs
        printf("%s\n", playlist);
        print_lib(lib);
    }
    else {
        printf("invalid command");
    }

    write(client_socket, input, sizeof(input));
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);
    int listen_socket = server_setup();
    struct node** lib = makelib();
    // struct node*** wholelib = &lib;
    
    while (1) {
        int client_socket = server_tcp_handshake(listen_socket);
        printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip\n \n");
        printf("press 'm' to make a playlist, 'v' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song\n");
        char in[32];
        read(client_socket, in, sizeof(in));
        if (fork() == 0) {
            if (strncmp(in, "a", 1)==0){
                printf("asking for song info to add\n");
                subserver_logic(client_socket, lib);
                exit(0);
            }
            else if (strncmp(in, "v", 1)==0){
                printf("printing playlist ");
                subserver_logic(client_socket, lib);
                exit(0);
            }
            else if (strncmp(in, "d", 1)==0){
                
            }
            else if (strncmp(in, "m", 1)==0){
                
            }
            else if (strncmp(in, "vlib", 4)==0){

            }
        } 
        else {
            close(client_socket);
        }
    }
}