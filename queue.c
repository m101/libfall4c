#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct t_queue* queue_new (void)
{
    struct t_queue *Queue = malloc(sizeof(struct t_queue));

    Queue->data = NULL;
    Queue->next = NULL;

    return Queue;
}

struct t_queue* queue_destroy (struct t_queue *Queue)
{
    struct t_queue *QueueTemp = Queue;
    while (Queue)
    {
        Queue = Queue->next;
        free(QueueTemp);
        QueueTemp = Queue;
    }

    return NULL;
}

int queue_count (struct t_queue *anchor)
{
    size_t nb = 0;

    while (anchor)
    {
        nb++;
        anchor = anchor->next;
    }

    return nb;
}

void queue_add (struct t_queue **anchor, struct t_queue *List)
{
    struct t_queue *anchorTemp = NULL;
    struct t_queue *m_anchor = NULL;
    if (!anchor)
    {
        fprintf(stderr, "queue_add: Queue is empty\n");
        return;
    }

    if (!*anchor)
    {
        fprintf(stderr, "queue_add: Queue is empty\n");
        return;
    }

    m_anchor = *anchor;

    if ( m_anchor->data == NULL)
    {
        *anchor = m_anchor->next;
        m_anchor = *anchor;
        free(m_anchor);
        if (*anchor == NULL)
            *anchor = List;
    }
    else
    {
        while (m_anchor)
        {
            anchorTemp = m_anchor;
            m_anchor = m_anchor->next;
        }
        if (anchorTemp)
            anchorTemp->next = List;
    }
}

struct t_queue* queue_remove (struct t_queue **anchor)
{
    struct t_queue *node = NULL;
    if (!anchor)
    {
        fprintf(stderr, "queue_remove: Queue is empty\n");
        return NULL;
    }

    node = *anchor;
    *anchor = (*anchor)->next;

    // Renvoi le premier element
    return node;
}
