#include "playlist.h"

struct node** createPlaylist(char* playlistName) {
    struct node** playlist = calloc(sizeof(struct node*), 27);
    playlist[0] = makesong(playlistName, "", NULL);
    return playlist;
}

struct node** findPlaylist(char* playlistName, struct node** playlist) {
    struct node* temp = playlist[0]-> next;
    while (temp != NULL) {
        if (strcmp(temp-> name, playlistName) == 0) {
            return &temp;
        }
        temp = temp-> next;
    }
    return NULL;
}

void addSong2Playlist(struct node* song, char* playlistName, struct node** playlist) {
    struct node** target = findPlaylist(playlistName, playlist);
    if (target != NULL) {
        *target = insert_front(*target, song-> name, song-> artist);
    } 
    else {
        err(errno, "playlist not found \n");
    }
}

void printPlaylist(char* playlistName, struct node** playlist) {
    struct node** target = findPlaylist(playlistName, playlist);
    if (target != NULL) {
        printf("playlist: %s \n", playlistName);
        print_list(*target);
    } 
    else {
        err(errno, "playlist not found \n");
    }
}

void deletePlaylist(char* playlistName, struct node** playlist) {
    struct node** target = findPlaylist(playlistName, playlist);
    if (target != NULL) {
        *target = free_list(*target);
    } 
    else {
        err(errno, "playlist not found \n");
    }
}