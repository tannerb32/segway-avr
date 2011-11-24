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
#define ALPHA           0.1f                    /* Learning rate */

#define DIMENSIONS      2                       /* Number of axis */
#define TILES_X         32                      /* Tiles over X axis */
#define TILES_Y         8                       /* Tiles over Y axis */
#define TILE_X_WIDTH    2.0f                    /* Tile width over X*/
#define TILE_Y_WIDTH    0.5f                    /* Tile width over Y*/
#define MEM_SIZE        TILES_X * TILES_Y 

#define X_MIN 150.0f                            /* Angle */
#define X_MAX 250.0f

//needs to be tuned
#define Y_MIN -30.0f                            /* Angle hat */
#define Y_MAX  30.0f

typedef struct CMAC
{

} cmac;

static cmac CMAC;
static float *weights;
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  alloc_cmac
 *  Description:  Allocates a new CMAC
 * =====================================================================================
 */
void alloc_cmac()
{

}
