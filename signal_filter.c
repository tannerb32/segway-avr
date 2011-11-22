/*
 * =====================================================================================
 *
 *       Filename:  signal_filter.c
 *
 *    Description:  Functions to perform noise cancellation techniques on signal data
 *
 *        Version:  1.0
 *        Created:  11/20/2011 07:23:59 PM
 *       Revision:  none
 *       Compiler:  avr-gcc
 *
 *         Author:  Tanner Bruce, bruce.tanner@gmail.com
 *
 * =====================================================================================
 */

struct lowpass_filter
{
    uint8_t size;
    uint8_t index;
    float *frame;
    float alpha;
};

uint8_t init_filter(struct lowpass_filter *filter, uint8_t window_size, float alpha)
{
    filter        = malloc(sizeof(struct lowpass_filter));
    filter->frame = malloc(sizeof(float) * window_size);
    filter->alpha = alpha;
    filter->index = 0;
    filter->size  = window_size;
}

uint8_t delete_filter(struct lowpass_filter *filter)
{
    free(filter->frame);
    free(filter);

    filter = NULL;
}

float push(struct lowpass_filter *filter, float value)
{
    uint8_t cur    = (filter->index + 1) % filter->size;
    float prev_val = filter->frame[filter->index];
    float new_val  = prev_val + filter->alpha * (value - prev_val);

    filter->frame[cur] = new_val;

//queue->data[tin] = queue->data[(queue->in - 1) % QUEUE_SIZE] + 
//    ALPHA * (data - queue->data[(queue->in - 1) % QUEUE_SIZE]);
}

