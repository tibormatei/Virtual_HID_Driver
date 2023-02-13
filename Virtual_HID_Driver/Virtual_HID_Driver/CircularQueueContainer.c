#include "CircularQueueContainer.h"
#include <stdlib.h>
#include <string.h>
#include "Loger.h"


CircularQueue* createCircularQueue(int size)
{
    CircularQueue *cq = (CircularQueue*) malloc(sizeof(CircularQueue));
    if (cq != NULL)
    {
        cq->data_array = (Data*) malloc(size * sizeof(Data));
        if (cq->data_array != NULL)
        {
            cq->capacity = size;

            cq->front = -1;
            cq->rear = -1;
            cq->actual_size = 0;
        }
        else
        {
            cq->capacity = 0;
            cq->actual_size = 0;
        }
    }

    return cq;
}

void destroyCircularQueue(CircularQueue* circularqueue)
{
    if (circularqueue != NULL)
    {
        if (circularqueue->data_array != NULL)
        {
            free(circularqueue->data_array);
        }
        free(circularqueue);
        circularqueue = NULL;
    }
}

void enqueue(CircularQueue* const circularqueue, Data* item)
{
    if (circularqueue != NULL)
    {
        if (!isFull(circularqueue))
        {
            if (circularqueue->front == circularqueue->capacity - 1)
            {
                circularqueue->front = 0;
            }
            else
            {
                circularqueue->front++;
            }
            memcpy(&circularqueue->data_array[circularqueue->front], item, sizeof(Data));
            circularqueue->actual_size++;
        }
        else
        {
            write_log_message("CircularQueue is full");
        }
    }
}

bool dequeue(CircularQueue* const circularqueue, Data* item)
{
    bool bDequeueIsSucces = false;

    if (circularqueue != NULL)
    {
        if (!isEmpty(circularqueue))
        {
            if (circularqueue->rear == circularqueue->capacity - 1)
            {
                circularqueue->rear = 0;
            }
            else
            {
                circularqueue->rear++;
            }

            if (item != NULL)
            {
                memcpy(item, &circularqueue->data_array[circularqueue->rear], sizeof(Data));
                bDequeueIsSucces = true;
            }
            circularqueue->actual_size--;
        }
        else
        {
            write_log_message("CircularQueue is empty");
        }
    }

    return bDequeueIsSucces;
}

bool isFull(CircularQueue* const circularqueue)
{
    return circularqueue->actual_size == circularqueue->capacity;
}

bool isEmpty(CircularQueue* const circularqueue)
{
    return circularqueue->actual_size == 0;
}
