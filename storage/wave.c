#include "delta-2d.h"

void    close_audio(SDL_AudioDeviceID *dev)
{
    if (dev != 0) {
        SDL_CloseAudioDevice(*dev);
        *dev = 0;
    }
}

void    open_audio(t_wave *wave, SDL_AudioDeviceID *dev)
{
    *dev = SDL_OpenAudioDevice(NULL, SDL_FALSE, &wave->spec, NULL, 0);
    if (!dev) {
        SDL_FreeWAV(wave->sound);
        error_exit("Couldn't open audio device.\n", 1);
    }
    SDL_PauseAudioDevice(*dev, SDL_FALSE);
}

void    reopen_audio(t_wave *wave, SDL_AudioDeviceID *device)
{
    close_audio(device);
    open_audio(wave, device);
}
