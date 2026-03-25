#include "timer.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>
#include <termios.h>
#include <locale.h>
#include <stdint.h>

// Global structure to save original terminal parameters
struct termios orig_termios;

char get_decimal_separator() {
    setlocale(LC_NUMERIC, "");

    struct lconv *loc = localeconv();

    // The decimal_point member of the lconv structure holds the separator character
    // It's a string, so we can access the first character.
    char decimal_separator = loc->decimal_point[0];

    return decimal_separator;
}


long long get_elapsed_time(struct timespec start_time) {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    
    return (current_time.tv_sec - start_time.tv_sec) * 1000000000LL +
           (current_time.tv_nsec - start_time.tv_nsec);
}

void set_conio_mode() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(reset_terminal_mode); // Ensure terminal is reset on exit

    new_termios = orig_termios;
    // Disable canonical mode (line buffering) and echo
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    // Set stdin to non-blocking
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK); 
}

void reset_terminal_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void clearInputBuffer() {
    int c;
    // Read and discard characters until a newline or end-of-file (EOF) is encountered
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

char* get_strtime(long long nanoseconds) {
    static char str_time[20];
    
    long long seconds = nanoseconds / 1000000000LL;
    long long minutes = (long long)(seconds / 60);
    long long seconds_part = (long long)(seconds % 60);
    long long milliseconds = (long long)((nanoseconds % 1000000000LL) / 1000000);
    
    sprintf(str_time, "%02lld:%02lld%c%03lld", minutes, seconds_part, get_decimal_separator(), milliseconds);
    return str_time;
}

char* get_strseconds(long long nanoseconds) {
    static char str_time[20];
    
    long long seconds = nanoseconds / 1000000000LL;
    long long seconds_part = (long long)(seconds % 60);
    
    sprintf(str_time, "%02lld", seconds_part);
    return str_time;
}

int get_timer_color(long long elapsed_ns, double ao5, double ao12, int ao_count) {
    if (ao_count < 5)
        return 32;
    
    // Compare against the better of AO5 or AO12
    // You can change this to use AO12 if you prefer
    double comparison_time = ao5;
    
    // If AO12 is available and better than AO5, use AO12
    if (ao12 > 0 && ao12 < ao5) {
        comparison_time = ao12;
    }
    
    // If current time is greater than the comparison time, return red (31)
    // Otherwise, return green (32)
    return (elapsed_ns > (long long)comparison_time) ? 31 : 32;
}
