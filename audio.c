#include "audio.h"
#include "list.h"
#include "connect.h"

char currSong[1024] = "";

void play(char* songName) {
    char command[256];
    snprintf(command, sizeof(command), "mpg123 \"./music/%s\"", songName);
    
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

void getCurrSong(char* song) {
    strcpy(song, currSong);
}