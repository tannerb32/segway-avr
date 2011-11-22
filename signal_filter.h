/*
 * =====================================================================================
 *
 *       Filename:  signal_filter.h
 *
 *    Description:  Functions to perform noise cancellation techniques on signal data
 *
 *        Version:  1.0
 *        Created:  11/20/2011 07:22:56 PM
 *       Revision:  none
 *       Compiler:  avr-gcc
 *
 *         Author:  Tanner Bruce, bruce.tanner@gmail.com
 *
 * =====================================================================================
 */
#define SUCCESS      0
#define FILTER_ERROR 1

struct lowpass_filter;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_filter
 *  Description:  Initializes the lowpass filter using the specified window size and
 *                alpha value
 * =====================================================================================
 */
uint8_t init_filter(struct lowpass_filter filter, uint8_t window_size, float alpha);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delete_filter
 *  Description:  Deletes the filter
 * =====================================================================================
 */
uint8_t delete_filter(struct lowpass_filter filter);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  push
 *  Description:  Pushes a new value to be used in the filter, and returns the new
 *                filtered value
 * =====================================================================================
 */
float push(struct lowpass_filter filter, float value);
