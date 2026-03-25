#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <stddef.h>
#include <unistd.h>
#include "utils.h"
#include "timer.h"

#define MAX_LINE_LENGTH 2048

// ASCII art for letters
char *B_7lines[] = {
    "    ",
    "▛▀▖ ",
    "▙▄▘ ",
    "▌ ▌ ",
    "▀▀  ",
    "    ",
    "    "
};

char *D_7lines[] = {
    "    ",
    "▛▀▖ ",
    "▌ ▌ ",
    "▌ ▌ ",
    "▀▀  ",
    "    ",
    "    "
};

char *F_7lines[] = {
    "    ",
    "▛▀▘ ",
    "▙▄  ",
    "▌   ",
    "▘   ",
    "    ",
    "    "
};

char *L_7lines[] = {
    "    ",
    "▌   ",
    "▌   ",
    "▌   ",
    "▀▀▘ ",
    "    ",
    "    "
};

char *R_7lines[] = {
    "    ",
    "▛▀▖ ",
    "▙▄▘ ",
    "▌▚  ",
    "▘ ▘ ",
    "    ",
    "    "
};

char *U_7lines[] = {
    "    ",
    "▌ ▌ ",
    "▌ ▌ ",
    "▌ ▌ ",
    "▝▀  ",
    "    ",
    "    "
};

char *TWO_7lines[] = {
    "    ",
    "▞▀▖ ",
    " ▗▘ ",
    "▗▘  ",
    "▀▀▘ ",
    "    ",
    "    "
};

char *prime_7lines[] = {
    "    ",
    "▞   ",
    "    ",
    "    ",
    "    ",
    "    ",
    "    "
};

char *space_7lines[] = {
    "    ",
    "    ",
    "    ",
    "    ",
    "    ",
    "    ",
    "    "
};

char *point_7lines[] = {
    "    ",
    "    ",
    "    ",
    "    ",
    " ▀  ",
    "    ",
    "    "
};

