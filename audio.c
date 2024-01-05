void err(int i, char* message) {
    if (i < 0) {
        printf("error %s - %s \n", message, strerror(errno));
        exit(1);
    }
}

void initializeSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        err(errno, "SDL could not be initialized");
    }
}