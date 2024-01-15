#include <signal.h>
#include "list.h"
#include "lib.h"
#include "audio.h"
#include "connect.h"
#include "playlist.h"
#include "err.h"

static void sighandler(int signo) {
    if (signo == SIGINT){ 
        //ctrl c
        printf("\nexiting music player \n");
        exit(0);
    }
    // if (signo == SIGCONT){ 
    //     //ctrl q
    //     char song[BUFFER_SIZE];
    //     printf("enter the song title: ");
    //     fgets(song, sizeof(song), stdin);
    //     strtok(song, "\n");    
    //     play(song);
    // }
}

int main() {
    // struct sigaction sa;
    // sa.sa_handler = sighandler;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = 0;

    // if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGCONT, &sa, NULL) == -1) {
    //     err(errno, "error setting up sighandler \n");
    // }

    printf("ready to test \n");

    while (1) {
        char in[32];
        fgets(in, sizeof(in), stdin);
        if (in[strlen(in) - 1] == '\n') {
            in[strlen(in) - 1] = '\0';
        }

        if (strcmp(in, "play") == 0) {
            char song[BUFFER_SIZE];
            printf("enter the song title: ");
            fgets(song, sizeof(song), stdin);
            if (song[strlen(song) - 1] == '\n') {
                song[strlen(song) - 1] = '\0';
            }            
            play(song);
        }
    }

    return 0;
}