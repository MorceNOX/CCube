#include "utils.h"
#include <stdio.h>
#include <string.h>

#include "quicksort.h"



unsigned short get_terminal_width(void) {
    struct winsize ws;
    // Try STDIN_FILENO, STDOUT_FILENO, and STDERR_FILENO in case one is redirected
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == 0) {
        return ws.ws_col;
    } else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        return ws.ws_col;
    } else if (ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == 0) {
        return ws.ws_col;
    }

    return 80;
}

void replace_char(char *str, char find, char replace) {
    // Iterate through the string until the null-terminating character ('\0') is reached
    for (int i = 0; str[i] != '\0'; i++) {
        // If the current character matches the one to find, replace it
        if (str[i] == find) {
            str[i] = replace;
        }
    }
}

long long min(long long a, long long b) {
    return (a <= b) ? a : b;
}

long long max(long long a, long long b) {
    return (a >= b) ? a : b;
}

double calculate_average(long long *arr, int size) {
    if (size <= 0) return 0.0;
    
    long long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

double calc_mo(int n, long long *arr, int size) {
    if (size <= 0) return 0.0;
    
    // Take the last n elements
    long long last_n[1000];
    int start_idx = (size >= n) ? (size - n) : 0;
    int actual_n = (size >= n) ? n : size;
    
    for (int i = 0; i < actual_n; i++) {
        last_n[i] = arr[start_idx + i];
    }
    
    return calculate_average(last_n, actual_n);

}

double calc_ao(int n, long long *arr, int size) {
    if (size <= 0) return 0.0;
    
    // Take the last n elements
    long long last_n[1000];
    int start_idx = (size >= n) ? (size - n) : 0;
    int actual_n = (size >= n) ? n : size;
    
    for (int i = 0; i < actual_n; i++) {
        last_n[i] = arr[start_idx + i];
    }
    
    // If we don't have enough elements to remove min and max, return normal average
    if (actual_n < 3) {
        return calculate_average(last_n, actual_n);
    }
    
    quick_sort_generic(last_n, 0, actual_n - 1, sizeof(long long), compare_long_long);
    
    // Remove min and max (first and last elements)
    long long sum = 0;
    for (int i = 1; i < actual_n - 1; i++) {
        sum += last_n[i];
    }
    
    // Calculate average
    return (double)sum / (actual_n - 2);
}

double calc_ao_50(int n, long long *arr, int size) {
    if (size <= 0) return 0.0;
    
    if (size < 50) {
        return calc_ao(size, arr, size);
    }
    
    // Take the last 50 elements
    long long last_50[50];
    int start_idx = size - 50;
    
    for (int i = 0; i < 50; i++) {
        last_50[i] = arr[start_idx + i];
    }
    
    quick_sort_generic(last_50, 0, 49, sizeof(long long), compare_long_long);
    
    // Remove min and max (first 3 and last 3 elements)
    long long sum = 0;
    for (int i = 3; i < 47; i++) {
        sum += last_50[i];
    }
    
    // Calculate average
    return (double)sum / 44;
}
