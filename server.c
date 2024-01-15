#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
#include "playlist.h"
#include "err.h"
#include <sys/shm.h>
#define key 111111
#define key1 111112

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

struct lists* subserver_logic(int client_socket, struct lists** lib, int i, int count) {
    char input[BUFFER_SIZE];
    read(client_socket, input, sizeof(input));
    printf("input %s\n", input);

    if (i == 0) {
        char* song = strtok(input, ", ");
        char* artist = strtok(NULL, ", ");
        char* playlistname = strtok(NULL, "\n");
        printf("adding %s by %s to %s\n", song, artist, playlistname);
        addSong2Playlist(makesong(song, artist, NULL), playlistname, *lib);
        printf("song added: %s, %s\n", song, artist);
        // printPlaylist(playlistname, *lib);
    } 
    else if(i==1){//view
        char* playlistname = strtok(input, "\n");
        printf("%s\n", playlistname);
        printPlaylist(playlistname, lib);
    }
    else if (i==2){
        char* pOrS = strtok(input, "\n");
        char* playlistname = strtok(NULL, "\n");
        // printf("%s %s\n", pOrS, playlistname);
        if(strcmp(pOrS, "playlist")==0){
            deletePlaylist(playlistname, *lib);
            count--;//if playlist
            printf("playlist count from inside subserver %d\n", count);
            printf("new:\n");
            printallplaylist(lib);
        }
        else if (strcmp(pOrS, "song")==0){
            char* song = strtok(NULL, "\n");
            char* artist = strtok(NULL, "\n");
            struct lists** templib = lib;
            deletesong(templib, playlistname, song, artist);
            printf("new:\n");
            printPlaylist(playlistname, lib);//or do i not need templib
        }
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
        printf("playlists %d\n", count);
        if (count==0){
            *lib = createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL);
        }
        else *lib = insertplaylist(createPlaylist(playlistName, makesong(song[0], artist[0], NULL), NULL), *lib);
        for (int k = 1; k<songnum; k++){
            addSong2Playlist(makesong(song[k], artist[k], NULL), playlistName, *lib);
        }
        printf("name of playlist: %s\n", (*lib)->pname);
        printPlaylist(playlistName, lib);
    }
    else if (i==4){//view lib
        int stdoutcopy = dup(STDOUT_FILENO);//only does all this after client exits
        int temp = open("tempfile", O_RDWR | O_CREAT | O_TRUNC, 0777);
        dup2(temp, STDOUT_FILENO);
        printallplaylist(lib);
        char contents[2*BUFFER_SIZE];
        read(temp, contents, sizeof(contents));
        dup2(stdoutcopy, STDOUT_FILENO);
        printf("%s\n", contents);
        write(client_socket, contents, sizeof(contents));
    }
    else {
        err(errno, "invalid command \n");
    }
    printf("end of subserver\n");
    // write(client_socket, input, sizeof(input));
    return *lib;
}

