#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

void time_diff(struct timespec *start, struct timespec *end, struct timespec *diff);

void time_diff(struct timespec *start, struct timespec *end, struct timespec *diff)
{
    diff->tv_sec=end->tv_sec - start->tv_sec;
    diff->tv_nsec=end->tv_nsec - start->tv_nsec;
    if(diff->tv_nsec < 0)
    {
        --diff->tv_sec;
        diff->tv_nsec+=1000000000;
    }
}

int main(int argc, char *argv[])
{
    struct timespec start, end, diff;
    ll_error error;
    linked_list *list;
    uint32_t i, *d, limit;
    double diff_ind;

    /* top insertion */
    puts("top insertion");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0x9ffffff;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, 0);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/ll_size(list);
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    puts("top insertion round 2");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0x9ffffff;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, 0);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/ll_size(list);
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* bottom insertion */
    puts("bottom insertion");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, i);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/ll_size(list);
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* append insertion */
    puts("append insertion");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_append(list, d);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/ll_size(list);
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* random insertion */
    puts("random insertion");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0xcfff;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, (uint32_t)rand()%(i+1));
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/ll_size(list);
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* top removal */
    puts("top removal");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0x9ffffff;
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, i);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }

    limit=ll_size(list);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        error=ll_remove(list, 0, (void**)&d);
        if(error!=ll_ESUCCESS)
            printf("insert %d error %d\n", i, error);
        free(d);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/limit;
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* bottom removal */
    puts("bottom removal");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0xffff;
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, i);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }

    limit=ll_size(list);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        error=ll_remove(list, ll_size(list)-1, (void**)&d);
        if(error!=ll_ESUCCESS)
            printf("insert %d error %d\n", i, error);
        free(d);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/limit;
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    /* random removal */
    puts("random removal");
    list=ll_new();
    if(!list)
    {
        puts("failed to create list");
        return -1;
    }

    limit=0xffff;
    for(i=0; i<limit; ++i)
    {
        d=malloc(sizeof(uint32_t));
        if(d)
        {
            *d=i;
            error=ll_insert(list, d, i);
            if(error!=ll_ESUCCESS)
                printf("insert %d error %d\n", i, error);
        }
    }

    limit=ll_size(list);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(i=0; i<limit; ++i)
    {
        error=ll_remove(list, (uint32_t)rand()%ll_size(list), (void**)&d);
        if(error!=ll_ESUCCESS)
            printf("insert %d error %d\n", i, error);
        else
            free(d);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time_diff(&start, &end, &diff);
    diff_ind=(diff.tv_sec + (diff.tv_nsec/1e9))/limit;
    printf("  time %ld.%09ld (%.10g s/insert)\n", diff.tv_sec, diff.tv_nsec, diff_ind);

    error=ll_delete(list, free);
    if(error!=ll_ESUCCESS)
        printf("delete error %d\n", error);

    return 0;
}

