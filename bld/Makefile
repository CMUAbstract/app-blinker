EXEC = blinker

OBJECTS = \
	main.o \

DEPS += \
	libmsp \
	libio \

CONFIG_EDB ?= 0

ifeq ($(BOARD),edb)
DEPS += libmspware

export LIBMSP_XT1_FREQ = 32678
export LIBMSP_XT1_CAP = 12
export LIBMSP_XT2_FREQ = 12000000
export LIBMSP_CLOCK_SOURCE = DCO
export LIBMSP_DCO_REF_SOURCE = XT2
export LIBMSP_DCO_REF_CLOCK_DIV = 4


export LIBMSP_STARTUP_VOLTAGE_WORKAROUNDS = disable-pmm
export LIBMSP_CORE_VOLTAGE_LEVEL = 3

export MAIN_CLOCK_FREQ = 24000000
else # BOARD != sprite-edb
export MAIN_CLOCK_FREQ = 8000000
endif # BOARD != sprite-edb


export CLOCK_FREQ_ACLK = 32768
export CLOCK_FREQ_SMCLK = $(MAIN_CLOCK_FREQ)
export CLOCK_FREQ_MCLK = $(MAIN_CLOCK_FREQ)

export LIBMSP_CLOCK_SOURCE = DCO
export LIBMSP_DCO_FREQ = $(MAIN_CLOCK_FREQ)

# Sleep currently not supported with Clang
#export LIBMSP_SLEEP_TIMER = B.0.0
#export LIBMSP_SLEEP_TIMER_CLK = ACLK
#export LIBMSP_SLEEP_TIMER_DIV = 8*1

# To use add: libmspsoftuart to DEPS
#export LIBIO_BACKEND = swuart
#ifeq ($(BOARD_MAJOR),1)
#export LIBMSPSOFTUART_PIN_TX = 3.6
#else ifeq ($(BOARD_MAJOR),2)
#export LIBMSPSOFTUART_PIN_TX = 3.5
#endif # BOARD_MAJOR
#export LIBMSPSOFTUART_BAUDRATE = 9600
#export LIBMSPSOFTUART_CLOCK_FREQ = $(MAIN_CLOCK_FREQ)
#export LIBMSPSOFTUART_TIMER = B.0.5

# UART currently not supported with Clang
#export LIBIO_BACKEND = hwuart
#export LIBMSP_UART_IDX = 0
#export LIBMSP_UART_PIN_TX = 2.0
#export LIBMSP_UART_BAUDRATE = 115200
#export LIBMSP_UART_CLOCK = SMCLK
