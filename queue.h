#ifndef _QUEUE_H_
#define _QUEUE_H_

struct t_queue
{
    void *data;
    struct t_queue *next;
} t_queue;

struct t_queue* queue_new (void);
struct t_queue* queue_destroy (struct t_queue *Queue);
int queue_count (struct t_queue *anchor);
void queue_add (struct t_queue **anchor, struct t_queue *List);
struct t_queue* queue_remove (struct t_queue **anchor);

#endif
