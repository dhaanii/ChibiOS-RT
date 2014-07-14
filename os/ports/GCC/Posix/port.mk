# List of the ChibiOS/RT Posix port files.
PORTSRC = ${CHIBIOS}/os/ports/GCC/Posix/chcore.c \
		  ${CHIBIOS}/os/various/memstreams.c
# PORTSRC = $(CHIBIOS)/os/ports/GCC/ARMCMx/crt0.c \
#           $(CHIBIOS)/os/ports/GCC/ARMCMx/STM32F4xx/vectors.c \
#           ${CHIBIOS}/os/ports/GCC/ARMCMx/chcore.c \
#           ${CHIBIOS}/os/ports/GCC/ARMCMx/chcore_v7m.c \
#           ${CHIBIOS}/os/ports/common/ARMCMx/nvic.c

BOARDSRC = ${CHIBIOS}/boards/simulator/board.c

PORTINC = ${CHIBIOS}/os/ports/GCC/Posix \
          ${CHIBIOS}/boards/simulator

# PORTLD  = ${CHIBIOS}/os/ports/GCC/ARMCMx/STM32F4xx/ld
