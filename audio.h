#include "list.h"
#include "lib.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AUDIO_H
#define AUDIO_H

void play(struct node* song);
void pause();
void skip(struct node* nextSong);
void rewind(struct node* song);

#endif