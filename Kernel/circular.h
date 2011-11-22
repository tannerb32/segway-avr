#ifndef _CIRCULAR_H_
#define _CIRCULAR_H_

#include <inttypes.h>

#define QUEUE_SIZE 16
#define QUEUE_ERROR (-1)
#define QUEUE_OK (0)

struct CircularQueue
{
    volatile uint8_t in;
    volatile uint8_t out;
    volatile uint8_t data[QUEUE_SIZE];
    uint8_t low_pass;
};

void initQueue(struct CircularQueue *queue);
int enQueue(struct CircularQueue *queue, uint8_t data);
int deQueue(struct CircularQueue *queue);
void low_pass(struct CircularQueue *queue);

#endif /* _CIRCULAR_H_ */

