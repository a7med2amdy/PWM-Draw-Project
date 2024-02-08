#include <avr/io.h>

#include "TIMER0_Int.h"



void timer0_init() {
    // Set Timer0 in Normal mode
    TCCR0 = 0;

    // Set Timer0 prescaler to 1 (no prescaling)
    TCCR0 |= (1 << CS00);

    // Enable Timer0 Overflow Interrupt
    TIMSK |= (1 << TOIE0);

    // Enable global interrupts
    //sei();
}
