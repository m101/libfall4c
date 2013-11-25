#include <stdio.h>
#include <stdlib.h>

#include "data/data_ops.h"

struct data_ops *data_ops_new (void)
{
    struct data_ops *data_ops;

    data_ops = calloc (1, sizeof (*data_ops));
    if (!data_ops) {
        fprintf (stderr, "error: data_ops_new(): Failed allocating data_ops\n");
        return NULL;
    }

    data_ops->comparator = comparator_no_ops;
    data_ops->destroy = destroy_no_ops;
    data_ops->get_size = get_size_no_ops;
    data_ops->show = show_no_ops;

    return data_ops;
}

int comparator_no_ops (void *data1, void *data2)
{
    return data1 - data2;
}

void destroy_no_ops (void **data)
{
    return;
}

void destroy_allocated (void **data)
{
    if (!data) {
        fprintf (stderr, "error: destroy_allocated(): Bad parameter(s)\n");
        return;
    }

    free (*data);
}

size_t get_size_no_ops (void *data)
{
    return 0;
}

void show_no_ops (void *data)
{
    return;
}

