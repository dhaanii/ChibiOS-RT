# List of the ChibiOS/RT Posix port files.
PORTSRC = ${CHIBIOS}/os/ports/GCC/Posix/chcore.c \
		  ${CHIBIOS}/os/various/memstreams.c

BOARDSRC = ${CHIBIOS}/boards/simulator/board.c

PORTINC = ${CHIBIOS}/os/ports/GCC/Posix \
          ${CHIBIOS}/boards/simulator

# size command def
SZ = size

# Never have the linker remove unused code and data
USE_LINK_GC = no

# ARM-only option that shouldn't be used in the simulator
USE_THUMB = no
