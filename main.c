#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
static void sighandler(int signo) {
    if (signo == SIGINT){//ctrl c
        printf("exiting music player\n");
        exit(0);
    }
    if (signo == SIGSTOP){//ctrl z
        //pause?
    }
}
int main() {
    signal(SIGINT, sighandler);
    signal(SIGSTOP, sighandler);
    while (1){
        char in[32];
        printf("press 'm' to make a playlist, 'a' to add a song, 'd' to delete song, 's' to shuffle play\n");
        fgets(in, sizeof(in), stdin);
        if (strcmp(in, "m")==0){
            struct node** playlist = makelib();
            char num[8];
            printf("how many songs would you like to add? (in numbers) \n");
            fgets(num, sizeof(num),stdin);
            int numsongs = atoi(num);
            for (int i = 0; i < numsongs; i++){
                
            }
        }
        //if m, ask how many songs to add then later they can adjust by adding or deleting
    }
}