/**
 * @file main.c
 * @brief main file for blackbox project
 * @details test functions for runtime complexity using unisigned long integer or unisigned long list
 *
 * @author Jennifer Minnich
 * @date 4/23/2021
 * @bug After building out the program for automation, runtimes differ slightly than documented in summary.pdf
 *      The second test run seems to be reporting erraticly.
 *      Valgrind reports reachable memory but no loss.
 *      Seg Faults with large n at F2 and F7
 * 
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "blackbox.h"

int main(int argc, char **argv)
{
    unsigned long n;
    unsigned long i;
    unsigned long *list = malloc(sizeof(unsigned long) * n);
    int msec;
    clock_t time_elapsed;
    int c = 0; // menu switch
    FILE *fp = NULL;
    int fx = 0;  // nested function switch
    int run = 0; // program counter
    unsigned long int sum = 0;

    if (argc == 1)
    {
        printf("usage: ./main -n [NUM] -x [FUNCTION] -f [FILE]\n");
        printf("[FUNCTION] is the number of the function we are testing, use 1-7 \n");
        printf("[FUNCTION 3 sorted list] use 3 \n");
        printf("[FUNCTION 3 reversed list] use 31 \n");
        printf("[FUNCTION 3 shuffled list] use 32 \n");
        printf("[FUNCTION 6 sorted list] use 6 \n");
        printf("[FUNCTION 6 reversed list] use 61 \n");
        printf("[FUNCTION 6 shuffled list] use 62 \n");
        printf("[NUM] is the unsigned long integer\n");
        printf("[FILE] is the name of the file the data is written to\n");
        exit(EXIT_SUCCESS);
    }

    while (run >= 0 && run < 3)
    {
        printf("|Testing requirement: take the average of 3 tests\n");
        printf("|counter: %d\n", run + 1);

        while ((c = getopt(argc, argv, ":hn:x:f:")) != -1)
            switch (c)
            {
            case 'n':
                n = atoll(optarg);
                break;
            case 'x':
                fx = atoi(optarg);
                switch (fx)
                {
                case 1:
                    time_elapsed = clock();
                    function_1(n);
                    break;
                case 2:
                    time_elapsed = clock();
                    function_2(n);
                    break;
                case 3:
                    generate_sorted_list(n, i, list);
                    time_elapsed = clock();
                    function_3(list, n);
                    free(list);
                    break;
                case 31:
                    generate_sorted_list(n, i, list);
                    generate_reverse_list(list, 0, n - 1, n);
                    time_elapsed = clock();
                    function_3(list, n);
                    free(list);
                    break;
                case 32:
                    generate_sorted_list(n, i, list);
                    //unsigned long n = huge_random_number();
                    generate_shuffled_list(n, i, list);
                    time_elapsed = clock();
                    function_3(list, n);
                    free(list);
                    break;
                case 4:
                    time_elapsed = clock();
                    function_4(n);
                    break;
                case 5:
                    time_elapsed = clock();
                    function_5(n);
                    break;
                case 6:
                    generate_sorted_list(n, i, list);
                    time_elapsed = clock();
                    function_6(list, n);
                    free(list);
                    break;
                case 61:
                    generate_sorted_list(n, i, list);
                    generate_reverse_list(list, 0, n - 1, n);
                    time_elapsed = clock();
                    function_6(list, n);
                    free(list);
                    break;
                case 62:
                    generate_sorted_list(n, i, list);
                    //unsigned long m = huge_random_number();
                    generate_shuffled_list(n, i, list);
                    time_elapsed = clock();
                    function_6(list, n);
                    free(list);
                    break;
                case 7:
                    time_elapsed = clock();
                    function_7(n);
                    break;
                default:
                    printf("error");
                    return 0;
                }
            case 'f':
                errno = 0; // set to 0 so it can process if an error occurs
                fp = fopen(optarg, "w");
                if (fp == NULL)
                {
                    //strerror
                    fprintf(stderr, "%s: argument to option '-f' failed: %d\n", argv[0], strerror(errno));
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h': //help
                if (fp != NULL)
                    fclose(fp);
                printf("usage: ./main -n [NUM] -x [FUNCTION] -f [FILE]\n");
                printf("[FUNCTION] is the number of the function we are testing, use 1-7 \n");
                printf("[FUNCTION 3 sorted list] use 3 \n");
                printf("[FUNCTION 3 reversed list] use 31 \n");
                printf("[FUNCTION 3 shuffled list] use 32 \n");
                printf("[FUNCTION 6 sorted list] use 6 \n");
                printf("[FUNCTION 6 reversed list] use 61 \n");
                printf("[FUNCTION 6 shuffled list] use 62 \n");
                printf("[NUM] is the unsigned long integer\n");
                printf("[FILE] is the name of the file the data is written to\n");
                exit(EXIT_SUCCESS);
            case ':':
                // missing option argument
                if (fp != NULL)
                    fclose(fp);
                fprintf(stderr, "%s: option '-%c' reguires an argument\n", argv[0], optopt);
                exit(EXIT_FAILURE);
            case '?': //getopt default invalid option
            default:
                printf("illegal option %c - ignored\n", optopt);
                break;
            }

        //all options are required, check to make sure they are valid
        if (fp == NULL)
        {
            printf("the option -f [FILE] is required\n");
            printf("usage: ./main -n [NUM] -f [FILE]\n");
            exit(EXIT_FAILURE);
        }

        //time tracker
        time_elapsed = clock() - time_elapsed;
        msec = time_elapsed * 1000 / CLOCKS_PER_SEC;
        printf("|Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
        printf("|CPU-Time elapsed: %d ticks\n\n", (int)time_elapsed);
        printf("|------------------------------------------------------------- |\n");

        //sums the time elapsed from 3 tests
        sum += time_elapsed;

        //run counter
        run++;
    }

    //calculates the average time elapsed from 3 tests
    unsigned long int average_time = 0;
    average_time = sum / run - 1;
    //prints n, and average time to file
    fprintf(fp, "%ld %ld\n", n, average_time);
    printf("\naverage: %ld ticks\n\n", average_time);

    //close file
    fclose(fp);

    return 0;
}

/**
* classic swap function, swaps two ulis
* @param a pointer to first uli
* @param b pointer to second uli
*/

