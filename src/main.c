#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include <libmsp/watchdog.h>
#include <libmsp/gpio.h>
#include <libmsp/periph.h>
#include <libmsp/clock.h>
#include <libio/console.h>

#include "pins.h"

volatile unsigned work_x;

static void burn(unsigned iters)
{
    unsigned iter = iters;
    while (iter--)
        work_x++;
}

static void init_hw()
{
    msp_watchdog_disable();
    msp_gpio_unlock();
    msp_clock_setup();

    INIT_CONSOLE();
    __enable_interrupt();
    LOG("blinker app\r\n");

    GPIO(PORT_LED1, DIR) |= BIT(PIN_LED1);
}

int main() {
    uint32_t i;

    init_hw();

    while(1) {

        GPIO(PORT_LED1, OUT) ^= BIT(PIN_LED1);

        for (i = 0; i < 100; ++i)
            burn(500);
    }

    return 0;
}
