// #define ENABLE_WATCHDOG


#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include "pins.h"

// TODO: the interval calculation doesn't add up for some reason
#define WATCHDOG_INTERVAL_BITS WDTIS__8192K // by trial and error: yields a few seconds

volatile unsigned work_x;

static void burn(unsigned iters)
{
    unsigned iter = iters;
    while (iter--)
        work_x++;
}

static void init_hw()
{
#ifndef ENABLE_WATCHDOG
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
#endif

    PM5CTL0 &= ~LOCKLPM5;

    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    PJOUT = 0x00;
    P1DIR = 0x00;
    PJDIR = 0x00;
    P2DIR = 0x00;
    P3DIR = 0x00;
    P4DIR = 0x00;

    GPIO(PORT_LED1, DIR) |= BIT(PIN_LED1);

    // set clock speed to 4 MHz
    CSCTL0_H = 0xA5;
    CSCTL1 = DCOFSEL0 | DCOFSEL1;
    CSCTL2 = SELA_0 | SELS_3 | SELM_3;
    CSCTL3 = DIVA_0 | DIVS_0 | DIVM_0;

#ifdef ENABLE_WATCHDOG
    WDTCTL = WDTPW | WATCHDOG_INTERVAL_BITS | WDTCNTCL;
#endif
}

int main() {
    uint32_t i;

    init_hw();

    while(1) {
#ifdef ENABLE_WATCHDOG
        WDTCTL = WDTPW | WATCHDOG_INTERVAL_BITS | WDTCNTCL;  // poke watchdog
#endif

        GPIO(PORT_LED1, OUT) ^= BIT(PIN_LED1);

        for (i = 0; i < 100; ++i)
            burn(500);
    }

    return 0;
}
