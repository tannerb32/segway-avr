#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "segway.h"

#define CALI_COUNT 10

#if defined(HIGH_RESOLUTION)
#define ADC_RES 1024
#else
#define ADC_RES 255
#endif

#define Vref  5000
#define zeroG 2500.0f
#define sens   500

#define speed_ratio 1.25f

struct prev_data
{
    orient_data angles;
    accel_data accel;
};

struct curr_data
{
    orient_data angles;
    accel_data  accel;
};

struct motor_speed
{
    uint16_t left;
    uint16_t right;
};

struct segway
{
    struct motor_speed;
    struct prev_data pdata;
    struct curr_data cdata;
    float ch_angle;
    float set_point;
};

static struct segway segway; 

void update(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
    segway.pdata.angles = segway.cdata.angles;
    segway.pdata.accel  = segway.cdata.accel;

    segway.cdata.accel.accel_x = accel_x;
    segway.cdata.accel.accel_y = accel_y;
    segway.cdata.accel.accel_z = accel_z;

    update_components(accel_x, accel_y, accel_z);

    segway.ch_angle = segway.cdata.angles.pitch - segway.pdata.angles.pitch;
}

void update_components(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
    float x = (((accel_x * Vref) / ADC_RES) - zeroG) / sens;
    float y = (((accel_y * Vref) / ADC_RES) - zeroG) / sens;
    float z = (((accel_z * Vref) / ADC_RES) - zeroG) / sens;

    segway.cdata.angles->pitch = atan2(x, sqrt(y*y + z*z)) * 10; 
    segway.cdata.angles->roll  = atan2(y, sqrt(2*z*z)) * 10;  
}

struct accel *get_components(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
    struct accel *ac = malloc(sizeof(struct accel));

    ac->accel_x = (((accel_x * Vref) / ADC_RES) - zeroG) / sens;
    ac->accel_y = (((accel_y * Vref) / ADC_RES) - zeroG) / sens;
    ac->accel_z = (((accel_z * Vref) / ADC_RES) - zeroG) / sens;

    return ac;
}

struct orient *get_orient(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
    struct orient *or = malloc(sizeof(struct orient));

    float x = (((accel_x * Vref) / ADC_RES) - zeroG) / sens;
    float y = (((accel_y * Vref) / ADC_RES) - zeroG) / sens;
    float z = (((accel_z * Vref) / ADC_RES) - zeroG) / sens;

    or->pitch = atan2(x, sqrt(y*y + z*z)) * 10; 
    or->roll  = atan2(y, sqrt(z*z + z*z)) * 10;  

    return or;
}
