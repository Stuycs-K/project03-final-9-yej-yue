#include "list.h"
#include "audio.h"

void play(struct node* song) {
    char command[256];
    strcpy(command, "mpg123 \"");
    strcat(command, song-> name);
    strcat(command, "\"");
    
    if (system(command) == -1) {
        err(errno, "error playing the song \n");
    }
}

void ppause() {
    if (system("pkill -STOP mpg123") == -1) {
        err(errno, "error pausing the song \n");
    }
    printf("song paused \n");
}

void skip(struct node* nextSong) {
    if (system("pkill -KILL mpg123") == -1) {
        err(errno, "error skipping the song \n");
    }
    play(nextSong);
    printf("song skipped \n");
}

void rrewind(struct node* song) {
    if (system("pkill -KILL mpg123") == -1) {
        err(errno, "error rewinding the song \n");
    }
    play(song);
    printf("song rewound \n");
}