#ifndef PIN_ASSIGN_H
#define PIN_ASSIGN_H

#if defined(BOARD_WISP)

#define     PORT_LED_1           4
#define     PIN_LED_1            0
#define     PORT_LED_2           J
#define     PIN_LED_2            6

#elif defined(BOARD_MSPTS430) || \
      defined(BOARD_MSPEXP430FR5994) || \
      defined(BOARD_CAPYBARA)

#define     PORT_LED_1           1
#define     PIN_LED_1            1
#define     PORT_LED_2           1
#define     PIN_LED_2            2
#define     PORT_LED_3           1
#define     PIN_LED_3            0

#elif defined(BOARD_EDB)

#define     PORT_LED_1           J
#define     PIN_LED_1            0
#define     PORT_LED_2           J
#define     PIN_LED_2            1
#define     PORT_LED_3           J
#define     PIN_LED_3            2

#endif // BOARD_*

#endif
