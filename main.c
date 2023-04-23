#include <stdio.h>
#include "list.h"
#include "list_sort.h"
#include "timsort.h"
#include "f9_sort.h"

#define BUF_SIZE 512

int main() 
{
    int *sort_buf = malloc(sizeof(int) * BUF_SIZE);
    int *qsort_buf = malloc(sizeof(int) * BUF_SIZE);
    int *timsort_buf = malloc(sizeof(int) * BUF_SIZE);

    for (size_t i = 0; i < BUF_SIZE; i++) {
        int data = i;
        sort_buf[i] = data;
        qsort_buf[i] = data;
        timsort_buf[i] = data;
    }

    for (size_t i = BUF_SIZE - BUF_SIZE / 16; i < BUF_SIZE; i++) {
        int data = rand() % BUF_SIZE;
        sort_buf[i] = data;
        qsort_buf[i] = data;
        timsort_buf[i] = data;
    }

    clock_t time;

    time = clock();
    timsort(timsort_buf, timsort_buf + BUF_SIZE, sizeof(int), compare);
    printf("timsort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);

    time = clock();
    qsort(qsort_buf, BUF_SIZE, sizeof(int), Q_compare);
    printf("qsort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);
    
    time = clock();
    f9sort(sort_buf, BUF_SIZE, sizeof(int), Q_compare);
    printf("f9sort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);

    // for (size_t i = 0; i < BUF_SIZE; i++) {
    //     printf("%d \n", sort_buf[i]);
    // }

    return 0;
}