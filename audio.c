#include "list.h"
#include "audio.h"

void playSong(struct node* song) {
    char command[256];
    strcpy(command, "mpg123 \"");
    strcat(command, song-> name);
    strcat(command, "\"");
    
    if (system(command) == -1) {
        err(errno, "error playing the song \n");
    }
}

void pauseSong() {
    if (system("pkill -STOP mpg123") == -1) {
        err(errno, "error pausing the song \n");
    }
    printf("song paused \n");
}

void skipSong(struct node* nextSong) {
    if (system("pkill -KILL mpg123") == -1) {
        err(errno, "error pausing the song \n");
    }
    playSong(nextSong);
    printf("song skipped \n");
}