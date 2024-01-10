#include "list.h"
#include "lib.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef AUDIO_H
#define AUDIO_H

void playSong(struct node* song);
void skipSong(struct node* nextSong);

#endif