// ASCII art for numbers (12 lines each)
char *zero_12lines[] = {
    "           ",
    "  ░████    ",
    " ░██ ░██   ",
    "░██ ░████  ",
    "░██░██░██  ",
    "░████ ░██  ",
    " ░██ ░██   ",
    "  ░████    ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *one_12lines[] = {
    "           ",
    "  ░██      ",
    "░████      ",
    "  ░██      ",
    "  ░██      ",
    "  ░██      ",
    "  ░██      ",
    "░██████    ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *two_12lines[] = {
    "           ",
    " ░██████   ",
    "░██   ░██  ",
    "      ░██  ",
    "  ░█████   ",
    " ░██       ",
    "░██        ",
    "░████████  ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *three_12lines[] = {
    "           ",
    " ░██████   ",
    "░██   ░██  ",
    "      ░██  ",
    "  ░█████   ",
    "      ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *four_12lines[] = {
    "           ",
    "   ░████   ",
    "  ░██ ██   ",
    " ░██  ██   ",
    "░██   ██   ",
    "░█████████ ",
    "     ░██   ",
    "     ░██   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *five_12lines[] = {
    "           ",
    "░████████  ",
    "░██        ",
    "░███████   ",
    "      ░██  ",
    "░██   ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *six_12lines[] = {
    "           ",
    " ░██████   ",
    "░██   ░██  ",
    "░██        ",
    "░███████   ",
    "░██   ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *seven_12lines[] = {
    "           ",
    "░█████████ ",
    "░██    ░██ ",
    "      ░██  ",
    "     ░██   ",
    "    ░██    ",
    "    ░██    ",
    "    ░██    ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *eight_12lines[] = {
    "           ",
    " ░██████   ",
    "░██   ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "░██   ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *nine_12lines[] = {
    "           ",
    " ░██████   ",
    "░██   ░██  ",
    "░██   ░██  ",
    " ░███████  ",
    "      ░██  ",
    "░██   ░██  ",
    " ░██████   ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *dot_12lines[] = {
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "    ░██    ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *comma_12lines[] = {
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "    ░██    ",
    "     ░█    ",
    "    ░█     ",
    "           ",
    "           "
};

char *colon_12lines[] = {
    "           ",
    "           ",
    "           ",
    "           ",
    "    ░██    ",
    "           ",
    "           ",
    "    ░██    ",
    "           ",
    "           ",
    "           ",
    "           "
};

char *space_12lines[] = {
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           ",
    "           "
};


char print_scramble( const char *text ) {
    char c=' ';
    
    for (int i = 0; i < 59; i++ ) {
        
        if ( text[i] != '\0' )
            c = text[i]; 
            
        printf("%c", text[i]);
            
        if (( text[i] == '\'' ) || ( text[i] == '2' )) {
            c = text[i]; 
            printf(" ");
            
        } else if ( ( text[i] == ' ' ) 
        ) {
            c = text[i]; 
            printf(" ");
            
        } else if ( ( text[i] == '\0' ) 
        ) {
            printf("");            
        }         
    }
    
    printf("   \b\b");

    return c;
}


void create_box(const char *text) {
    int width = strlen(text) + 4;
    
    // Top border
    printf("┌");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┐\n");
    
    // Text line
    printf("│ %s │\n", text);
    
    // Bottom border
    printf("└");
    for (int i = 0; i < width - 2; i++) {
        printf("─");
    }
    printf("┘\n");
}


// Function to create a box around text
void create_box_scramble(const char *text) {
    setlocale(LC_ALL, "");

    int width = 63;

    // Top border
    printf("\033[32m");
    printf("┌");
    for (int i = 0; i < width; i++) {
        printf("─");
    }
    printf("┐\n");

    // Text line
    //printf("│ %s │\n", text);
    printf("│ ");
       
    printf("\033[32;41m");
    printf(" ");
    char c = print_scramble( text );

   if (( c == '\'' ) || ( c == '2' ))
        printf("  \b\b\b");
    else
        printf(" ");
    
    printf("\033[0m");
    printf("\033[32m");
    printf(" │     \n");

    // Bottom border
    printf("└");
    for (int i = 0; i < width; i++) {
        printf("─");
    }
    printf("┘\n");
    printf("\033[0m");
}

void create_boxes(char* words[], int count) {
    // Calculate width for each box
    int widths[100];
    for (int i = 0; i < count; i++) {
        widths[i] = strlen(words[i]) + 4;
    }
    
    // Top border
    for (int i = 0; i < count; i++) {
        printf("┌");
        for (int j = 0; j < widths[i] - 2; j++) {
            printf("─");
        }
        printf("┐\t");
    }
    printf("\n");
    
    // Text line
    for (int i = 0; i < count; i++) {
        printf("│ %s │\t", words[i]);
    }
    printf("\n");
    
    // Bottom border
    for (int i = 0; i < count; i++) {
        printf("└");
        for (int j = 0; j < widths[i] - 2; j++) {
            printf("─");
        }
        printf("┘\t");
    }
    printf("\n");
}

// Function to create multiple boxes
void create_boxes_times(char* words[], int count) {
    // Calculate width for each box
    int widths[100];
    for (int i = 0; i < count; i++) {
        widths[i] = strlen(words[i]) + 4;
    }
    
    // Top border
    for (int i = 0; i < count; i++) {
        printf("┌");
        for (int j = 0; j < widths[i] - 2; j++) {
            printf("─");
        }
        printf("┐\t");
    }
    printf("\n");
    
    // Text line
    for (int i = 0; i < count; i++) {
        int bg_color = 44;
        int fg_color = 33;
        int bg_color2 = 43;
        int fg_color2 = 94;
        if ( i == count - 1 ) {
            bg_color = 43;
            fg_color = 34;
            bg_color2 = 44;
            fg_color2 = 33;
        }
        printf("\033[0m\033[%dm│\033[1;%d;%dm %s \033[0;%d;%dm\033[0m\033[%dm│\t", fg_color2, fg_color, bg_color, words[i], fg_color2, bg_color2, fg_color2);
    }
    printf("\n");
    
    // Bottom border
    for (int i = 0; i < count; i++) {
        printf("└");
        for (int j = 0; j < widths[i] - 2; j++) {
            printf("─");
        }
        printf("┘\t");
    }
    printf("\n");
}


void print_average_times(int ao_count, double ao5, double ao12, double ao50, double mo3, double n_best) {

    printf("\033[1m");
    printf("\rAverage times for this session:\n");
    printf("───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");

    printf("\033[0m");
    printf("\033[40m");

    char strao5[20];
    char strao12[20];
    char strao50[20];
    char strmo3[20];
    char strbest[20];

    strcpy(strao5, get_strtime((long long)ao5));
    strcpy(strao12, get_strtime((long long)ao12));
    strcpy(strao50, get_strtime((long long)ao50));
    strcpy(strmo3, get_strtime((long long)mo3));
    strcpy(strbest, get_strtime((long long)n_best));
    
    char* aoStr[5] = {
                        strao5, 
                        strao12,
                        strao50,
                        strmo3,
                        strbest
                    };
    
    printf("\033[0;34m");
    printf("   ao5 (%#2d)       ao12 (%#2d)       ao50 (%#2d)       mo3 (%#2d)        \033[33mBEST TIME\n", min(5, ao_count), min(12, ao_count), min(50, ao_count), min(3, ao_count));
    
    printf("\033[1;94m");
    create_boxes_times( aoStr, 5 );
    
    printf("\033[0m");

}




// Print ASCII art for letters
void print_letter(const char *letter) {
    setlocale(LC_ALL, "");
    char *letter_array[7];
    
    // Initialize result lines
    char lines[7][MAX_LINE_LENGTH];
    for (int i = 0; i < 7; i++) {
        lines[i][0] = '\0';
    }
    
    // Process each character
    for (int i = 0; i < strlen(letter); i++) {
        wchar_t c = letter[i];
        char *current_char_array[7];
        
        switch (c) {
            case 'B': 
                for (int j = 0; j < 7; j++) current_char_array[j] = B_7lines[j];
                break;
            case 'D': 
                for (int j = 0; j < 7; j++) current_char_array[j] = D_7lines[j];
                break;
            case 'F': 
                for (int j = 0; j < 7; j++) current_char_array[j] = F_7lines[j];
                break;
            case 'L': 
                for (int j = 0; j < 7; j++) current_char_array[j] = L_7lines[j];
                break;
            case 'R': 
                for (int j = 0; j < 7; j++) current_char_array[j] = R_7lines[j];
                break;
            case 'U': 
                for (int j = 0; j < 7; j++) current_char_array[j] = U_7lines[j];
                break;
            case '2': 
                for (int j = 0; j < 7; j++) current_char_array[j] = TWO_7lines[j];
                break;
            case '\'': 
            case '´':
                for (int j = 0; j < 7; j++) current_char_array[j] = prime_7lines[j];
                break;
            case ' ': 
                for (int j = 0; j < 7; j++) current_char_array[j] = space_7lines[j];
                break;
            case '.': 
                for (int j = 0; j < 7; j++) current_char_array[j] = point_7lines[j];
                break;
            default:
                for (int j = 0; j < 7; j++) current_char_array[j] = space_7lines[j];
                break;
        }
        
        // Combine with existing lines
        for (int j = 0; j < 7; j++) {
            strcat(lines[j], current_char_array[j]);
            strcat(lines[j], " ");
        }
    }
    
    // Print the result
    for (int i = 0; i < 7; i++) {
        printf("%s\n", lines[i]);
        usleep(50000);
    }
}

// Print ASCII art for numbers
void print_number(const char *number) {
    char *number_array[12];
    
    // Initialize result lines
    char lines[12][MAX_LINE_LENGTH];
    for (int i = 0; i < 12; i++) {
        lines[i][0] = '\0';
    }
    
    // Process each character
    for (int i = 0; i < strlen(number); i++) {
        char c = number[i];
        char *current_char_array[12];
        
        switch (c) {
            case '0': 
                for (int j = 0; j < 12; j++) current_char_array[j] = zero_12lines[j];
                break;
            case '1': 
                for (int j = 0; j < 12; j++) current_char_array[j] = one_12lines[j];
                break;
            case '2': 
                for (int j = 0; j < 12; j++) current_char_array[j] = two_12lines[j];
                break;
            case '3': 
                for (int j = 0; j < 12; j++) current_char_array[j] = three_12lines[j];
                break;
            case '4': 
                for (int j = 0; j < 12; j++) current_char_array[j] = four_12lines[j];
                break;
            case '5': 
                for (int j = 0; j < 12; j++) current_char_array[j] = five_12lines[j];
                break;
            case '6': 
                for (int j = 0; j < 12; j++) current_char_array[j] = six_12lines[j];
                break;
            case '7': 
                for (int j = 0; j < 12; j++) current_char_array[j] = seven_12lines[j];
                break;
            case '8': 
                for (int j = 0; j < 12; j++) current_char_array[j] = eight_12lines[j];
                break;
            case '9': 
                for (int j = 0; j < 12; j++) current_char_array[j] = nine_12lines[j];
                break;
            case '.': 
                for (int j = 0; j < 12; j++) current_char_array[j] = dot_12lines[j];
                break;
            case ',': 
                for (int j = 0; j < 12; j++) current_char_array[j] = comma_12lines[j];
                break;
            case ':': 
                for (int j = 0; j < 12; j++) current_char_array[j] = colon_12lines[j];
                break;
            case ' ': 
                for (int j = 0; j < 12; j++) current_char_array[j] = space_12lines[j];
                break;
            default:
                for (int j = 0; j < 12; j++) current_char_array[j] = space_12lines[j];
                break;
        }
        
        // Combine with existing lines
        for (int j = 0; j < 12; j++) {
            strcat(lines[j], current_char_array[j]);
            strcat(lines[j], " ");
        }
    }
    
    // Print the result
    for (int i = 0; i < 12; i++) {
        printf("%s\n", lines[i]);
    }
}
