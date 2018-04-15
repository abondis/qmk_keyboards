/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "config.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
static const uint8_t col_pins[][2] = MATRIX_COL_PINS;
static const uint8_t row_pins[][2] = MATRIX_ROW_PINS;
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static GPIO_TypeDef * _PORTS[] = PORTS; 

// static matrix_row_t read_cols(void);
static void init_cols(void);
static void init_rows(void);
static void unselect_rows(void);
static void select_row(uint8_t row);
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);


/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
#define LED_ON()    do { palClearPad(GPIOC, GPIOC_LED) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, GPIOC_LED); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, GPIOC_LED); } while (0)
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON()    do { palSetPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palClearPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

void matrix_init(void) {


  unselect_rows();
  init_rows();
  init_cols();

  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
#       if (DEBOUNCING_DELAY > 0)
            bool matrix_changed = read_cols_on_row(matrix_debouncing, current_row);

            if (matrix_changed) {
                debouncing = true;
                debouncing_time = timer_read();
            }

#       else
            read_cols_on_row(matrix, current_row);
#       endif

    }



#   if (DEBOUNCING_DELAY > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_quantum();
    return 1;
}

/* Column pin configuration
 */
static void  init_cols(void)
{
  for(uint8_t x = 0; x < MATRIX_COLS; x++) {
    palSetPadMode(_PORTS[row_pins[x][0]], row_pins[x][1], PAL_MODE_INPUT_PULLUP);
  }
}

static void  init_rows(void)
{
  for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
    palSetPadMode(_PORTS[row_pins[x][0]], row_pins[x][1], PAL_MODE_OUTPUT_PUSHPULL);
  }
}
/* Row pin configuration
 */
static void unselect_row(uint8_t row)
{
  palSetPad(_PORTS[row_pins[row][0]], row_pins[row][1]);
}

static void unselect_rows(void)
{
  for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
    unselect_row(x);
  }
}

static void select_row(uint8_t row)
{
  // Output low to select
  palClearPad(_PORTS[row_pins[row][0]], row_pins[row][1]);
}

/* Returns status of switches(1:on, 0:off) */
/* FIXME: COPY PASTA FROM CORE */
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Clear data in matrix row
  current_matrix[current_row] = 0;

  // Select row and wait for row selecton to stabilize
  select_row(current_row);
  wait_us(30);

  // For each col...
  for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

    // Select the col pin to read (active low)
    uint8_t pin_state = palReadPad(_PORTS[col_pins[col_index][0]], col_pins[col_index][1])==PAL_HIGH;

    // Populate the matrix row with the state of the col pin
    current_matrix[current_row] |=  pin_state ? 0 : (1 << col_index);
  }

  // Unselect row
  unselect_row(current_row);

  return (last_row_value != current_matrix[current_row]);
}

