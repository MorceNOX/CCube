#ifndef AUDIO_H
#define AUDIO_H

// Define if we want to use libao
#define USE_LIBAO

#ifdef USE_LIBAO
#include <ao/ao.h>
#endif
#include "notes.h"

// Function declarations for audio functionalities
void init_audio();
void cleanup_audio();
void beep_sound();
void play_tone(double frequency, double duration);
void play_timer_start_sound();
void play_timer_stop_sound();
void play_pre_timer();

#endif // AUDIO_H