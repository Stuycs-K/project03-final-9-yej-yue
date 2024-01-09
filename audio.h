#include "list.h"
#include "lib.h"
#include "err.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <SDL3/SDL.h>

#ifndef AUDIO_H
#define AUDIO_H

void initializeSDL();
void playSong(struct node* song);
void pauseSong();

#endif