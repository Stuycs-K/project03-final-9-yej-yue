#include "audio.h"

void initializeSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        err(errno, "SDL could not be initialized \n");
    }
}

void playSong(struct node* song) {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    if (SDL_LoadWAV(s-> file_path, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        err(errno, "SDL_LoadWAV failure \n")
    }

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        err(errno, "SDL_OpenAudioDevice failure \n");
        SDL_FreeWAV(wavBuffer);
    }

    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    SDL_Delay(wavLength / (wavSpec.freq * wavSpec.channels * wavSpec.format));

    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void pauseSong() {
    SDL_PauseAudio(0);
}