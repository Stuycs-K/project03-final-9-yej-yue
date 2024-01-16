#include <signal.h>
#include "list.h"
#include "lib.h"
#include "audio.h"
#include "connect.h"
#include "playlist.h"
#include "err.h"

static void sighandler(int signo) {
    if (signo == SIGINT){ 
        // ctrl+c
        printf("\nexiting music player \n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, sighandler);

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
        if (strcmp(in, "mplaylist") == 0) {
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
                char artist[50];

                printf("enter song name: ");
                fgets(songName, sizeof(songName), stdin);
                if (songName[strlen(songName) - 1] == '\n') {
                    songName[strlen(songName) - 1] = '\0';
                }

                printf("enter artist name: ");
                fgets(artist, sizeof(artist), stdin);
                if (artist[strlen(artist) - 1] == '\n') {
                    artist[strlen(artist) - 1] = '\0';
                }
                playlist-> song = insert_in_order(makesong(songName, artist, NULL), playlist-> song);
            }
            printf("playlist created successfully! \n");
        }
        if (strcmp(in, "vplaylist") == 0) {
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
        if (strcmp(in, "add2playlist") == 0) {
            char playlistName[100];
            char songName[50];
            char artist[50];

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
            fgets(artist, sizeof(artist), stdin);
            if (artist[strlen(artist) - 1] == '\n') {
                artist[strlen(artist) - 1] = '\0';
            }

            struct lists* target = findPlaylist(playlistName, playlist);
            if (target != NULL) {
                target-> song = insert_in_order(makesong(songName, artist, NULL), target-> song);
                printf("song added to playlist %s successfully! \n", playlistName);
            } 
            else {
                printf("playlist not found \n");
            }        
        }
        if (strcmp(in, "deletefromplaylist") == 0) {
            char playlistName[100];
            char songName[50];
            char artist[50];

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
            fgets(artist, sizeof(artist), stdin);
            if (artist[strlen(artist) - 1] == '\n') {
                artist[strlen(artist) - 1] = '\0';
            }

            struct lists* target = findPlaylist(playlistName, playlist);
            if (target != NULL) {
                target = deletesong(&playlist, playlistName, songName, artist);
                printf("song deleted from playlist %s successfully! \n", playlistName);
            } 
            else {
                printf("playlist not found \n");
            }
        }
        if (strcmp(in, "deleteplaylist") == 0) {
            deletePlaylist(&playlist);
        }
        if (strcmp(in, "playsong") == 0) {
            char song[BUFFER_SIZE];
            printf("enter the song title: ");
            fgets(song, sizeof(song), stdin);
            if (song[strlen(song) - 1] == '\n') {
                song[strlen(song) - 1] = '\0';
            }            
            play(song);
        }
        if (strcmp(in, "add2queue") == 0) {
            char songName[50];
            printf("enter song to add to the queue: ");
            fgets(songName, sizeof(songName), stdin);
            if (songName[strlen(songName) - 1] == '\n') {
                songName[strlen(songName) - 1] = '\0';
            }
            enqueue(songQueue, songName);
            printf("song added to the queue successfully! \n");
        }
        if (strcmp(in, "vqueue") == 0) {
            displayQueue(songQueue);
        }
        if (strcmp(in, "playqueue") == 0) {
            playQueue(songQueue);
        }
        if (strcmp(in, "clearqueue") == 0) {
            clearQueue(songQueue);
            printf("queue cleared successfully \n");
        }
    }
    return 0;
}