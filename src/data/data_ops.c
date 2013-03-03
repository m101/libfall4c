#include <stdio.h>
#include <stdlib.h>

int comparator_no_ops (void *data1, void *data2)
{
    return data1 - data2;
}

void destroy_no_ops (void **data)
{
    return;
}

void free_no_ops (void *data)
{
    return;
}

void destroy_allocated (void **data)
{
    if (!data) {
        printf ("error: destroy_allocated(): Bad parameter(s)\n");
        return;
    }

    free (*data);
}

void get_size_no_ops (void *data)
{
    return 0;
}

void show_no_ops (void *data)
{
    return;
}

