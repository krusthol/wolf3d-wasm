#ifndef WAVE_H
# define WAVE_H

# include "delta-2d.h"

typedef struct      s_wave
{
    SDL_AudioSpec   spec;
    Uint8           *sound;
    Uint32          soundlen;
    int             soundpos;
}                   t_wave;

void                close_audio(SDL_AudioDeviceID *device);
void                open_audio(t_wave *wave, SDL_AudioDeviceID *device);
void                reopen_audio(t_wave *wave, SDL_AudioDeviceID *device);

#endif
