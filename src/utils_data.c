// utils_data.c - Data directory utility functions
#include "utils_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

// Function to get the proper data directory
char* get_data_dir() {
    static char data_dir[1024];
    char* home_dir = getenv("HOME");
    char* xdg_data_home = getenv("XDG_DATA_HOME");
    
    // If XDG_DATA_HOME is set, use it
    if (xdg_data_home && *xdg_data_home) {
        snprintf(data_dir, sizeof(data_dir), "%s/ccube", xdg_data_home);
    } else if (home_dir) {
        // Fallback to ~/.local/share/ccube
        snprintf(data_dir, sizeof(data_dir), "%s/.local/share/ccube", home_dir);
    } else {
        // Fallback to a default location
        snprintf(data_dir, sizeof(data_dir), "/usr/local/share/ccube");
    }
    
    return data_dir;
}

// Function to create data directory if it doesn't exist
int create_data_dir() {
    char* data_dir = get_data_dir();
    struct stat st = {0};
    
    if (stat(data_dir, &st) == -1) {
        // Directory doesn't exist, create it
        char* parent_dir = strdup(data_dir);
        char* last_slash = strrchr(parent_dir, '/');
        
        if (last_slash) {
            *last_slash = '\0';
            if (stat(parent_dir, &st) == -1) {
                if (mkdir(parent_dir, 0755) == -1) {
                    free(parent_dir);
                    return -1;
                }
            }
        }
        free(parent_dir);
        
        if (mkdir(data_dir, 0755) == -1) {
            return -1;
        }
    }
    
    return 0;
}

// Function to get full path to a data file
char* get_data_file_path(const char* filename) {
    static char full_path[1024];
    char* data_dir = get_data_dir();
    
    snprintf(full_path, sizeof(full_path), "%s/%s", data_dir, filename);
    return full_path;
}
