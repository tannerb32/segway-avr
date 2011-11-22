/*
 * sound_driver.h
 *
 * Created: 11/2/2011 3:27:58 PM
 *  Author: jacky
 */


#ifndef SOUND_DRIVER_H_
#define SOUND_DRIVER_H_

/* Some music theory and frequencies
 A_0   = 440Hz              ICR = 18182
 BF_0  = 466Hz  B Flat      ICR = 17167
 B_0   = 494                ICR = 16194
 C_0   = 523                ICR = 15296
 CS_0  = 554    C Sharp     ICR = 14440
 D_0   = 587                ICR = 13628
 DS_0  = 622                ICR = 12861
 E_0   = 659                ICR = 12140
 F_0   = 698                ICR = 11461
 FS_0  = 740                ICR = 10811
 G_0   = 784                ICR = 10204
 AF_0  = 831                ICR =  9626

 A_1   = 880                ICR =  9091
*/

/* Constants for the musical notes */
#define INVALID_NOTE 0
#define A_0         (18182)
#define BF_0        (17167)
#define B_0         (16194)
#define C_0         (15296)
#define CS_0        (14440)
#define D_0         (13628)
#define DS_0        (12861)
#define E_0         (12140)
#define F_0         (11461)
#define FS_0        (10811)
#define G_0         (10204)
#define AF_0        (9626)

#define A_1         (9091)
#define BF_1        (8584)
#define B_1         (8097)
#define C_1         (7648)
#define CS_1        (7220)
#define D_1         (6814)
#define DS_1        (6431)
#define E_1         (6070)
#define F_1         (5731)
#define FS_1        (5405)
#define G_1         (5102)
#define AF_1        (4813)

#define A_2         (4545)

#include <avr/io.h>

#include "robot.h"

struct Note
{
    uint16_t freq;
    uint16_t volume;
    uint16_t duration;
};

#if defined(USE_SOUND)

#if ROBOT == 3
/* Sound on the Educational Platform Version 3 uses OCR3A
    SOUND_MODE=1: OC0/PB4  INVALID for sound
    SOUND_MODE=2: OC2/PB7 same as OC1C INVALID for sound
    SOUND_MODE=3: OC1A/PB5
    SOUND_MODE=4: OC1B/PB6
    SOUND_MODE=5: OC1C/PB7 same as OC2
    SOUND_MODE=6: OC3A/PE3
    SOUND_MODE=7: OC3B/PE4
    SOUND_MODE=8: OC3C/PE5
 */
#define SOUND_MODE 6
#else
#   error "Unknown robot definition"
#endif

#if SOUND_MODE == 3
#   define SOUND_PORT                       PORTB
#   define SOUND_PORT_DIRECTION             DDRB
#   define SOUND_PORT_MASK                  (1 << PB5)
#   define SOUND_PITCH                      ICR1
#   define SOUND_VOLUME                     OCR1A
#elif SOUND_MODE == 4
#   define SOUND_PORT                       PORTB
#   define SOUND_PORT_DIRECTION             DDRB
#   define SOUND_PORT_MASK                  (1 << PB6)
#   define SOUND_PITCH                      ICR1
#   define SOUND_VOLUME                     OCR1B
#elif SOUND_MODE == 5
#   define SOUND_PORT                       PORTB
#   define SOUND_PORT_DIRECTION             DDRB
#   define SOUND_PORT_MASK                  (1 << PB7)
#   define SOUND_PITCH                      ICR1
#   define SOUND_VOLUME                     OCR1C
#elif SOUND_MODE == 6
#   define SOUND_PORT                       PORTE
#   define SOUND_PORT_DIRECTION             DDRE
#   define SOUND_PORT_MASK                  (1 << PE3)
#   define SOUND_PITCH                      ICR3
#   define SOUND_VOLUME                     OCR3A
#elif SOUND_MODE == 7
#   define SOUND_PORT                       PORTE
#   define SOUND_PORT_DIRECTION             DDRE
#   define SOUND_PORT_MASK                  (1 << PE4)
#   define SOUND_PITCH                      ICR3
#   define SOUND_VOLUME                     OCR3B
#elif SOUND_MODE == 8
#   define SOUND_PORT                       PORTE
#   define SOUND_PORT_DIRECTION             DDRE
#   define SOUND_PORT_MASK                  (1 << PE5)
#   define SOUND_PITCH                      ICR3
#   define SOUND_VOLUME                     OCR3C
#else
#   error "Unknown SOUND_MODE Definition for sound"
#endif /* SOUND_MODE */

void initSoundSubSystem(void);

#endif /* USE_SOUND */

#endif /* SOUND_DRIVER_H_ */
