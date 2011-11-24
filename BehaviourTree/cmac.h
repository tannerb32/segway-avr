#ifndef _CMAC_H_
#define _CMAC_H_
/*
 * =====================================================================================
 *
 *       Filename:  cmac.h
 *
 *    Description:  Header file for a CMAC learning algorithm
 *
 *        Version:  1.0
 *        Created:  11/18/2011 08:19:43 PM
 *       Revision:  none
 *       Compiler:  gcc-avr
 *
 *         Author:  Tanner Bruce, bruce.tanner@gmail.com
 *
 * =====================================================================================
 */
#include <inttypes.h>

typedef struct CMAC cmac;

void alloc_cmac() __attribute__ ((constructor));

#endif // _CMAC_H_
