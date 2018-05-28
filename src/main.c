#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include <libmsp/watchdog.h>
#include <libmsp/gpio.h>
#include <libmsp/periph.h>
#include <libmsp/clock.h>
#include <libio/console.h>
#include <libcapybara/capybara.h>
#include <libcapybara/board.h>
#include <libcapybara/reconfig.h>

#ifdef DINO
#include <libdino/dino.h>
#else // !DINO
#define DINO_TASK_BOUNDARY(...)
#define DINO_RESTORE_CHECK()
#endif // !DINO

#include "pins.h"

// When using reconfiguration (LIBCAPYBARA_SWITCH_DESIGN is set) need to define:
// CAPYBARA_CFG_TABLE(0) = { };

volatile unsigned work_x;

static void burn(unsigned iters)
{
    unsigned iter = iters;
    while (iter--)
        work_x++;
}

int main() {
    msp_watchdog_disable();
    msp_gpio_unlock();

    capybara_init();
    msp_clock_setup();

    INIT_CONSOLE();
    __enable_interrupt();
    LOG("blinker app\r\n");

    capybara_board_init();

    GPIO(PORT_LED_1, DIR) |= BIT(PIN_LED_1);
    GPIO(PORT_LED_2, DIR) |= BIT(PIN_LED_2);
#if defined(PORT_LED_3)
    GPIO(PORT_LED_3, DIR) |= BIT(PIN_LED_3);
#endif

    DINO_RESTORE_CHECK();

    while(1) {

        DINO_TASK_BOUNDARY(0);

        GPIO(PORT_LED_1, OUT) ^= BIT(PIN_LED_1);

        for (int i = 0; i < 100; ++i)
            burn(10000);

        LOG("blink\r\n");
    }

    return 0;
}
