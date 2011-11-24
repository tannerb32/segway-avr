#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "segway.h"

#if defined(HIGH_RESOLUTION)
#define ADC_RES 1023
#else
#define ADC_RES 255
#endif

#define Vref  5000.0f
#define zeroG 2500.0f
#define sens  500

#define speed_ratio 1.25f

void update_components();

struct data
{
    orient_data angles;
    accel_data  accel;
};


struct motor_speed speed;
static struct data pdata;
static struct data cdata;
static float ch_angle;
static float set_point;

void update(accel_x, accel_y, accel_z)
uint16_t accel_x, accel_y, accel_z;
{
    pdata.angles = cdata.angles;
    pdata.accel  = cdata.accel;
    cdata.accel.x = (((accel_x * Vref) / ADC_RES) - zeroG) / sens;
    cdata.accel.y = (((accel_y * Vref) / ADC_RES) - zeroG) / sens;
    cdata.accel.z = (((accel_z * Vref) / ADC_RES) - zeroG) / sens;
    update_components();
    ch_angle = cdata.angles.roll - pdata.angles.roll;
}

void update_components()
{
    float x = cdata.accel.x;
    float y = cdata.accel.y;
    float z = cdata.accel.z;
    cdata.angles.pitch = atan2(x, sqrt(y * y + z * z)) * 10;
    cdata.angles.roll  = atan2(y, sqrt(z * z + z * z)) * 10;
}


void set_angle(float f)
{
    set_point = f;
}

/* ACCESSORS */
void get_components(struct accel *ac)
{
    ac->x = cdata.accel.x;
    ac->y = cdata.accel.y;
    ac->z = cdata.accel.z;
}

void get_orient(struct orient *or)
{
    or->pitch = cdata.angles.pitch;
    or->roll  = cdata.angles.roll;
}
