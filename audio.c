#include "audio.h"
#include "list.h"
#include "connect.h"

char currSong[1024] = "";

void play(char* songName) {
    pid_t pid = fork();

    if (pid == -1) {
        err(errno, "error forking process \n");
    } 
    else if (pid == 0) {
        chdir("./music");
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s.mp3", songName);
        char* command[] = {"mpg123", filePath, NULL};
        execvp("mpg123", command);
        err(errno, "error executing command \n");
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            err(errno, "error waiting for child process \n");
        }
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
    //play(nextSong);
    printf("song skipped \n");
}

void rrewind(struct node* song) {
    if (system("pkill -KILL mpg123") == -1) {
        err(errno, "error rewinding the song \n");
    }
    //play(song);
    printf("song rewound \n");
}

void getCurrSong(char* song) {
    strcpy(song, currSong);
}