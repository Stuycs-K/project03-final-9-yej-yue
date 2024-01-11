#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "lib.h"
#include "err.h"

#ifndef PLAYLIST_H
#define PLAYLIST_H
// struct lists{
//     struct node** song;
//     char pname[100]; 
// };
struct lists createPlaylist(char* playlistName, struct node* t);
struct node** findPlaylist(char* playlistName, struct node** playlist);
void addSong2Playlist(struct node* song, char* playlistName, struct node** playlist);
void printPlaylist(char* playlistName, struct node** playlist);
void deletePlaylist(char* playlistName, struct node** playlist);
void alphabetizePlaylists(char* playlistName, struct node** playlist, struct node** library);

#endif