#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <locale.h>

// Define if we want to use libao
#define USE_LIBAO

#ifdef USE_LIBAO
#include <ao/ao.h>
#endif

// Include audio functions
#include "audio.h" // Include the audio functions

// Timer-related functions
long long get_elapsed_time(struct timespec start_time);
void set_conio_mode();
void reset_terminal_mode();
void clearInputBuffer();
char* get_strtime(long long nanoseconds);
char* get_strseconds(long long nanoseconds);
char get_decimal_separator();
int get_timer_color(long long elapsed_ns, double ao5, double ao12, int ao_count);

#endif // TIMER_H