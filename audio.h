#include "list.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>


#ifndef AUDIO_H
#define AUDIO_H

void err(int i, char* message);
void initializeSDL();
void playSong(struct node* song);

#endif