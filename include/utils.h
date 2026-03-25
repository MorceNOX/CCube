#ifndef UTILS_H
#define UTILS_H

#include "quicksort.h"

void replace_char(char *str, char find, char replace);
long long min(long long a, long long b);
long long max(long long a, long long b);
double calculate_average(long long *arr, int size);
double calc_mo(int n, long long *arr, int size);
double calc_ao(int n, long long *arr, int size);
double calc_ao_50(int n, long long *arr, int size);

#endif
