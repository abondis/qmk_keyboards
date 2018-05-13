#ifndef KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
#define KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_
// FIXME: move to config_user

#include "../chibios_common/config.h"

#undef MATRIX_ROWS
#undef MATRIX_COLS
#define MATRIX_ROWS 4
#define MATRIX_COLS 11 

// #define PORTS {(GPIO_TypeDef *)GPIOA, (GPIO_TypeDef *)GPIOB}
#define PORTA 0
#define PORTB 1

#define PA(pin) (PAL_LINE(GPIOA, pin))
#define MATRIX_COL_PINS                                  \
    PAL_LINE(GPIOA, 0), PAL_LINE(GPIOA, 1),                \
      PAL_LINE(GPIOA, 2), PAL_LINE(GPIOA, 3),              \
      PAL_LINE(GPIOA, 4), PAL_LINE(GPIOA, 5),              \
      PAL_LINE(GPIOA, 6), PAL_LINE(GPIOA, 7),              \
      PAL_LINE(GPIOA, 8), PAL_LINE(GPIOA, 9),              \
    PAL_LINE(GPIOA, 10)


#define MATRIX_ROW_PINS                                                                      \
    PAL_LINE(GPIOB, 12), PAL_LINE(GPIOB, 13),                             \
    PAL_LINE(GPIOB, 14), PAL_LINE(GPIOB, 15)

#define DIODE_DIRECTION COL2ROW
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200
//#undef  PERMISSIVE_HOLD
#endif /* KEYBOARDS_STM32_F103_ATREUS_CONFIG_H_ */
