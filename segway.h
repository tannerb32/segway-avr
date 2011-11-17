#ifndef _SEGWAY_H_
#define _SEGWAY_H_

#define CALI_POINTS 10

uint16_t get_angle(uint16_t, uint16_t, uint16_t);

uint16_t add_cali_data(uint16_t, uint16_t, uint16_t);

void send_cali_data();
#endif
