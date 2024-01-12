#include "list.h"
#include "lib.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AUDIO_H
#define AUDIO_H

extern char currSong[1024];

void play(char* songName);
void ppause();
void skip(struct node* nextSong);
void rrewind(struct node* song);
void getCurrSong(char* song);

#endif