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