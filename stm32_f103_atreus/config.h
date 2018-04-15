#ifndef KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
#define KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
// FIXME: move to config_user

#include "../chibios_common/config.h"

#define MATRIX_ROW_PINS {
  {GPIOA, 0},{GPIOA, 1},
  {GPIOA, 2},{GPIOA, 3},
  {GPIOA, 4},{GPIOA, 5},
  {GPIOA, 6},{GPIOA, 7},
  {GPIOA, 8},{GPIOA, 9},
  {GPIOA, 10},
}
#define MATRIX_COL_PINS {
  {GPIOB, 12},
  {GPIOB, 13},
  {GPIOB, 14},
  {GPIOB, 15},
}
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

#define DIODE_DIRECTION COL2ROW
#endif /* KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_ */
