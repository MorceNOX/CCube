#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*CompareFunc)(const void*, const void*);

void swap(void *a, void *b, size_t size);
int partition(void *arr, int low, int high, size_t size, CompareFunc cmp);
void quick_sort_generic(void *arr, int low, int high, size_t size, CompareFunc cmp);
int compare_long_long(const void *a, const void *b);
int compare_integers(const void *a, const void *b);

#endif
