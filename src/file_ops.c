#include "file_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <ctype.h>
#include "utils_data.h"


void close_session() {
    char* scrambles_file_ptr = get_data_file_path("scrambles.txt");
    char scrambles_file[1024];
    strcpy(scrambles_file, scrambles_file_ptr);

    char* times_file_ptr = get_data_file_path("times.txt");
    char times_file[1024];
    strcpy(times_file, times_file_ptr);   
    
    // Check if both files exist by trying to open them
    FILE* f1 = fopen(scrambles_file, "r");
    FILE* f2 = fopen(times_file, "r");
    
    if (!f1 && !f2) {
        printf("No session files to close.\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return;
    }
    
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    
    // Find next available number (000-099)
    int available_numbers[100] = {0}; // 0 = available, 1 = taken
    
    // Check existing files in data directory for prefixes
    char* data_dir = get_data_dir();
    DIR* dir = opendir(data_dir);
    if (dir) {
        struct dirent* entry;
        
        while ((entry = readdir(dir)) != NULL) {
            // Check if file name starts with 3 digits followed by underscore
            if (strlen(entry->d_name) >= 4 && 
                isdigit(entry->d_name[0]) && 
                isdigit(entry->d_name[1]) && 
                isdigit(entry->d_name[2]) && 
                entry->d_name[3] == '_') {
                
                // Extract the prefix (first 3 characters)
                char prefix[4];
                prefix[0] = entry->d_name[0];
                prefix[1] = entry->d_name[1];
                prefix[2] = entry->d_name[2];
                prefix[3] = '\0';
                
                int prefix_num = atoi(prefix);
                if (prefix_num >= 0 && prefix_num <= 99) {
                    available_numbers[prefix_num] = 1; // Mark as taken
                }
            }
        }
        closedir(dir);
    }
    
    // Find the first available number
    int next_number = 0;
    for (int i = 0; i < 100; i++) {
        if (available_numbers[i] == 0) {
            next_number = i;
            break;
        }
    }
    
    // Format the number with leading zeros
    char prefix[4];
    snprintf(prefix, sizeof(prefix), "%03d", next_number);
    
    // Create new names with prefix
    char new_scrambles_name[1024];
    char new_times_name[1024];
    
    snprintf(new_scrambles_name, sizeof(new_scrambles_name), "%s/%s_scrambles.txt", data_dir, prefix);
    snprintf(new_times_name, sizeof(new_times_name), "%s/%s_times.txt", data_dir, prefix);
    
    // Debug information
    printf("\nChecking files before renaming:\n");
    printf("  Original scrambles file: %s\n", scrambles_file);
    printf("  Original times file: %s\n", times_file);
    printf("  Prefix to use: %s\n", prefix);
    printf("  New scrambles file: %s\n", new_scrambles_name);
    printf("  New times file: %s\n", new_times_name);
    
    // Rename the files
    int result1 = 0;
    int result2 = 0;
    
    // Try to rename scrambles.txt
    if (access(scrambles_file, F_OK) == 0) {
        result1 = rename(scrambles_file, new_scrambles_name);
        if (result1 == 0) {
            printf("✓ Successfully renamed scrambles.txt to %s_scrambles.txt\n", prefix);
        } else {
            printf("✗ Failed to rename scrambles.txt: ");
            perror("");
        }
    } else {
        printf("⚠ scrambles.txt doesn't exist\n");
    }
    
    // Try to rename times.txt
    if (access(times_file, F_OK) == 0) {
        result2 = rename(times_file, new_times_name);
        if (result2 == 0) {
            printf("✓ Successfully renamed times.txt to %s_times.txt\n", prefix);
        } else {
            printf("✗ Failed to rename times.txt: ");
            perror("");
        }
    } else {
        printf("⚠ times.txt doesn't exist\n");
    }
    
    if (result1 == 0 || result2 == 0) {
        printf("Session closed successfully with prefix %s\n", prefix);
    }
}


/**
 * Reads integers from a file, with one or more integers per line (space/newline separated).
 * 
 * @param filename The name of the file to read.
 * @param count A pointer to an integer that will store the number of elements read.
 * @return A dynamically allocated array of integers, or NULL on failure.
 */
long long* read_numbers_from_file(const char* filename, int* count) {
    // Get full path to the file
    char* full_path = get_data_file_path(filename);
    
    FILE* file = fopen(full_path, "r");
    if (file == NULL) {
        perror("No times saved yet...");
        return NULL;
    }

    long long* numbers = NULL;
    int capacity = 100; // Initial capacity
    *count = 0;

    numbers = (long long*)malloc(capacity * sizeof(long long));
    if (numbers == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    long long num;
    // Read formatted input from the file
    while (fscanf(file, "%lld", &num) == 1) {
        if (*count >= capacity) {
            // Double the capacity if the array is full
            capacity *= 2;
            long long* temp = (long long*)realloc(numbers, capacity * sizeof(long long));
            if (temp == NULL) {
                perror("Memory re-allocation failed");
                free(numbers);
                fclose(file);
                return NULL;
            }
            numbers = temp;
        }
        numbers[(*count)++] = num;
    }

    // Close the file
    fclose(file);

    // Optional: Re-allocate to the exact size to save memory
    if (*count > 0) {
        long long* temp = (long long*)realloc(numbers, (*count) * sizeof(long long));
        if (temp != NULL) {
            numbers = temp;
        }
    }

    return numbers;
}

void f_print_scramble( int fd, const char *text ) {
    char c=' ';
    for (int i = 0; i < 67; i++ ) {

        if ( text[i] != '\0' )     
            dprintf(fd, "%c", text[i]);
            
        if (( text[i] == '\'' ) || ( text[i] == '2' )) {
            dprintf(fd, "%s", " ");
            
        } else if ( ( text[i] == ' ' ) 
        ) {
            dprintf(fd, "%s", " ");
            
        } else if ( ( text[i] == '\0' ) 
        ) {
            dprintf(fd, "%s", " ");
            
        }
        c = text[i];  
    }
    if ( c == '\0' ) {
        dprintf(fd, "%s", " ");
    }
    if ( c == ' ' ) {
        dprintf(fd, "%s", " ");
    }   
}

void save_scramble(const char *timestamp, const char *time_str, const char *scramble) {
    // Create data directory if it doesn't exist
    create_data_dir();
    
    // Get full path to the scrambles file
    char* scrambles_file = get_data_file_path("scrambles.txt");
    
    // First, read existing scrambles
    FILE *file = fopen(scrambles_file, "r");
    char existing_lines[20][512];  // 20 lines max
    int line_count = 0;
    
    if (file) {
        while (line_count < 19 && fgets(existing_lines[line_count], 512, file)) {
            line_count++;
        }
        fclose(file);
    }
    
    // Write new scramble to temporary file
    char temp_file[] = "scrambles.tmp.XXXXXX";
    int fd = mkstemp(temp_file);
    if (fd != -1) {
        // Write new scramble first
        dprintf(fd, "%s\t%s\t", timestamp, time_str);
        
        f_print_scramble(fd, scramble);
        dprintf(fd, "\n");
        
        // Write existing scrambles
        for (int i = 0; i < line_count; i++) {
            dprintf(fd, "%s", existing_lines[i]);
        }
        
        close(fd);
        
        // Move temporary file to final location
        rename(temp_file, scrambles_file);
    }
}

void save_time(long long elapsed_ns) {
    // Create data directory if it doesn't exist
    create_data_dir();
    
    // Get full path to the times file
    char* times_file = get_data_file_path("times.txt");
    
    // Read existing times
    FILE *file = fopen(times_file, "r");
    long long existing_times[100];
    int time_count = 0;
    
    if (file) {
        while (time_count < 99 && fscanf(file, "%lld", &existing_times[time_count]) == 1) {
            time_count++;
        }
        fclose(file);
    }
    
    // Write to temporary file
    char temp_file[] = "times.tmp.XXXXXX";
    int fd = mkstemp(temp_file);
    if (fd != -1) {
        // Write new time first
        dprintf(fd, "%lld\n", elapsed_ns);
        
        // Write existing times
        for (int i = 0; i < time_count; i++) {
            dprintf(fd, "%lld\n", existing_times[i]);
        }
        
        close(fd);
        
        // Move temporary file to final location
        rename(temp_file, times_file);
    }
}

void print_last_scrambles() {
    // Get full path to the scrambles file
    char* scrambles_file = get_data_file_path("scrambles.txt");
    
    FILE *file = fopen(scrambles_file, "r");
    if (!file) return;
    
    char line[512];
    int line_count = 0;
    
    printf("\033[35m");
    printf("\nLast 12 scrambles:\n");
    printf("───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    
    // Read all lines into array
    char lines[12][512];
    int count = 0;
    
    // Read up to 12 lines
    while (fgets(line, 512, file) && count < 12) {
        strcpy(lines[count], line);
        count++;
    }
    
    // Print in reverse order (most recent first)
    for (int i = 0; i <= count - 1; i++) {
        if ( i % 2 == 0 )
           printf("\033[35m");
        else
           printf("\033[0m");

        printf("%s", lines[i]);
    }
    
    fclose(file);
    printf("───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
    printf("\033[0m");
}