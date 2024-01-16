#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include "list.h"
#include "lib.h"
#include "audio.h"
#include "connect.h"
#include "playlist.h"
#include "err.h"

void displayFileInfo(const char* filePath) {
    struct stat fileStat;
    if (stat(filePath, &fileStat) == 0) {
        printf("file: %s \n", filePath);
        printf("size: %lld bytes \n \n", fileStat.st_size);
    } 
    else {
        err(errno, "error getting file information \n");
    }
}

static void sighandler(int signo) {
    if (signo == SIGINT) { 
        // ctrl+c
        printf("\nexiting music player \n");
        exit(0);
    }
    if (signo == SIGQUIT) { 
        // 'ctrl+\'
        const char *directoryPath = "./music";
        DIR *dir = opendir(directoryPath);
        printf("music folder files' data");
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_type == DT_REG) {
                    char filePath[256]; 
                    snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, entry->d_name);
                    displayFileInfo(filePath);
                }
            }
            closedir(dir);
        } 
        else {
            err(errno, "error opening directory \n");
        }
    }
}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);

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

    struct lists* playlist = NULL;
    struct queue* songQueue = createQueue();
    printf("enter 'vlib' to view library, 'mplaylist' to make a playlist, 'vplaylist' to view a playlist, 'add2playlist' to add a song to a playlist, ");
    printf("'deletefromplaylist' to delete a song from playlist, 'deleteplaylist' to delete a playlist, 'playsong' to play a song',"); 
    printf("'add2queue' to add a song to the queue, 'vqueue' to view the queue, 'playqueue' to play the queue, and 'clearqueue' to clear the queue\n");
    while (1) {
        printf("enter a command: ");

        char in[50];
        fgets(in, sizeof(in), stdin);
        if (in[strlen(in) - 1] == '\n') {
            in[strlen(in) - 1] = '\0';
        }

        if (strcmp(in, "vlib") == 0) {
            print_lib(library);
        }
        else if (strcmp(in, "mplaylist") == 0) {
            char playlistName[50];
            int numSongs;

            printf("enter playlist name: ");
            fgets(playlistName, sizeof(playlistName), stdin);
            if (playlistName[strlen(playlistName) - 1] == '\n') {
                playlistName[strlen(playlistName) - 1] = '\0';
            }

            printf("enter the number of songs: ");
            scanf("%d", &numSongs);
            getchar(); 

            playlist = createPlaylist(playlistName, NULL, playlist);

            for (int i = 0; i < numSongs; i++) {
                char songName[50];
                char artistName[50];

                printf("enter song name: ");
                fgets(songName, sizeof(songName), stdin);
                if (songName[strlen(songName) - 1] == '\n') {
                    songName[strlen(songName) - 1] = '\0';
                }

                printf("enter artist name: ");
                fgets(artistName, sizeof(artistName), stdin);
                if (artistName[strlen(artistName) - 1] == '\n') {
                    artistName[strlen(artistName) - 1] = '\0';
                }

                struct node* toadd = makesong(songName, artistName, NULL);
                // struct node* a = search_song(artistName, songName, library);
                // printf("%s\n", a->artist);
                // if (a != NULL){
                //     playlist-> song = insert_in_order(toadd, playlist-> song);
                // }
                // else{
                //     printf("invalid song\n");
                // }
                playlist-> song = insert_in_order(toadd, playlist-> song);
            }
            printf("playlist created successfully! \n");
        }
        else if (strcmp(in, "vplaylist") == 0) {
            char playlistName[100];

            printf("existing playlist(s): \n");
            printAllPlaylists(playlist);

            printf("enter the playlist name to view: ");
            fgets(playlistName, sizeof(playlistName), stdin);
            if (playlistName[strlen(playlistName) - 1] == '\n') {
                playlistName[strlen(playlistName) - 1] = '\0';
            }     

            struct lists* target = findPlaylist(playlistName, playlist);
            if (target != NULL) {
                printf("playlist %s: \n", playlistName);
                printPlaylist(playlistName, &playlist);
            }  
            else {
                printf("playlist not found \n");
            }
        }
        else if (strcmp(in, "add2playlist") == 0) {
            char playlistName[100];
            char songName[50];
            char artistName[50];

            printf("existing playlist(s): \n");
            printAllPlaylists(playlist);

            printf("enter the playlist name: ");
            fgets(playlistName, sizeof(playlistName), stdin);
            if (playlistName[strlen(playlistName) - 1] == '\n') {
                playlistName[strlen(playlistName) - 1] = '\0';
            } 

            printf("enter song name: ");
            fgets(songName, sizeof(songName), stdin);
            if (songName[strlen(songName) - 1] == '\n') {
                songName[strlen(songName) - 1] = '\0';
            }

            printf("enter artist name: ");
            fgets(artistName, sizeof(artistName), stdin);
            if (artistName[strlen(artistName) - 1] == '\n') {
                artistName[strlen(artistName) - 1] = '\0';
            }

            struct lists* target = findPlaylist(playlistName, playlist);
            if (target != NULL) {
                    struct node* toadd = makesong(songName, artistName, NULL);
                    // if (search_song(toadd->artist, toadd->name, library)!=NULL){
                    //     target-> song = insert_in_order(toadd, target-> song);
                    // }
                    // else{
                    //     printf("invalid song\n");
                    // }
                    target-> song = insert_in_order(toadd, target-> song);
                printf("song added to playlist %s successfully! \n", playlistName);
            } 
            else {
                printf("playlist not found \n");
            }        
        }
        else if (strcmp(in, "deletefromplaylist") == 0) {
            char playlistName[100];
            char songName[50];
            char artistName[50];

            printf("existing playlist(s): \n");
            printAllPlaylists(playlist);

            printf("enter the playlist name: ");
            fgets(playlistName, sizeof(playlistName), stdin);
            if (playlistName[strlen(playlistName) - 1] == '\n') {
                playlistName[strlen(playlistName) - 1] = '\0';
            } 

            printf("enter song name: ");
            fgets(songName, sizeof(songName), stdin);
            if (songName[strlen(songName) - 1] == '\n') {
                songName[strlen(songName) - 1] = '\0';
            }

            printf("enter artist name: ");
            fgets(artistName, sizeof(artistName), stdin);
            if (artistName[strlen(artistName) - 1] == '\n') {
                artistName[strlen(artistName) - 1] = '\0';
            }

            struct lists* target = findPlaylist(playlistName, playlist);
            if (target != NULL) {
                target = deletesong(&playlist, playlistName, songName, artistName);
                printf("song deleted from playlist %s successfully! \n", playlistName);
            } 
            else {
                printf("playlist not found \n");
            }
        }
        else if (strcmp(in, "deleteplaylist") == 0) {
            deletePlaylist(&playlist);
        }
        else if (strcmp(in, "playsong") == 0) {
            char song[BUFFER_SIZE];
            printf("enter the song title: ");
            fgets(song, sizeof(song), stdin);
            if (song[strlen(song) - 1] == '\n') {
                song[strlen(song) - 1] = '\0';
            }            
            play(song);
        }
        else if (strcmp(in, "add2queue") == 0) {
            char songName[50];
            printf("enter song to add to the queue: ");
            fgets(songName, sizeof(songName), stdin);
            if (songName[strlen(songName) - 1] == '\n') {
                songName[strlen(songName) - 1] = '\0';
            }
            enqueue(songQueue, songName);
            printf("song added to the queue successfully! \n");
        }
        else if (strcmp(in, "vqueue") == 0) {
            displayQueue(songQueue);
        }
        else if (strcmp(in, "playqueue") == 0) {
            playQueue(songQueue);
        }
        else if (strcmp(in, "clearqueue") == 0) {
            clearQueue(songQueue);
            printf("queue cleared successfully \n");
        }
        else {
            printf("invalid command\n");
        }
    }
    return 0;
}