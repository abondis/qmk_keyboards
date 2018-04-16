#ifndef KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
#define KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
// FIXME: move to config_user

#include "../chibios_common/config.h"

#undef MATRIX_ROWS
#undef MATRIX_COLS
#define MATRIX_ROWS 4
#define MATRIX_COLS 11 

#define PORTS {(GPIO_TypeDef *)GPIOA, (GPIO_TypeDef *)GPIOB}
#define PORTA 0
#define PORTB 1

#define MATRIX_COL_PINS                         {                                             \
    {PORTA, 0},{PORTA, 1},                      \
    {PORTA, 2},{PORTA, 3},                      \
    {PORTA, 4},{PORTA, 5},                      \
    {PORTA, 6},{PORTA, 7},                      \
    {PORTA, 8},{PORTA, 9},                      \
    {PORTA, 10}                                 \
  }

#define MATRIX_ROW_PINS                         {                                             \
    {PORTB, 12},                                \
    {PORTB, 13},                                \
    {PORTB, 14},                                \
    {PORTB, 15}                                 \
  }

#define DIODE_DIRECTION COL2ROW
#endif /* KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_ */
