#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"

// allow server to read from multiple clients (include numbered clients)
// check audio functions with mpg123
// fix signals
struct lists** playlistlib;
int playlistcount=0;

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
    struct lists* playl;
    // printf("input server %s\n", input);

    if (i == 0) {
        char* song = strtok(input, ",");//change to strsep
        char* artist = strtok(NULL, "\n");

        add_song(makesong(song, artist, NULL), lib);

        printf("song added: %s, %s\n", song, artist);
    } 
    else if(i==1){//view
        char* playlistname = strtok(input, "\n");//connect playlist name w libs
        printf("%s\n", playlistname);
        struct lists* target = findPlaylist(playlistname, playl);//how to search through????
        print_list(target->song);
        //print_listexcept something with lib
    }
    // else if (i == 2) {
    //     char song[BUFFER_SIZE];
    //     getCurrSong(song);
    //     printf("\"song\" %s is currently being played \n", song);
    // }
    else if (i==2){
        printf("delete playlist or song?\n");
        playlistcount--;
    }
    else if (i == 3) {
        printf("asking for playlist info \n");
        char* playlistName = strtok(input, "\n");
        char* num = strtok(input+strlen(playlistName)+1, "\n");
        int songnum = atoi(num);
        char* song[songnum];
        char* artist[songnum];
        for (int k = 0; k < songnum; k++) {
            song[k] = strtok(NULL, ", ");
            printf("song %s\n", song[k]);
            artist[k] = strtok(NULL, "\n");
            printf("artist %s\n", artist[k]);
        }
        if (playlistcount==0){
            playl = createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL);
        }
        else playl = insertplaylist(createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL), playl);
        for (int k = 1; k<songnum; k++){
            addSong2Playlist(makesong(song[k], artist[k], NULL), playlistName, playl);
        }
        printf("name of playlist: %s\n", playl->pname);
        // *(playlistlib+playlistcount) = playl;
        playlistcount++;//stays 1?
        printf("%d\n", playlistcount);
        print_list(playl->song);
    }
    else if (i==4){//view lib
        int stdoutcopy = dup(STDOUT_FILENO);//only does all this after client exits
        int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        dup2(temp, STDOUT_FILENO);
        print_lib(lib);//why does it only print after client exits???
        char contents[2*BUFFER_SIZE];
        read(temp, contents, sizeof(contents));
        printf("%s\n", contents);
        write(client_socket, contents, sizeof(contents));
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

    // printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip \n");
    // printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song \n \n");
    
    while (1) {
        int client_socket = server_tcp_handshake(listen_socket);
        // printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip\n \n");
        printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song or playlist\n \n");
        char in[32];
        read(client_socket, in, sizeof(in));

        if (fork() == 0) {
            int currClientCount = clientCount++;
            printf("waiting for client %d's command \n", currClientCount);

            if (strcmp(in, "a\n") == 0) {
                printf("asking for song info to add \n");
                subserver_logic(client_socket, lib, 0);
                exit(0);
            }
            else if (strcmp(in, "vplaylist\n")==0){
                printf("printing playlist ");
                subserver_logic(client_socket, lib, 1);
                exit(0);
            }
            else if (strcmp(in, "d\n")==0){
                
            }
            else if (strcmp(in, "m\n")==0){
                subserver_logic(client_socket, lib, 3);
                exit(0);
            }
            else if (strcmp(in, "vlib\n")==0){
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