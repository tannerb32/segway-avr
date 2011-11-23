/*
 * =====================================================================================
 *
 *       Filename:  cmac.c
 *
 *    Description:  Implementation of the CMAC learning algorithm
 *
 *        Version:  1.0
 *        Created:  11/18/2011 08:20:58 PM
 *       Revision:  none
 *       Compiler:  gcc-avr
 *
 *         Author:  Tanner Bruce, bruce.tanner@gmail.com
 *
 * =====================================================================================
 */
#define ALPHA           0.1f 
#define DIMENSIONS 		2
#define TILES 			4
#define CELLS_PER_TILE 	10

#define X_MIN 150.0f
#define X_MAX 250.0f

//needs to be tuned
#define Y_MIN -30.0f
#define Y_MAX  30.0f

typedef struct CMAC
{

} cmac;

static cmac CMAC;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  alloc_cmac
 *  Description:  Allocates a new CMAC
 * =====================================================================================
 */
void alloc_cmac()
{

}
