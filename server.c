#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"

// allow server to read from multiple clients (include numbered clients)
// check audio functions with mpg123
// fix signals

static void sighandler(int signo) {
    if (signo == SIGINT){//ctrl c
        printf("\nexiting music player \n");
        exit(0);
    }
    if (signo == SIGTSTP){//ctrl z
        pause();
    }
    // if (signo == SIGQUIT){//ctrl '\'
    //     skip(nextSong);
    // }
    if (signo == SIGCONT){//ctrl q
        char song[BUFFER_SIZE];
        printf("song %s is currently being played \n", song);
    }
    // if (signo == SIGSTOP){//ctrl s
    //     rrewind(currSong);
    // }
}

void subserver_logic(int client_socket, struct node** lib, int i) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));
    // printf("input server %s\n", input);

    if (i == 0) {
        char* song = strtok(input, ",");//change to strsep
        char* artist = strtok(NULL, "\n");

        add_song(makesong(song, artist, NULL), lib);

        printf("song added: %s, %s\n", song, artist);
    } 
    else if(i==1){//view
        char* playlist = strtok(input, "\n");//connect playlist name w libs
        printf("%s\n", playlist);
        //print_list();//except something with lib
    }
    else if (i == 2) {
        char song[BUFFER_SIZE];
        getCurrSong(song);
        printf("\"song\" %s is currently being played \n", song);
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
        struct lists playl = createPlaylist(playlistName, makesong(song[0], artist[0], NULL));
        for (int k = 0; k < songnum; k++) {
            song[k] = strtok(NULL, ", ");
            printf("song %s\n", song[k]);
            artist[k] = strtok(NULL, "\n");
            printf("artist %s\n", artist[k]);
            // add_song(makesong(song[k], artist[k], NULL), playlist);
        }
        // struct node* playlist = makesong(song[0], artist[0], NULL);
        // add_song(makesong(song[0], artist[0], NULL), lib);
        
        for (int k = 1; k<songnum; k++){
            // lib[0] = insert_in_order(makesong(song[k], artist[k], NULL), lib[0]);
            // add_song(makesong(song[k], artist[k], NULL), lib);
            //change these to adding to playlist not to lib
        }
        printf("%s\n", playl.pname);
        print_list(playl.song);
        // print_list(lib[0]);//how to make playlist inherently part of lib
    }
    else if (i==4){//view lib
        // int stdoutcopy = dup(STDOUT_FILENO);
        // int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        // dup2(temp, STDOUT_FILENO);
        print_lib(lib);
        // write(client_socket, temp, sizeof(temp));
    }
    else {
        err(errno, "invalid command \n");
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
    int clientCount = 1;

    printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip \n");
    printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song \n \n");
    
    while (1) {
        int client_socket = server_tcp_handshake(listen_socket);

        char in[32];
        read(client_socket, in, sizeof(in));

        if (fork() == 0) {
            int currClientCount = clientCount++;
            printf("waiting for client %d's command \n", currClientCount);

            if (strcmp(in, "a") == 0) {
                printf("asking for song info to add \n");
                subserver_logic(client_socket, lib, 0);
                exit(0);
            }
            else if (strcmp(in, "vplaylist")==0){
                printf("printing playlist \n");
                subserver_logic(client_socket, lib, 1);
                exit(0);
            }
            else if (strcmp(in, "d")==0){
                
            }
            else if (strcmp(in, "m")==0){
                subserver_logic(client_socket, lib, 3);
                exit(0);
            }
            else if (strcmp(in, "vlib")==0){
                subserver_logic(client_socket, lib, 4);
                print_lib(lib);
                exit(0);
            }
        } 
        else {
            close(client_socket);
        }
    }
}