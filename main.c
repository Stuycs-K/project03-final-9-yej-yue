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
    if (signo == SIGCONT){ 
        //ctrl q
        char song[BUFFER_SIZE];
        printf("enter the song title: ");
        fgets(song, sizeof(song), stdin);
        strtok(song, "\n");    
        play(song);
    }
}

int main() {
    printf("ready to test \n");
    while (1) {
        signal(SIGINT, sighandler);
        signal(SIGCONT, sighandler);
    }
}