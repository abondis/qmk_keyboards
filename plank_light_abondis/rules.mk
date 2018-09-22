SRC += muse.c

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

MOUSEKEY_ENABLE = yes        # Mouse keys(+4700)
STENO_ENABLE = no          # Additional protocols for Stenography(+1700), requires VIRTSER
MIDI_ENABLE = yes            # MIDI controls
CONSOLE_ENABLE = no            # MIDI controls
SERIAL_ENABLE = no            # MIDI controls
