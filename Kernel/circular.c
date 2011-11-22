#include "circular.h"

void initQueue(struct CircularQueue *queue)
{
    queue->in = 0;
    queue->out = 0;
}

int enQueue(struct CircularQueue *queue, uint8_t data)
{
    int result = QUEUE_ERROR;
    //    char debug[16];
    uint8_t tin;
    tin = (queue->in + 1) % QUEUE_SIZE;

    if (queue->out != tin)
    {
        queue->data[tin] = data; 
        queue->in = tin;
        result = QUEUE_OK;
    }

    //    sprintf(debug, "In: %3d Out: %3d\n", queue->in, queue->out );
    //    transmitStringUSART1(debug);
    return result;
}

int deQueue(struct CircularQueue *queue)
{
    int result = QUEUE_ERROR;

    if (queue->in != queue->out)
    {
        result = (0x00 << 8) | queue->data[queue->out];
        queue->out = (queue->out + 1) % QUEUE_SIZE;
    }

    return result;
}

