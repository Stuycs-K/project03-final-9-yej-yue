#include "playlist.h"

struct lists createPlaylist(char* playlistName, struct node* t) {
    struct lists* playlist = calloc(sizeof(struct node*), 27);
    strcpy(playlist->pname, playlistName);
    playlist->song = t;
    return *playlist;
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

void alphabetizePlaylists(char* playlistName, struct node** playlist, struct node** library) {
    struct node** target = findPlaylist(playlistName, playlist);
    if (target != NULL) {
        struct node* temp = *target;
        while (temp != NULL) {
            add_song(temp, library);
            temp = temp-> next;
        }
        *target = free_list(*target);
    } 
    else {
        err(errno, "playlist not found \n");
    }
}