void swap(unsigned long *a, unsigned long *b)
{
    unsigned long temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
* generates a sorted list with size dependent on uli
* @param n list size determined by user intake, uli
* @param i index
* @param list the list of ulis
*/

void generate_sorted_list(unsigned long n, unsigned long i, unsigned long *list)
{
    for (i = 0; i < n; i++)
    {
        *(list + i) = i;
    }
}

/**
* generates a reverse list with size dependent on uli
* @param n uli list size determined by user intake
* @param low index list 0
* @param list the list of ulis
* @param high index at list -1 (end)
*/

void generate_reverse_list(unsigned long *list, unsigned long low, unsigned long high, unsigned long n)
{

    for (int low = 0, high = n - 1; low < high; low++, high--)
    {
        unsigned long temp = list[low];
        list[low] = list[high];
        list[high] = temp;
    }
}

/**
* generates a shuffled list with size dependent on uli
* @param n uli list size determined by user intake
* @param i index
* @param list the list of ulis
* @param m uli variable
*/

void generate_shuffled_list(unsigned long n, unsigned long i, unsigned long *list)
{
    //fisher yates shuffle
    //seed random value
    srand(time(NULL));
    int j;
    //start from last element
    for (i = n - 1; i > 0; i--)
    {
        //pick a random element between 0 and i to swap
        j = rand() % (i + 1);
        swap(list + i, list + j);
    }
}

/**
* generates a huge random number to utilize the shuffle on very large lists
*/

unsigned long huge_random_number(void)
{
    unsigned long n, p, r;
    int i;
    p = 1;
    n = 0;
    srandom(time(NULL));
    for (i = 0; i < 8; i++, p *= 256)
    {

        /* we have p = 256^i */
        /* random value between 0 and 255 */
        r = random() % 256;

        /* add this pseudo-random byte to n */
        n += r * p;

    } /* repeat 8 times, so we have 64 pseudo-random bits */
    return n;
}

/**
* prints lists to test and debug code
* @param n uli list size determined by user intake
* @param list the list of ulis
*/

void print(unsigned long *list, unsigned long n)
{
    for (unsigned long i = 0; i < n; i++)
    {
        printf("%ld ", list[i]);
    }
}
