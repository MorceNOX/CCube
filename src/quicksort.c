#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Type definition for a comparison function
typedef int (*CompareFunc)(const void*, const void*);

// 1. Generic Swap Function using memcpy
void swap(void *a, void *b, size_t size) {
    void *temp = malloc(size);
    
    if (!temp) return;
    
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    
    free(temp);
}

// 2. Generic Partition Function (Lomuto Scheme)
int partition(void *arr, int low, int high, size_t size, CompareFunc cmp) {
    char *pivot = (char *)arr + (high * size);
    int i = (low - 1);
    
    for (int j = low; j < high; j++) {
        if (cmp((char *)arr + (j * size), pivot) <= 0) {
            i++;
            swap((char *)arr + (i * size), (char *)arr + (j * size), size);
        }
    }
    swap((char *)arr + ((i + 1) * size), (char *)arr + (high * size), size);
    return (i + 1);
}

// 3. Generic Quick Sort Function
void quick_sort_generic(void *arr, int low, int high, size_t size, CompareFunc cmp) {
    if (low < high) {
        int pi = partition(arr, low, high, size, cmp);
        quick_sort_generic(arr, low, pi - 1, size, cmp);
        quick_sort_generic(arr, pi + 1, high, size, cmp);
    }
}


int compare_integers(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    return (int_a > int_b) - (int_a < int_b);
}

int compare_long_long(const void *a, const void *b) {
    long long int_a = *((long long *)a);
    long long int_b = *((long long *)b);
    
    return (int_a > int_b) - (int_a < int_b);
}