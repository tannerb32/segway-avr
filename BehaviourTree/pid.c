/*
 * =====================================================================================
 *
 *       Filename:  pid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/23/2011 02:37:36 PM
 *       Revision:  none
 *       Compiler:  avr-gcc
 *
 *         Author:  Tanner Bruce (), bruce.tanner@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "pid.h"

#define Kp 5.0f                                 /* Proportional gain */
#define Ki 0.03f                                 /* Integral gain */
#define Kd 0.5f                                 /* Derivative gain */

#define It 10                                   /* Int. iterations to keep */

static uint8_t first;                           /* First run */
static float set_point;                         /* Current set point (angle) */

static float prev_error;                        /* Previous error */
static float int_error;                         /* Accumulated integ. error */
static float der_error;                         /* Derivative error */
static float pro_error;                         /* Proportional error */

static uint8_t int_index;                       /* Current index of integral */
static float *int_error_list;                   /* List of prev. int. errors */

void init()
{
    first          = 1;
    set_point      = 188.0f; 
    prev_error     = 0.0f;
    int_error_list = (float *)calloc(It, sizeof(float));
    int_error      = 0.0f;
    int_index      = 0;
}

void deinit()
{
    free(int_error_list);
}

void set_setpoint(float f) { set_point = f; }
float get_setpoint() { return set_point; }

int32_t get_pid(float cur_angle)
{
    float pro_error, der_error, sign;
    float error = set_point - cur_angle;
    int32_t pid;

    if(cur_angle > 230.0f || cur_angle < 140.0f)
    {
        prev_error = error;
        return 0;
    }

    if(first)
    {
        prev_error = error;
        --first;
        return 0;
    }
    
    // Only keep track of the last # iterations
    // to prevent integral windup
    int_error = (int_error - int_error_list[int_index]) + error;
    int_error_list[int_index] = error;
    int_index = (int_index >= It - 1 ? 0 : int_index + 1);
         
    pro_error = error;
    der_error = error - prev_error;
    prev_error = error;
    
    pid = Kp * pro_error + Ki * int_error + Kd * der_error * -1;
    
    if(pid > -10 && pid < 10)
        return 0;
    return pid;
}
