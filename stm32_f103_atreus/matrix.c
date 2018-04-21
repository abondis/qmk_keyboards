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


#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void init_rows(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

static const ioline_t col_pins[MATRIX_COLS] = {MATRIX_COL_PINS};
static const ioline_t row_pins[MATRIX_ROWS] = {MATRIX_ROW_PINS};

inline uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
#define LED_LINE PAL_LINE(GPIOC, GPIOC_LED)
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_LINE PAL_LINE(GPIOB, 1)
#endif

#ifdef LED_LINE
#define LED_ON()    do { palClearLine(LED_LINE) ;} while (0)
#define LED_OFF()   do { palSetLine(LED_LINE); } while (0)
#define LED_TGL()   do { palToggleLine(LED_LINE); } while (0)
#endif

void matrix_init(void)
{
    // initialize row and col
    init_cols();
    init_rows();
    unselect_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

}

uint8_t matrix_scan(void)
{
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(50);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    if (matrix_debouncing[i] != cols) {
      matrix_debouncing[i] = cols;
      if (debouncing) {
        debug("bounce!: "); debug_hex(debouncing); debug("\n");
      }
      debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing) {
    if (--debouncing) {
      wait_ms(1);
    } else {
      for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = matrix_debouncing[i];
      }
    }
  }

  return 1;
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 */
static void  init_cols(void)
{
  for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    palSetLineMode(col_pins[i], PAL_MODE_INPUT_PULLUP);
  }
}

static void  init_rows(void)
{
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    palSetLineMode(row_pins[i], PAL_MODE_OUTPUT_PUSHPULL);
  }
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
  matrix_row_t col = 0;
  for (uint8_t i = 0; i < MATRIX_COLS; i++) {
    col |= ((palReadLine(col_pins[i]) == PAL_HIGH) ? 0 : (1<<i));
  }
  return col;
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    palSetLine(row_pins[i]);
  }
}

static void select_row(uint8_t row)
{
  palClearLine(row_pins[row]);
}
