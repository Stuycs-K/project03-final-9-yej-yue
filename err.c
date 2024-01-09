#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void err(int i, char* message) {
    if (i < 0){
        printf("error %s - %s \n", message, strerror(errno));
        exit(1);
    }
}