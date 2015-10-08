#ifndef PIN_ASSIGN_H
#define PIN_ASSIGN_H

// Ugly workaround to make the pretty GPIO macro work for OUT register
// (a control bit for TAxCCTLx uses the name 'OUT')
#undef OUT

#define BIT_INNER(idx) BIT ## idx
#define BIT(idx) BIT_INNER(idx)

#define GPIO_INNER(port, reg) P ## port ## reg
#define GPIO(port, reg) GPIO_INNER(port, reg)

// #define BOARD_WISP
#define BOARD_MSP_TS430RGZ

#if defined(BOARD_WISP)

#define     PORT_LED           4
#define 	PIN_LED			   0

#elif defined(BOARD_MSP_TS430RGZ)

#define     PORT_LED1           1
#define 	PIN_LED1			0

#endif // BOARD_*

#endif
