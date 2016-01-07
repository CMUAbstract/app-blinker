#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

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
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;

    GPIO(PORT_LED1, DIR) |= BIT(PIN_LED1);

    // set clock speed to 4 MHz
    CSCTL0_H = 0xA5;
    CSCTL1 = DCOFSEL0 | DCOFSEL1;
    CSCTL2 = SELA_0 | SELS_3 | SELM_3;
    CSCTL3 = DIVA_0 | DIVS_0 | DIVM_0;
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
