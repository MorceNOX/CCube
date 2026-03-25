#ifndef SCRAMBLE_H
#define SCRAMBLE_H

void get_scramble(const char *full_scramble, char *scramble);
void generate_scramble(char *scramble);
void split_scramble(const char *full_scramble, char *scrambleA, char *scrambleB, char *scrambleC);
int random_int(int max);

#endif

