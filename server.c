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

void subserver_logic(int client_socket, struct node** lib, int i) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));
    // printf("%s\n", input);

    if (i == 0) {
        char* song = strtok(input, ",");//change to strsep
        char* artist = strtok(NULL, "\n");

        add_song(makesong(song, artist, NULL), lib);

        printf("song added: %s, %s\n", song, artist);
    } 
    else if(i==1){//view
        char* playlist = strtok(input+8, "\n");//connect playlist name w libs
        printf("%s\n", playlist);
        print_list(playlist);//except playlist name
    }
    else if (i == 3) {
        printf("asking for playlist info \n");
        char* playlistName = strtok(input, "\n");
        // printf("%s\n", playlistName);

        // *playlist = (struct node*)malloc(sizeof(struct node));
        // (*playlist)->name = malloc(strlen(playlistName) + 1);
        // strcpy((*playlist)->name, playlistName);//but *playlist->name is name of song in playlist
        // printf("%s\n", (*playlist)->name);

        char* num = strtok(input+strlen(playlistName)+1, "\n");
        // printf("%s\n",num);
        int songnum = atoi(num);
        char* song[songnum];
        char* artist[songnum];
        for (int k = 0; k < songnum; k++) {
            song[k] = strtok(NULL, ", ");
            printf("song %s\n", song[k]);
            artist[k] = strtok(NULL, "\n");
            printf("artist %s\n", artist[k]);
            // add_song(makesong(song[k], artist[k], NULL), playlist);
        }
        struct node* playlist = makesong(song[0], artist[0], NULL);
        for (int k = 1; k<songnum; k++){
            playlist = insert_in_order(makesong(song[k], artist[k], NULL), playlist);
        }
        print_list(playlist);
    }
    else if (i==4){//view lib
        // int stdoutcopy = dup(STDOUT_FILENO);
        // int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        // dup2(temp, STDOUT_FILENO);
        print_lib(lib);
        // write(client_socket, temp, sizeof(temp));
    }
    else {
        printf("invalid command");
    }

    // write(client_socket, input, sizeof(input));
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);
    int listen_socket = server_setup();
    struct node** lib = makelib();
    
    while (1) {
        int client_socket = server_tcp_handshake(listen_socket);
        printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip\n \n");
        printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song\n");
        char in[32];
        read(client_socket, in, sizeof(in));
        if (fork() == 0) {
            if (strncmp(in, "a", 1)==0){
                printf("asking for song info to add\n");
                subserver_logic(client_socket, lib, 0);
                exit(0);
            }
            else if (strncmp(in, "vplaylist", 9)==0){
                printf("printing playlist \n");
                subserver_logic(client_socket, lib, 1);
                exit(0);
            }
            else if (strncmp(in, "d", 1)==0){
                
            }
            else if (strncmp(in, "m", 1)==0){
                subserver_logic(client_socket, lib, 3);
                exit(0);
            }
            else if (strncmp(in, "vlib", 4)==0){
                subserver_logic(client_socket, lib, 4);
                exit(0);
            }
        } 
        else {
            close(client_socket);
        }
    }
}