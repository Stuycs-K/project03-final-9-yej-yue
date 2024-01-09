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