#include <stdio.h>
#include "list.h"
#include "list_sort.h"
#include "timsort.h"
#include "f9_sort.h"
#include "sort.h"

#define BUF_SIZE 1024

static bool b_cmp(const void *a, const void *b);
static int cmp(const void *a, const void *b);
static void swap_r(void *a, void *b, int n);

int main() 
{
    int *fsort_buf = malloc(sizeof(int) * BUF_SIZE);
    int *qsort_buf = malloc(sizeof(int) * BUF_SIZE);
    int *timsort_buf = malloc(sizeof(int) * BUF_SIZE);
    int *sort_buf = malloc(sizeof(int) * BUF_SIZE);

    for (size_t i = 0; i < BUF_SIZE; i++) {
        int data = i;
        fsort_buf[i] = data;
        qsort_buf[i] = data;
        timsort_buf[i] = data;
        sort_buf[i] = data;
    }

    for (size_t i = 0; i < BUF_SIZE; i++) {
        int data = rand() % BUF_SIZE;
        fsort_buf[i] = data;
        qsort_buf[i] = data;
        timsort_buf[i] = data;
        sort_buf[i] = data;
    }

    clock_t time;

    time = clock();
    timsort(timsort_buf, timsort_buf + BUF_SIZE, sizeof(int), b_cmp);
    printf("timsort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);

    time = clock();
    qsort(qsort_buf, BUF_SIZE, sizeof(int), cmp);
    printf("qsort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);
    
    time = clock();
    f9sort(fsort_buf, BUF_SIZE, sizeof(int), cmp);
    printf("f9sort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);

    time = clock();
    sort_o(sort_buf, BUF_SIZE, sizeof(int), cmp, swap_r);
    printf("sort: %.1f us\n",
           (double) (clock() - time) / CLOCKS_PER_SEC * 1e6);

    // for (size_t i = 0; i < BUF_SIZE; i++) {
    //     printf("%d ", sort_buf[i]);
    // }
    // printf("\n");
    // assert(!memcmp(timsort_buf, qsort_buf, BUF_SIZE * sizeof(int)));

    return 0;
}

static bool b_cmp(const void *a, const void *b)
{
    return *(int *) a < *(int *) b;
}

static int cmp(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

static void swap_r(void *a, void *b, int n)
{
	do {
		unsigned int t = *(unsigned int *)(a + (n -= 4));
		*(unsigned int *)(a + n) = *(unsigned int *)(b + n);
		*(unsigned int *)(b + n) = t;
	} while (n);
}