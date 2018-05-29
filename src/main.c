#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

#include <libmsp/watchdog.h>
#include <libmsp/gpio.h>
#include <libmsp/periph.h>
#include <libmsp/clock.h>
#include <libio/console.h>

#ifdef BOARD_CAPYBARA
#include <libcapybara/capybara.h>
#include <libcapybara/board.h>
#include <libcapybara/reconfig.h>
#endif // BOARD_CAPYBARA

#include <libalpaca/alpaca.h>

#include "pins.h"

#define INIT_TASK_DURATION_ITERS  400000
#define TASK_START_DURATION_ITERS 1600000
#define BLINK_DURATION_ITERS      400000
#define WAIT_TICK_DURATION_ITERS  300000
#define NUM_BLINKS_PER_TASK       5
#define WAIT_TICKS                3

TASK(task_init)
TASK(task_1)
TASK(task_2)
TASK(task_3)

GLOBAL_SB(unsigned, blinks);
GLOBAL_SB(unsigned, tick);
GLOBAL_SB(unsigned, duty_cycle);
GLOBAL_SB(unsigned, wait_tick);

// When using reconfiguration (LIBCAPYBARA_SWITCH_DESIGN is set) need to define:
// CAPYBARA_CFG_TABLE(0) = { };

volatile unsigned work_x;

static void burn(uint32_t iters)
{
    uint32_t iter = iters;
    while (iter--)
        work_x++;
}

void init() {
    msp_watchdog_disable();
    msp_gpio_unlock();

#ifdef BOARD_CAPYBARA
    capybara_init();
#endif // BOARD_CAPYBARA

    msp_clock_setup();

    INIT_CONSOLE();
    __enable_interrupt();
    LOG("blinker app\r\n");

#ifdef BOARD_CAPYBARA
    capybara_board_init();
#endif // BOARD_CAPYBARA

    GPIO(PORT_LED_1, DIR) |= BIT(PIN_LED_1);
    GPIO(PORT_LED_2, DIR) |= BIT(PIN_LED_2);
#if defined(PORT_LED_3)
    GPIO(PORT_LED_3, DIR) |= BIT(PIN_LED_3);
#endif
}

static void blink_led1(unsigned blinks, unsigned duty_cycle) {
    unsigned i;

    for (i = 0; i < blinks; ++i) {
        GPIO(PORT_LED_1, OUT) |= BIT(PIN_LED_1);
        burn(BLINK_DURATION_ITERS * 2 * duty_cycle / 100);

        GPIO(PORT_LED_1, OUT) &= ~BIT(PIN_LED_1);
        burn(BLINK_DURATION_ITERS * 2 * (100 - duty_cycle) / 100);
    }
}

static void blink_led2(unsigned blinks, unsigned duty_cycle) {
    unsigned i;

    for (i = 0; i < blinks; ++i) {
        GPIO(PORT_LED_2, OUT) |= BIT(PIN_LED_2);
        burn(BLINK_DURATION_ITERS * 2 * duty_cycle / 100);

        GPIO(PORT_LED_2, OUT) &= ~BIT(PIN_LED_2);
        burn(BLINK_DURATION_ITERS * 2 * (100 - duty_cycle) / 100);
    }
}

void task_init()
{
    LOG("init\r\n");

    // Solid flash signifying beginning of task
    GPIO(PORT_LED_1, OUT) |= BIT(PIN_LED_1);
    GPIO(PORT_LED_2, OUT) |= BIT(PIN_LED_2);
    burn(INIT_TASK_DURATION_ITERS);
    GPIO(PORT_LED_1, OUT) &= ~BIT(PIN_LED_1);
    GPIO(PORT_LED_2, OUT) &= ~BIT(PIN_LED_2);
    burn(INIT_TASK_DURATION_ITERS);

    GV(blinks) = NUM_BLINKS_PER_TASK;
    GV(tick) = 0;
    GV(duty_cycle) = 75;

    TRANSITION_TO(task_3);
}

void task_1()
{
    LOG("task 1\r\n");

    // Solid flash signifying beginning of task
    GPIO(PORT_LED_1, OUT) |= BIT(PIN_LED_1);
    burn(TASK_START_DURATION_ITERS);
    GPIO(PORT_LED_1, OUT) &= ~BIT(PIN_LED_1);
    burn(TASK_START_DURATION_ITERS);

    LOG("task 1: blinks %u dc %u\r\n", GV(blinks), GV(duty_cycle));

    blink_led1(GV(blinks), GV(duty_cycle));
    GV(blinks)++;

    TRANSITION_TO(task_2);
}

void task_2()
{
    LOG("task 2\r\n");

    // Solid flash signifying beginning of task
    GPIO(PORT_LED_2, OUT) |= BIT(PIN_LED_2);
    burn(TASK_START_DURATION_ITERS);
    GPIO(PORT_LED_2, OUT) &= ~BIT(PIN_LED_2);
    burn(TASK_START_DURATION_ITERS);

    LOG("task 2: blinks %u dc %u\r\n", GV(blinks), GV(duty_cycle));

    blink_led2(GV(blinks), GV(duty_cycle));
    GV(blinks)++;

    TRANSITION_TO(task_3);
}

void task_3()
{
    LOG("task 3: wait tick %u\r\n", GV(wait_tick));

    GPIO(PORT_LED_1, OUT) |= BIT(PIN_LED_1);
    GPIO(PORT_LED_2, OUT) |= BIT(PIN_LED_2);
    burn(WAIT_TICK_DURATION_ITERS);
    GPIO(PORT_LED_1, OUT) &= ~BIT(PIN_LED_1);
    GPIO(PORT_LED_2, OUT) &= ~BIT(PIN_LED_2);
    burn(WAIT_TICK_DURATION_ITERS);

    if (++GV(wait_tick) < WAIT_TICKS) {
        TRANSITION_TO(task_3);
    } else {
        GV(wait_tick) = 0;
        TRANSITION_TO(task_1);
    }
}

ENTRY_TASK(task_init)
INIT_FUNC(init)
