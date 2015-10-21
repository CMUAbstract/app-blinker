EXEC = blinker.out

OBJECTS = \
	main.o \

BOARD ?= mspts430

include $(MAKER_ROOT)/Makefile.clang

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
