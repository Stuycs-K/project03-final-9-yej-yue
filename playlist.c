#include "playlist.h"

struct node** createPlaylist(char* playlistName) {
    struct node** playlist = calloc(sizeof(struct node*), 27);
    playlist[0] = makesong(playlistName, "", NULL);
    return playlist;
}