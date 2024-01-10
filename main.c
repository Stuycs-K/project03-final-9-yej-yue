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
        printf("exiting music player\n");
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
        rewind(currSong);
    }
}
int main() {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGTSTP, sighandler);
    signal(SIGCONT, sighandler);
    signal(SIGSTOP, sighandler);
    struct node** playlist = makelib();//but multiple playlists?
    while (1){
        char in[32];
        printf("press 'v' to view the playlist, 'a' to add a song, 'd' to delete song, 's' to shuffle play, 'ctrl+c' to exit\n");
        fgets(in, sizeof(in), stdin);
        // if (strcmp(in, "m")==0){
        //     char num[8];
        //     printf("how many songs would you like to add? (in numbers) \n");
        //     fgets(num, sizeof(num),stdin);
        //     int numsongs = atoi(num);
        //     for (int i = 0; i < numsongs; i++){
        //         //addsong to playlist
        //     }
        // }
        if (strcmp(in, "v")==0){
            print_lib(playlist);
        }
        else if (strcmp(in, "a")==0){
            char info[64];
            printf("song, artist?\n");
            fgets(info, sizeof(info), stdin);
            // add_song(makesong("habits", "tove lo", NULL), playlist);
            //addsong to playlist
        }
        else if (strcmp(in, "d")==0){
            //remove song
        }
        else if (strcmp(in, "s")==0){
            //shuffle
        }
        else {
            printf("try again\n");
        }
    }
}