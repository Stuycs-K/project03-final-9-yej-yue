#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include "list.h"
#include "lib.h"
#include "connect.h"
#include "audio.h"
static void sighandler(int signo) {
    if (signo == SIGINT){//ctrl c
        printf("exiting music player\n");
        exit(0);
    }
    if (signo == SIGSTOP){//ctrl z
        //pause?
    }
}
int main() {
    signal(SIGINT, sighandler);
    signal(SIGSTOP, sighandler);
}