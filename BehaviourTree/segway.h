#ifndef _SEGWAY_H_
#define _SEGWAY_H_

typedef struct orient
{
    double pitch;
    double roll;
} orient_data;

//TODO: accel_x -> x etc
typedef struct accel
{
	double accel_x;
	double accel_y;
	double accel_z;
} accel_data;

void update(uint16_t, uint16_t, uint16_t);

uint16_t get_angle(uint16_t, uint16_t, uint16_t);
void update_components(uint16_t, uint16_t, uint16_t);

uint8_t add_cali_data(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
struct orient *get_orient(uint16_t, uint16_t, uint16_t);
struct accel *get_components(uint16_t, uint16_t, uint16_t);

void send_cali_data();
#endif