int main(int argc, char* argv[]) {
    
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);

    int listen_socket = server_setup();
    // struct node** library = makelib();
    int clientCount = 1;
    struct lists** playlistlib = calloc(50, sizeof(struct lists*));
    *playlistlib = createPlaylist("hi", makesong("aldf", "b", NULL), NULL);
    *playlistlib = insertplaylist(createPlaylist("a", makesong("a", "f", NULL), NULL), *playlistlib);
    *playlistlib = insertplaylist(createPlaylist("b", makesong("s", "f", NULL), NULL), *playlistlib);
    addSong2Playlist(makesong("fd", "dg", NULL), "b", *playlistlib);
    *playlistlib = deletesong(playlistlib, "b", "fd", "dg");
    *playlistlib = insertplaylist(createPlaylist("z", makesong("s", "f", NULL), NULL), *playlistlib);
    printallplaylist(playlistlib);
    printf("done print all\n");

    struct node** library = makelib();
    add_song(makesong("505", "arctic monkeys", NULL), library);
    add_song(makesong("agora hills", "doja cat", NULL), library);
    add_song(makesong("awkward", "sza", NULL), library);
    add_song(makesong("delicate", "taylor swift", NULL), library);
    add_song(makesong("die for you", "the weeknd", NULL), library);
    add_song(makesong("maniac", "conan gray", NULL), library);
    add_song(makesong("miracle aligner", "the last shadow puppets", NULL), library);
    add_song(makesong("obsessed", "mariah carey", NULL), library);
    add_song(makesong("sugar", "maroon 5", NULL), library);
    add_song(makesong("this side of paradise", "coyote theory", NULL), library);

    int pcountShmid;
    int* PSCp;
    //trying two different shared mem things instead of one shared mem block
    pcountShmid = shmget(key, sizeof(int), IPC_CREAT|0644);
    err(pcountShmid, "pcount shmget didn't work in main\n");
    PSCp = shmat(pcountShmid, 0, 0);
    *PSCp = 0;
    int listsShmid;
    listsShmid = shmget(key1, 6000, IPC_CREAT|0644);
    err(listsShmid, "lists shmget didn't work in main\n");


    while (1) {
        int childPCshmid;
        childPCshmid = shmget(key, sizeof(int), 0);
        int* childPSCp;
        err(childPCshmid, "shmget didn't work in while\n");
        childPSCp = shmat(childPCshmid, 0, 0);

        int childLshmid;
        childLshmid = shmget(key1, 6000, 0);
        struct lists** childLSp;
        err(childLshmid, "list shmget didn't work in while\n");
        childLSp = shmat(childLshmid, 0, 0);
        printf("waiting for client\n");
        int client_socket = server_tcp_handshake(listen_socket);
        
        // printf("\nKEYBOARD COMMANDS: 'ctrl+c' to exit, 'ctrl+q' to play, 'ctrl+z' to pause, 'ctrl+s' to rewind, 'ctrl+\\' to skip\n \n");
        printf("press 'm' to make a playlist, 'vplaylist' to view a specific playlist, 'vlib' to view library, 'a' to add a song, 'd' to delete song or playlist\n \n");
        char in[32];
        read(client_socket, in, sizeof(in));
        if (in[strlen(in) - 1] == '\n') {
            in[strlen(in) - 1] = '\0';
        }
        
        if (fork() == 0) {
            int currClientCount = clientCount++;
            printf("waiting for client %d's command \n", currClientCount);

            if (strcmp(in, "a") == 0) {
                printf("asking for song info to add \n");
                *childLSp = subserver_logic(client_socket, childLSp, 0, *childPSCp);
                exit(0);
            }
            if (strcmp(in, "vplaylist")==0){
                printf("printing playlist ");
                *playlistlib = subserver_logic(client_socket, childLSp, 1, *childPSCp);
                exit(0);
            }
            if (strcmp(in, "d")==0){
                *childLSp = subserver_logic(client_socket, childLSp, 2, *childPSCp);
                exit(0);
            }
            if (strcmp(in, "m")==0){
                *childLSp = subserver_logic(client_socket, childLSp, 3, *childPSCp);
                // *childLSp += (*childPSCp)*sizeof(struct lists*);
                (*childPSCp)++;
                printf("playlist count %d\n", *childPSCp);
                // *childLSp = *playlistlib;
                printf("playlist name %s\n", (*childLSp)->pname);
                printf("song? %s\n", ((*childLSp)->song)->name);
                // printallplaylist(childLSp);
                // *childLSp -= ((*childPSCp)-1)*sizeof(struct lists*);
                exit(0);
            }
            if (strcmp(in, "vlib")==0){
                print_lib(library);
                //*playlistlib = subserver_logic(client_socket, childLSp, 4, *childPSCp);
                //exit(0);
            }
        } 
        else {
            wait(NULL);
            printf("outside of fork playlist count %d\n", *childPSCp);
            printallplaylist(childLSp);
            printf("outside of fork playlist name %s\n", (*childLSp)->pname);//empty?????
            shmdt(childPSCp);
            shmdt(childLSp);
            close(client_socket);
        }
    }
    shmctl(pcountShmid, IPC_RMID, 0);
    shmctl(listsShmid, IPC_RMID, 0);
}