/* Test program */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "s_treeinit.c"

static FILE *bench_fd;
static  struct timeval tv_start;
static  struct timeval tv_end;

static inline long time_diff_us(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) * 1000000) +
           (end->tv_usec - start->tv_usec);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: -t <num>\n");
        return -1;
    }

    bench_fd = fopen("bech_result", "w");
    if (!bench_fd) {
        fprintf(stderr, "Open bench result file failed\n");
        exit(-1);
    }
    
    int node_nums = atoi(argv[2]);
    srand(time(0));
    static struct st_root *tree_t;

    treeint_init(&tree_t);
    for (int i = 0; i < 100; ++i)
        treeint_insert(tree_t, rand() % 99);

    printf("[ After insertions ]\n");
    treeint_dump(tree_t);

    printf("Removing...\n");
    for (int i = 0; i < 100; ++i) {
        int v = rand() % 99;
        printf("%2d  ", v);
        if ((i + 1) % 10 == 0)
            printf("\n");
        treeint_remove(tree_t, v);
    }
    printf("\n");

    printf("[ After removals ]\n");
    treeint_dump(tree_t);

    treeint_destroy(tree_t);

    return 0;
}