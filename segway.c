#include <stdio.h>
#include <math.h>
#include "segway.h"

struct accel
{
	uint16_t accel_x;
	uint16_t accel_y;
	uint16_t accel_z;
};

/* PRIVATE FUNCTIONS */
struct accel *get_components(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z);


/* PRIVATE GLOBALS */
static uint16_t sens_l[CALI_COUNT];
static uint16_t sens_r[CALI_COUNT];
static uint16_t sens_m[CALI_COUNT];

uint16_t get_angle(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
	struct accel ac;
	
	float theta = cos(abs(accel_z), 9.81);
}

uint8_t add_cali_data(uint16_t light_l, uint16_t light_r, uint16_t light_m,
					   uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
	static int indice = 0;

	if(indice > 10)
		return 0;

	sens_l[indice] = light_l;
	sens_r[indice] = light_r;
	sens_m[indice] = light_m;

	++indice;

	return 1;
}

struct accel *get_components(uint16_t accel_x, uint16_t accel_y, uint16_t accel_z)
{
	memset(&ac, 0, sizeof(struct accel));

}

