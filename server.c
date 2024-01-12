#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"

// allow server to read from multiple clients (include numbered clients)
// check audio functions with mpg123
// fix signals
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

struct lists* subserver_logic(int client_socket, struct lists** lib, int i) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));

    if (i == 0) {
        char* song = strtok(input, ", ");
        char* artist = strtok(NULL, ", ");
        char* playlistname = strtok(NULL, "\n");
        printf("added %s by %s to %s\n", song, artist, playlistname);
        addSong2Playlist(makesong(song, artist, NULL), playlistname, *lib);

        printf("song added: %s, %s\n", song, artist);
    } 
    else if(i==1){//view
        char* playlistname = strtok(input, "\n");
        printf("%s\n", playlistname);
        printPlaylist(playlistname, *lib);

        //try make sample playlist and print
        // struct lists* playl = createPlaylist("hi", makesong("hey", "h", NULL), NULL);//haven't put it into lib!!
        // *(lib+playlistcount)=playl;
        // struct lists* found = findPlaylist("hi", *lib);
        // printf("%s\n", found->pname);
        // printPlaylist(found->pname, *lib);

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
        printf("playlists %d\n", playlistcount);
        if (playlistcount==0){
            *lib = createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL);
        }
        else *lib = insertplaylist(createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL), *lib);
        for (int k = 1; k<songnum; k++){
            addSong2Playlist(makesong(song[k], artist[k], NULL), playlistName, *lib);
        }
        printf("name of playlist: %s\n", (*lib)->pname);
        playlistcount++;//stays same?
        printPlaylist(playlistName, *lib);
        // return *lib;
    }
    else if (i==4){//view lib
        int stdoutcopy = dup(STDOUT_FILENO);//only does all this after client exits
        int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        dup2(temp, STDOUT_FILENO);
        // print_lib(lib);//why does it only print after client exits???
        char contents[2*BUFFER_SIZE];
        read(temp, contents, sizeof(contents));
        printf("%s\n", contents);
        write(client_socket, contents, sizeof(contents));
    }
    else {
        err(errno, "invalid command \n");
    }
    // write(client_socket, input, sizeof(input));
    // struct lists* temp = *lib;
    // printf("playlist %s\n", temp->pname); doesn't even do this.
    return *lib;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);

    int listen_socket = server_setup();
    struct node** library = makelib();
    int clientCount = 1;
    struct lists** playlistlib = calloc(50, sizeof(struct lists*));

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
                *playlistlib = subserver_logic(client_socket, playlistlib, 0);
                exit(0);
            }
            else if (strcmp(in, "vplaylist\n")==0){
                // printf("%s\n", (*playlistlib)->pname);
                printf("printing playlist ");
                *playlistlib = subserver_logic(client_socket, playlistlib, 1);
                // printPlaylist("hi", *playlistlib);
                exit(0);
            }
            else if (strcmp(in, "d\n")==0){
                
            }
            else if (strcmp(in, "m\n")==0){
                *playlistlib = subserver_logic(client_socket, playlistlib, 3);
                // printPlaylist("hi", *playlistlib);
                struct lists* temp = *playlistlib;
                // printf("playlist %s\n", temp->pname);
                // printf("playlist %s\n", (*playlistlib)->pname); doesn't do this
                exit(0);
            }
            else if (strcmp(in, "vlib\n")==0){
                *playlistlib = subserver_logic(client_socket, playlistlib, 4);
                // print_lib(lib);
                exit(0);
            }
        } 
        else {
            wait(NULL);
            // printf("%s\n", (*playlistlib)->pname);
            close(client_socket);
        }
    }
}