#ifndef _PID_H_
#define _PID_H_
/*
 * =====================================================================================
 *
 *       Filename:  pid.h
 *
 *    Description:  :q
 *    
 *
 *        Version:  1.0
 *        Created:  11/23/2011 02:34:15 PM
 *       Revision:  none
 *       Compiler:  avr-gcc
 *
 *         Author:  Tanner Bruce (), bruce.tanner@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <inttypes.h>

void init() __attribute__ ((constructor));
void deinit() __attribute__ ((destructor));
void set_setpoint(float);
float get_setpoint();

int32_t get_pid(float);

#endif
