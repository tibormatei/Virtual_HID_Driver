#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>


typedef struct _Data
{
    unsigned char command;
    unsigned char parameters[20];
} Data;

typedef struct _CircularQueue
{
    Data *data_array;
    int capacity;
    int actual_size;
    int rear;
    int front;
} CircularQueue;

CircularQueue* createCircularQueue(int size);
void destroyCircularQueue(CircularQueue* circularqueue);
void enqueue(CircularQueue* const circularqueue, Data* item);
bool dequeue(CircularQueue* const circularqueue, Data* item);
bool isFull(CircularQueue* const circularqueue);
bool isEmpty(CircularQueue* const circularqueue);

#ifdef __cplusplus
}
#endif
