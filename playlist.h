#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "err.h"

#ifndef PLAYLIST_H
#define PLAYLIST_H

struct node** createPlaylist();
void addSong2Playlist(struct node* song, struct node** playlist);
void printPlaylist(struct node** playlist);
void deletePlaylist(struct node** playlist);

#endif