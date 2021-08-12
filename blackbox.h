#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

//void time_track(clock_t time_elapsed, int msec);
void swap(unsigned long *a, unsigned long *b);
void generate_reverse_list(unsigned long *list, unsigned long low, unsigned long high, unsigned long list_size);
void generate_sorted_list(unsigned long n, unsigned long i, unsigned long *list);
void generate_shuffled_list(unsigned long n, unsigned long i, unsigned long *list);
unsigned long huge_random_number(void);
void print(unsigned long *list, unsigned long n);

void function_1(unsigned long n);
void function_2(unsigned long n);
void function_3(unsigned long *list, unsigned long n);
void function_4(unsigned long n);
void function_5(unsigned long n);
void function_6(unsigned long *list, unsigned long n);
void function_7(unsigned long n);

#endif
