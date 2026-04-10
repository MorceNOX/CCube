#include "scramble.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// Direction arrays
char DIRECTIONS[] = {'B', 'D', 'F', 'L', 'R', 'U'};
char OPPOSITE_DIR[] = {'F', 'U', 'B', 'R', 'L', 'D'};
char MODIFIERS[] = {' ', '\'', '2'};

// Function to generate a random number between 0 and max-1
int random_int(int max) {
    return rand() % max;
}

void generate_scramble(char *scramble) {
    scramble[0] = '\0';
    char prev_prev_dir = '\0';
    char prev_dir = '\0';
    char movements[N_SCRAMBLES][4]; // 20 movements, max 4 chars each

    for (int i = 0; i < N_SCRAMBLES; i++) {
        // Select random direction
        int n = random_int(6);
        char direction = DIRECTIONS[n];

        // Check for consecutive moves or opposite direction
        while ((direction == prev_dir) ||
               (prev_dir != '\0' && direction == prev_prev_dir && prev_dir == OPPOSITE_DIR[n])) {
            n = random_int(6);
            direction = DIRECTIONS[n];
        }

        if (i >= 1) {
            prev_prev_dir = prev_dir;
        }
        prev_dir = direction;

        // Select random modifier
        int m = random_int(3);
        char modifier = MODIFIERS[m];

        // Format movement
        if (modifier == ' ') {
            snprintf(movements[i], sizeof(movements[i]), "%c ", direction);
        } else if (modifier == '\'') {
            snprintf(movements[i], sizeof(movements[i]), "%c'", direction);
        } else {
            snprintf(movements[i], sizeof(movements[i]), "%c2", direction);
        }

        // Add to scramble
        if (i > 0) {
            strcat(scramble, " ");
        }
        strcat(scramble, movements[i]);
    }
}

void split_scramble(const char *full_scramble, char *scrambleA, char *scrambleB, char *scrambleC) {
    scrambleA[0] = '\0';
    scrambleB[0] = '\0';
    scrambleC[0] = '\0';
    
    char *token = strtok((char*)full_scramble, " ");
    int i = 0;
    
    while (token != NULL && i < N_SCRAMBLES) {
        if (i < 9) {
            if (strlen(scrambleA) >= 0) strcat(scrambleA, " ");
            strcat(scrambleA, token);
        } else if (i < 17) {
            if (strlen(scrambleB) >= 0) strcat(scrambleB, " ");
            strcat(scrambleB, token);
        } else {
            if (strlen(scrambleC) >= 0) strcat(scrambleC, " ");
            strcat(scrambleC, token);
        }
        i++;
        token = strtok(NULL, " ");
    }
}

void get_scramble(const char *full_scramble, char *scramble) {
    scramble = '\0';
    
    char *token = strtok((char*)full_scramble, " ");
    int i = 0;
    
    while (token != NULL && i < N_SCRAMBLES) {
        if (strlen(scramble) > 0) strcat(scramble, " ");
        strcat(scramble, token);
        
        i++;
        token = strtok(NULL, " ");
    }
}
