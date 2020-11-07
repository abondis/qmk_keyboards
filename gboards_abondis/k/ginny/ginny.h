#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>


/* #define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n)) */
/* #define CPU_16MHz       0x00 */

/*  -------- LEFT HAND------RIGHT HAND ---------- */
#define LAYOUT_ginny( L00,L01,L02,L03,L04, R00,R01,R02,R03,R04 ) { \
                        \
    {L04, L03, L02, L00, L01},                  \
    {R00, R01, R02, R04, R03 }      \
}

    /*{ KC_NO,  L04},  	  \
    {	KC_NO,  L03},    \
    {	KC_NO,  L02},    \
    { KC_NO,  L01},   	\
    { L00, 		KC_NO },    \*/
