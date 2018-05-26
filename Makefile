#export BOARD ?= msp-exp430fr5994
#export BOARD ?= wisp
#export BOARD ?= edb
export BOARD ?= capybara
export BOARD_MAJOR = 2
export BOARD_MINOR = 0

TOOLS = \
	mementos \
	dino \

TOOLCHAINS = \
	gcc \
	clang \
	mementos \
	dino \

# Paths to toolchains here if not in or different from defaults in Makefile.env

export MEMENTOS_ROOT ?= $(LIB_ROOT)/mementos
export DINO_ROOT ?= $(LIB_ROOT)/dino

EXEC = blinker

OBJECTS = \
	main.o \

DEPS += \
	libcapybara \
	libfxl:gcc \
	libmspware:gcc \
	libio \
	libmsp \

CONFIG_EDB ?= 0

ifeq ($(BOARD),edb)
DEPS += libmspware:gcc

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

export LIBMSP_SLEEP_TIMER = B.0.0
export LIBMSP_SLEEP_TIMER_CLK = ACLK
export LIBMSP_SLEEP_TIMER_DIV = 8*1

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

export LIBIO_BACKEND = hwuart
export LIBMSP_UART_IDX = 0
export LIBMSP_UART_PIN_TX = 2.0
export LIBMSP_UART_BAUDRATE = 115200
export LIBMSP_UART_CLOCK = SMCLK
export LIBMSP_SLEEP = 0

ifeq ($(BOARD),capybara)

export LIBCAPYBARA_VBANK_COMP_REF = 1.2 # V
export LIBCAPYBARA_VBANK_COMP_SETTLE_MS = 0.25

export LIBCAPYBARA_DEEP_DISCHARGE = 1.8 # V

# If using reconfiguration, remember to define the power config table
#export LIBCAPYBARA_NUM_BANKS = 4
#export LIBCAPYBARA_SWITCH_DESIGN = NO
#export LIBCAPYBARA_SWITCH_CONTROL = ONE_PIN

ifeq ($(BOARD_MAJOR),1)

ifeq ($(BOARD_MINOR),0)
export LIBCAPYBARA_PIN_VBOOST_OK = 2.3
else ifeq ($(BOARD_MINOR),1)
export LIBCAPYBARA_PIN_VBOOST_OK = 3.4
endif # BOARD_MINOR

export LIBCAPYBARA_PIN_VBANK_OK = 2.2
export LIBCAPYBARA_PIN_BOOST_SW = 2.7
export LIBCAPYBARA_VBANK_DIV = 10:20
export LIBCAPYBARA_VBANK_COMP_CHAN = E.11 # comparator type and channel for Vbank voltage
export LIBCAPYBARA_VBANK_COMP_PIN = 2.4

ifeq ($(LIBCAPYBARA_SWITCH_CONTROL),ONE_PIN)
export LIBCAPYBARA_BANK_PORT_0 = J.0
export LIBCAPYBARA_BANK_PORT_1 = J.2
export LIBCAPYBARA_BANK_PORT_2 = J.4
export LIBCAPYBARA_BANK_PORT_3 = 4.0
else ifeq ($(LIBCAPYBARA_SWITCH_CONTROL),TWO_PIN)
export LIBCAPYBARA_BANK_PORT_0_OPEN  ?= J.0
export LIBCAPYBARA_BANK_PORT_0_CLOSE ?= J.1
export LIBCAPYBARA_BANK_PORT_1_OPEN  ?= J.2
export LIBCAPYBARA_BANK_PORT_1_CLOSE ?= J.3
export LIBCAPYBARA_BANK_PORT_2_OPEN  ?= J.4
export LIBCAPYBARA_BANK_PORT_2_CLOSE ?= J.5
export LIBCAPYBARA_BANK_PORT_3_OPEN  ?= 4.0
export LIBCAPYBARA_BANK_PORT_3_CLOSE ?= 4.1
endif # LIBCAPYBARA_SWITCH_CONTROL

else ifeq ($(BOARD_MAJOR),2)

export LIBCAPYBARA_PIN_VBOOST_OK = 3.6
export LIBCAPYBARA_PIN_VBANK_OK = 3.7
export LIBCAPYBARA_PIN_BOOST_SW = 4.5
export LIBCAPYBARA_VBANK_DIV = 10:4.22
# comparator type and channel for Vbank voltage
export LIBCAPYBARA_VBANK_COMP_CHAN = E.13
export LIBCAPYBARA_VBANK_COMP_PIN = 3.1

ifeq ($(LIBCAPYBARA_SWITCH_CONTROL),ONE_PIN)
export LIBCAPYBARA_BANK_PORT_0 = J.0
export LIBCAPYBARA_BANK_PORT_1 = J.1
export LIBCAPYBARA_BANK_PORT_2 = J.2
export LIBCAPYBARA_BANK_PORT_3 = J.3
else ifneq ($(LIBCAPYBARA_SWITCH_CONTROL),)
$(error Given switch control type not supported on given board version)
endif # LIBCAPYBARA_SWITCH_CONTROL

endif # BOARD_MAJOR
endif # BOARD == capybara


include ext/maker/Makefile
