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
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
// static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

// static matrix_row_t read_cols(void);
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


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


/* Column pin configuration
 */
static void  init_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COL_PINS; x++) {
      uint8_t pin = row_pins[x];
      palSetPadMode(pin[0], pin[1], PAL_MODE_INPUT_PULLUP);
    }
}

static void  init_rows(void)
{
  for(uint8_t x = 0; x < MATRIX_ROW_PINS; x++) {
    uint8_t pin = row_pins[x];
    palSetPadMode(pin[0], pin[1], PAL_MODE_OUTPUT_PUSHPULL);
  }
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
    uint8_t pin[2] = col_pins[col_index];
    uint8_t pin_state = palReadPad(pin[0], pin[1])==PAL_HIGH;

    // Populate the matrix row with the state of the col pin
    current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
  }

  // Unselect row
  unselect_row(current_row);

  return (last_row_value != current_matrix[current_row]);
}

/* Row pin configuration
 */
static void unselect_row(uint8_t row)
{
  palSetPad(row_pins[row][0], row_pins[row][1]);
}

static void unselect_rows(void)
{
  for(uint8_t x = 0; x < MATRIX_ROW_PINS; x++) {
    unselect_row(x);
  }
}

static void select_row(uint8_t row)
{
  // Output low to select
  palClearPad(row_pins[row][0], row_pins[row][1]);
}
