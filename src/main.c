#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "scramble.h"
#include "timer.h"
#include "audio.h"
#include "display.h"
#include "utils.h"
#include "file_ops.h"
#include "utils_data.h"
#include "quicksort.h"

#include <locale.h>

#ifdef USE_LIBAO
#include <ao/ao.h>
#endif

#define N_SCRAMBLES 20
#define N_TIMES 100
#define MAX_SCRAMBLE_LENGTH 1024
#define MAX_AO_SIZE 1000
#define MAX_LINE_LENGTH 2048

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "");

    printf("\n                         TM\n");
    printf("    ░█▀▀░█▀▀░█░█░█▀▄░█▀▀\n");
    printf("    ░█░░░█░░░█░█░█▀▄░█▀▀\n");
    printf("    ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀▀▀\n\n");

    printf("\033[33m           _ _ _\n");
    printf("\033[33m          /_/_/_\033[32m/\\\n");
    printf("\033[33m         /_/_/_\033[32m/\\/\\\n");
    printf("\033[33m        /_/_/_\033[32m/\\/\\/\\\n");
    printf("\033[31m        \\_\\_\\_\033[32m\\/\\/\\/ \n");
    printf("\033[31m         \\_\\_\\_\033[32m\\/\\/ \n");
    printf("\033[31m          \\_\\_\\_\033[32m\\/ \033[0m\n\n");
 

    // printf("        ___ ___ ___  \n");
    // printf("      /___/___/___/| \n");
    // printf("     /___/___/___/|| \n");
    // printf("    /___/___/__ /|/| \n");
    // printf("   |   |   |   | /|| \n");
    // printf("   |___|___|___|/|/| \n");
    // printf("   |   |   |   | /|| \n");
    // printf("   |___|___|___|/|/  \n");
    // printf("   |   |   |   | /   \n");
    // printf("   |___|___|___|/    \n\n");

    
    printf("\n    CCube™ Copyright © 2026  Amilcar Antonio Mesquita Rizk\n");
    printf("    This program comes with ABSOLUTELY NO WARRANTY; for details see README.md file.\n");
    printf("    This is free software, and you are welcome to redistribute it\n");
    printf("    under certain conditions; see <https://www.gnu.org/licenses/> for details.\n");
    printf("\n");


    // Test sound at the beginning
    printf("Testing sound system...\n");
    play_timer_start_sound();
    usleep(500000); // Half a second
    play_timer_stop_sound();
    printf("Sound test complete. Press ENTER to continue...\n");
    getchar();

    // Initialize audio system
    init_audio();
    
    // Make sure we cleanup audio on exit
    atexit(cleanup_audio);

    long long ao[MAX_AO_SIZE];
    int ao_count = 0;
    double n_best = 0;
    double n_best_ant = 0;

    long long* ao_file = read_numbers_from_file("times.txt", &ao_count);

    if (ao_file != NULL) {
        if (ao_count > 0) {        
            n_best = ao_file[ao_count - 1];

            for (int i = 0; i < ao_count; i++) {
                ao[i] = ao_file[ao_count - i - 1];

                if (ao[i] < n_best)
                    n_best = ao[i];
            }
        }
    }

    while (1) {
        system("clear");
        
        char scramble[MAX_SCRAMBLE_LENGTH];
        char scrambleA[100];
        char scrambleB[100];
        char scrambleC[100];
        char timestamp[50];
        char str_time[20];
        char str_secs[20];

        double ao5 = 0;
        double ao12 = 0;
        double ao50 = 0;
        double mo3 = 0;

        if (ao_count > 0) {
            ao5 = calc_ao(5, ao, ao_count);
            ao12 = calc_ao(12, ao, ao_count);
            ao50 = calc_ao_50(50, ao, ao_count);
            mo3 = calc_mo(3, ao, ao_count);
        }
                
        // Get timestamp
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H:%M:%S", tm_info);
        
        // Generate scramble
        generate_scramble(scramble);
        
        // Split scramble into three parts
        split_scramble(scramble, scrambleA, scrambleB, scrambleC);
        
        // Print scramble
        printf("        Here is a scramble for the Rubik's Cube: #│\033[3;30;47m %03d \033[0m│\n", (ao_count + 1));
        
        
        create_box_scramble(scramble);
        printf("\n");
        
        printf("\033[33m");
        print_letter(scrambleA);
        printf("\033[32m");
        print_letter(scrambleB);
        printf("\033[36m");
        print_letter(scrambleC);
        
        printf("\n");
        printf("─────────────────────────────────────────────────────────────────────────────────────────────────────────────\n");
        printf("\033[31m");
        printf(" ▄▄▄       ██▀███  ▓█████    ▓██   ██▓ ▒█████   █    ██     ██▀███  ▓█████ ▄▄▄      ▓█████▄▓██   ██▓ ██████  \n");
        printf("▒████▄    ▓██ ▒ ██▒▓█   ▀     ▒██  ██▒▒██▒  ██▒ ██  ▓██▒   ▓██ ▒ ██▒▓█   ▀▒████▄    ▒██▀ ██▌▒██  ██▒      ██ \n");
        printf("▒██  ▀█▄  ▓██ ░▄█ ▒▒███        ▒██ ██░▒██░  ██▒▓██  ▒██░   ▓██ ░▄█ ▒▒███  ▒██  ▀█▄  ░██   █▌ ▒██ ██░   ▄███  \n");
        printf("░██▄▄▄▄██ ▒██▀▀█▄  ▒▓█  ▄      ░ ▐██▓░▒██   ██░▓▓█  ░██░   ▒██▀▀█▄  ▒▓█  ▄░██▄▄▄▄██ ░▓█▄   ▌ ░ ▐██▓░   ▀▀    \n");
        printf(" ▓█   ▓██▒░██▓ ▒██▒░▒████▒     ░ ██▒▓░░ ████▓▒░▒▒█████▓    ░██▓ ▒██▒░▒████▒▓█   ▓██▒░▒████▓  ░ ██▒▓░   ██    \n");
        printf(" ▒▒   ▓▒█░░ ▒▓ ░▒▓░░░ ▒░ ░      ██▒▒▒ ░ ▒░▒░▒░ ░▒▓▒ ▒ ▒    ░ ▒▓ ░▒▓░░░ ▒░ ░▒▒   ▓▒█░ ▒▒▓  ▒   ██▒▒▒          \n");
        printf("  ▒   ▒▒ ░  ░▒ ░ ▒░ ░ ░  ░    ▓██ ░▒░   ░ ▒ ▒░ ░░▒░ ░ ░      ░▒ ░ ▒░ ░ ░  ░ ▒   ▒▒ ░ ░ ▒  ▒ ▓██ ░▒░          \n");
        printf("  ░   ▒     ░░   ░    ░       ▒ ▒ ░░  ░ ░ ░ ▒   ░░░ ░ ░      ░░   ░    ░    ░   ▒    ░ ░  ░ ▒ ▒ ░░           \n");
        printf("      ░  ░   ░        ░  ░    ░ ░         ░ ░     ░           ░        ░  ░     ░  ░   ░    ░ ░              \n");
        printf("                              ░ ░                                                    ░      ░ ░              \n");
        printf("\n");
        printf("\033[0m");

        printf("Press <ENTER> to start the timer ('q' to exit)...");

        char ch;
        while (1) {
            ch = getchar();
            
            if (ch != EOF) {
                ungetc(ch, stdin);
                clearInputBuffer();
                break;
            }
            
            usleep(100000);
        }
        
        printf("\n");

        if (ch == 'q' || ch == 'Q') {
            break;
        }
                
        // Play timer start sound
        play_timer_start_sound();

        set_conio_mode();

        for (int i = 15; i >= 0; i--) {            
           // Display time
            char str[20];
            snprintf(str, sizeof(str), "     %02d", i);

            strcpy(str_secs, str);
            system("clear");

            play_pre_timer();

            ch = getchar(); // Get character without blocking
            if (ch != EOF) {
                // Key pressed, stop timer
                ungetc(ch, stdin);
                clearInputBuffer();
                break;
            }
                        
            printf("\033[35m");            
            print_number(str_secs);

            clearInputBuffer();
            usleep(857500); // 850ms sleep       
        }

        // Play timer start sound
        play_timer_start_sound();

        // Start timer
        struct timespec start_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);
       
        // Timer loop
        while (1) {
            long long elapsed_ns = get_elapsed_time(start_time);
            
            // Display time
            strcpy(str_time, get_strtime(elapsed_ns));
            system("clear");

            int color_code = get_timer_color(elapsed_ns, ao5, ao12, ao_count);
            printf("\033[%dm", color_code);
            
            print_number(str_time);
                        
            ch = getchar(); // Get character without blocking
            
            if (ch != EOF) {
                // Key pressed, stop timer
                ungetc(ch, stdin);
                clearInputBuffer();
                break;
            }
            
            usleep(20000); // 20ms sleep            
        }
        
        // Timer stopped
        long long elapsed_ns = get_elapsed_time(start_time);
        strcpy(str_time, get_strtime(elapsed_ns));

        system("clear");
        print_number(str_time);

        printf("\033[0m");
        printf("\nStopped!\n");

        // Play timer stop sound
        play_timer_stop_sound();

        clearInputBuffer();
        usleep(2000000);
  
        // Add to ao array
        ao[ao_count++] = elapsed_ns;

        n_best_ant = n_best;
        if (elapsed_ns < n_best || n_best == 0)
            n_best = (double)elapsed_ns;
        
        // Calculate averages
        ao5 = calc_ao(5, ao, ao_count);
        ao12 = calc_ao(12, ao, ao_count);
        ao50 = calc_ao_50(50, ao, ao_count);
        
        mo3 = calc_mo(3, ao, ao_count);
        
        printf("\033[1A\033[2K");

        print_average_times(ao_count, ao5, ao12, ao50, mo3, n_best);
        
        printf("\nSave this scramble (Y/n)? ");
        while (1) {
            ch = getchar();
            
            if (ch != EOF) {
                ungetc(ch, stdin);
                clearInputBuffer();
                break;                
            }
            
            usleep(100000);
        }
        
        if (ch == 'n' || ch == 'N') {           
            printf(" This scramble is NOT saved! Rolling back the times...");
            clearInputBuffer();
            usleep(1800000);

            // roll-back averages
            if (ao_count == 1) {
                ao5 = 0;
                ao12 = 0;
                ao50 = 0;
                n_best = 0;
                mo3 = 0;
                ao_count = 0;
            } else {
                ao_count--;
                ao5 = calc_ao(5, ao, ao_count);
                ao12 = calc_ao(12, ao, ao_count);
                ao50 = calc_ao_50(50, ao, ao_count);
                mo3 = calc_mo(3, ao, ao_count);

                n_best = n_best_ant;
            }
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\033[1A\033[2K");
            printf("\r");
            printf("\n");
            
            print_average_times(ao_count, ao5, ao12, ao50, mo3, n_best);

        } else if (ch == 'q' || ch == 'Q') {
            reset_terminal_mode();
            break;

        } else {
            save_scramble(timestamp, str_time, scramble);
            save_time(elapsed_ns);
            printf(" This scramble is SAVED!");
            clearInputBuffer();
            usleep(1800000);

            printf("\033[1A\033[2K");
            printf("\r");
        }       
                        
        // Calculate overall average
        int ao_file_count;
        // Use the new function to get proper file path
        ao_file = read_numbers_from_file("times.txt", &ao_file_count);

        if (ao_file == NULL) {
            printf("\nNo saved times yet to be shown! ");
            clearInputBuffer();
            usleep(2000000);
            continue;
        }

        if (ao_file_count > 0) {
            double overall_avg = calc_ao(ao_file_count, ao_file, ao_file_count);
            printf("\033[0;36m");
            printf("\n\033[40m\033[3m (Overall) Average of %2d \033[0m: \033[1;36m%s                                                                \n", ao_file_count, get_strtime((long long)overall_avg));

            free(ao_file);

            printf("\033[0m");
            print_last_scrambles();
        }
                
        printf("\n");
        printf("Enter any value to continue... or 'q' to exit, or 'x' to close session and exit...");

        clearInputBuffer();
        
        while (1) {
            ch = getchar();
            if (ch != EOF) {
                ungetc(ch, stdin);
                clearInputBuffer();
                break;
            } 
            
            // char continue_input[10];
            // if (fgets(continue_input, sizeof(continue_input), stdin)) {
            //     char continue_choice = continue_input[0];
            //     if (continue_choice == 's' || continue_choice == 'S') {
            //         // Use the proper data file path instead of hardcoded one
            //         char* scrambles_file = get_data_file_path("scrambles.txt");
            //         FILE *file = fopen(scrambles_file, "r");
            //         if (file) {
            //             char line[512];
            //             while (fgets(line, 512, file)) {
            //                 printf("%s", line);
            //             }
            //             fclose(file);
            //             printf("\nPress any key to continue... ");
            //             clearInputBuffer();
            //             getchar();
            //         }
            //     } else if (continue_choice == 'q' || continue_choice == 'Q') {
            //         break;
            //     }
            // }
            
            usleep(100000);
        }

        reset_terminal_mode();

        if (ch == 'q' || ch == 'Q') {
            break;
        }
        else if (ch == 'x' || ch == 'X') {
            close_session();
            break;
        }
        else {
            clearInputBuffer();
        }
    }

    printf("\n");
    printf("\n                         TM\n");
    printf("    ░█▀▀░█▀▀░█░█░█▀▄░█▀▀\n");
    printf("    ░█░░░█░░░█░█░█▀▄░█▀▀\n");
    printf("    ░▀▀▀░▀▀▀░▀▀▀░▀▀░░▀▀▀\n\n");
    printf("\033[33m           _ _ _\n");
    printf("\033[33m          /_/_/_\033[32m/\\\n");
    printf("\033[33m         /_/_/_\033[32m/\\/\\\n");
    printf("\033[33m        /_/_/_\033[32m/\\/\\/\\\n");
    printf("\033[31m        \\_\\_\\_\033[32m\\/\\/\\/ \n");
    printf("\033[31m         \\_\\_\\_\033[32m\\/\\/ \n");
    printf("\033[31m          \\_\\_\\_\033[32m\\/ \033[0m\n\n");
 
    printf("\n");
    return 0;
}








