# MCU name
MCU                 =   atmega32u4
# BOOTLOADER          =   atmel-dfu
# Might not be needed
F_CPU = 8000000

CUSTOM_MATRIX       =   no
VIRTSER_ENABLE      =   no
NKRO_ENABLE         =   no
BLUETOOTH           =   AdafruitBLE
DEBOUNCE_TYPE       =   eager_pr

# Lets try and save some space eh?
MOUSEKEY_ENABLE     =   no
EXTRAKEY_ENABLE     =   no
CONSOLE_ENABLE      =   yes
COMMAND_ENABLE      =   no

VPATH               +=  keyboards/abondis/ 
# SRC                 +=  matrix.c g/engine.c config_engine.c
SRC                 +=  g/engine.c config_engine.c
# QUANTUM_LIB_SRC     +=  i2c_master.c
OPT_DEFS            +=  -DONLYQWERTY 
LTO_ENABLE          =   yes
# BOOTLOADER          =   catarina

PS2_MOUSE_ENABLE = yes
PS2_USE_INT = yes
