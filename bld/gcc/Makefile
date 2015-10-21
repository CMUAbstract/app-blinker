EXEC = blinker.out

OBJECTS = \
	main.o \

BOARD ?= mspts430

include $(MAKER_ROOT)/Makefile.gcc

ifeq ($(BOARD),wisp)
CFLAGS += -DBOARD_WISP
endif

ifeq ($(BOARD),mspts430)
CFLAGS += -DBOARD_MSP_TS430
endif

CFLAGS += \

LFLAGS += \

LIBS += \

VPATH = ../../src
