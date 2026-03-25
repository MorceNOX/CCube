#ifndef FILE_OPS_H
#define FILE_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

// Function declarations
void close_session(void);
long long* read_numbers_from_file(const char* filename, int* count);
void save_scramble(const char *timestamp, const char *time_str, const char *scramble);
void save_time(long long elapsed_ns);
void print_last_scrambles();

#endif