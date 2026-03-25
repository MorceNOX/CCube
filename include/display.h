#ifndef DISPLAY_H
#define DISPLAY_H

void create_box(const char *text);
void create_box_scramble(const char *text);
void create_boxes(char **words, int count);
void create_boxes_times(char* words[], int count);
void print_letter(const char *letter);
void print_number(const char *number);
char print_scramble( const char *text );
void print_average_times(int ao_count, double ao5, double ao12, double ao50, double mo3, double n_best);

#endif
