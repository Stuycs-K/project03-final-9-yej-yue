#ifndef ERR_H
#define ERR_H
#include <errno.h>
void err(int i, char* message) {
    if (i < 0){
        printf("error %s - %s \n", message, strerror(errno));
        exit(1);
    }
}
#endif