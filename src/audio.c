#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

// Libao variables
#ifdef USE_LIBAO
#include <ao/ao.h>

static ao_device *audio_device = NULL;
static ao_sample_format audio_format;
static int audio_driver_id = -1;
static int audio_initialized = 0;
static int system_sample_rate = 48000;
static int system_channels = 2;
#endif

// Initialize audio system
void init_audio() {
#ifdef USE_LIBAO
    if (!audio_initialized) {
        ao_initialize();
        audio_driver_id = ao_default_driver_id();
        
        // Set fixed sample rate and channels to avoid channel matrix issues
        // system_sample_rate = 44100;  // Use common rate
        // system_channels = 2;         // Use mono to avoid channel problems
        
        // Set up audio format properly
        memset(&audio_format, 0, sizeof(audio_format));
        audio_format.bits = 16;
        audio_format.rate = system_sample_rate;
        audio_format.channels = system_channels;
        audio_format.byte_format = AO_FMT_LITTLE;
        
        // Explicitly set channel matrix to avoid "unrecognized channel name" errors
        // This is a workaround for the channel matrix corruption issue
        audio_format.matrix = "L,R";  // Explicitly set to NULL to avoid matrix issues
        
        audio_initialized = 1;
    }
#endif
}

// Cleanup audio system
void cleanup_audio() {
#ifdef USE_LIBAO
    if (audio_device) {
        ao_close(audio_device);
        audio_device = NULL;
    }
    if (audio_initialized) {
        ao_shutdown();
        audio_initialized = 0;
    }
#endif
}

// Simple beep using terminal
void beep_sound() {
    printf("");
    fflush(stdout);
}

// Play a musical tone using libao
void play_tone(double frequency, double duration) {
#ifdef USE_LIBAO
    if (!audio_initialized) {
        init_audio();
    }
    
    if (audio_driver_id >= 0) {
        // Open audio device if not already open
        if (!audio_device) {
            // Re-initialize format to ensure clean state
            memset(&audio_format, 0, sizeof(audio_format));
            audio_format.bits = 16;
            audio_format.rate = system_sample_rate;
            audio_format.channels = system_channels;
            audio_format.byte_format = AO_FMT_LITTLE;
            audio_format.matrix = "L,R";  // Explicitly avoid channel matrix issues
            
            audio_device = ao_open_live(audio_driver_id, &audio_format, NULL);
        }
        
        if (audio_device) {
            int sample_rate = audio_format.rate;
            int samples = duration * sample_rate;
            int buffer_size = samples * audio_format.bits / 8 * audio_format.channels;
            char *buffer = malloc(buffer_size);
            
            if (buffer) {
                // Generate sine wave
                for (int i = 0; i < samples; i++) {
                    double t = (double)i / sample_rate;
                    double sample = 0.5 * 32767 * sin(2 * M_PI * frequency * t);
                    
                    // Convert to 16-bit little-endian
                    short sample_val = (short)sample;

                    //if (audio_format.channels == 1) {
                        buffer[i * 2] = buffer[2*i+2] = sample_val & 0xFF;
                        buffer[i * 2 + 1] = buffer[2*i+3] = (sample_val >> 8) & 0xFF;
                    //} else {
                    //    buffer[4*i] = buffer[4*i+2] = sample_val & 0xFF;
		            //    buffer[4*i+1] = buffer[4*i+3] = (sample_val >> 8) & 0xFF;
                    //}
                }
                
                ao_play(audio_device, buffer, buffer_size);
                free(buffer);
            }
        }
    } else {
        // Fallback to terminal beep
        beep_sound();
    }
#else
    // Fallback to terminal beep if libao not available
    beep_sound();
#endif
}

// Play timer start sound with musical notes
void play_timer_start_sound() {
    play_tone(B5, 0.1);  // A4
    usleep(50000);          // 50ms pause
    play_tone(D6, 0.1); // C5
    usleep(50000);          // 50ms pause
    play_tone(Fs6, 0.1); // E5
    usleep(50000);
    play_tone(D6, 0.1); // C5
    usleep(50000);          // 50ms pause
    play_tone(Fs6, 0.2); // E5
}

// Play timer stop sound with descending melody
void play_timer_stop_sound() {
    // Play a pleasant descending melody
    play_tone(B5, 0.1); // C5
    usleep(50000);          // 50ms pause
    play_tone(Fs6, 0.1); // E5
    usleep(50000);          // 50ms pause
    play_tone(D6, 0.1); // C5
    usleep(50000);          // 50ms pause
    play_tone(G6, 0.1); // E5
    usleep(50000);          // 50ms pause
    play_tone(B5, 0.2);  // A4
}


// Play pre-timer start sound with musical notes
void play_pre_timer() {
    // Play a pleasant ascending melody
    play_tone(A7, 0.1);  // A5
    usleep(50000);          // 50ms pause    
}