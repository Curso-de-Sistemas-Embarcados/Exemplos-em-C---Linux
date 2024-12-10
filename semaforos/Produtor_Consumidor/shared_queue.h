#ifndef SHARED_QUEUE_H
#define SHARED_QUEUE_H

#define MAX_ITEMS 10

typedef struct {
    int buffer[MAX_ITEMS];
    int in;
    int out;
    int count;
} shared_queue;

#endif