#ifndef _SEGWAY_H_
#define _SEGWAY_H_

typedef struct orient
{
    float pitch;
    float roll;
} orient_data;

typedef struct accel
{
	float x;
	float y;
	float z;
} accel_data;

struct motor_speed
{
    uint16_t left;
    uint16_t right;
};

void update(uint16_t, uint16_t, uint16_t);
void update_components();

void set_angle(float f);

//for debugging
void get_orient(struct orient *) __attribute__ ((unused));
void get_components(struct accel *) __attribute__ ((unused));
#endif
