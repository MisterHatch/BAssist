//#include <msp430.h>
//
//void main (void)
//{
//    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
//
//    P1DIR |= BIT0;                            // Set P1.0 to output direction
//    P1OUT &= ~BIT0;
//
//    P1REN |= BIT1;                            // Enable P1.1 internal resistance
//    P1OUT |= BIT1;                            // Set P1.1 as pull-Up resistance
//    P1IES &= ~BIT1;                           // P1.1 Lo/Hi edge
//    P1IFG &= ~BIT1;                           // P1.1 IFG cleared
//    P1IE |= BIT1;                             // P1.1 interrupt enabled
//
//    __bis_SR_register( GIE );                 // Enable interrupts globally
//
//    while(1) {
//        __no_operation();                     // Placeholder for while loop (not required)
//    }
//}

// Port 1 interrupt service routine
//#pragma vector=PORT1_VECTOR
//__interrupt void Port_1(void)
//{
//    switch( __even_in_range( P1IV, P1IV_P1IFG7 )) {
//    case P1IV_P1IFG1:                                       // Pin 1 (button 2)
//        P1OUT^=BIT0;
//        break;
//    default:   _never_executed();
//
//    }
//
//}

#include <msp430.h>

int static const FIRST = 0x04, SECOND = 0x08, THIRD = 0x10, FOURTH = 0x20, FIFTH = 0x40;
int one = THIRD, two = SECOND, three = FIFTH, four = FIRST, five = FOURTH, six = SECOND, seven = FIFTH, eight = FIRST;

int state = 1; // initial state cycle through toggle all outputs currently

/**
 * blink.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    //P1DIR |= 0x05;                  // configure P1.0 as output, P1.2 = 0x04, P1.3 = 0x08, P1.4 = 0x10, P1.5 0x20, P1.6 = 0x40;

    P1DIR |= 0x7F;
    // P1.1 is 0x02
    P1DIR &= ~0x02; //Pin 1.1 Set as Input
//    P1REN |= 0x02; // Pull up resitor

    P1REN |= BIT1;                            // Enable P1.1 internal resistance
    P1OUT |= BIT1;                            // Set P1.1 as pull-Up resistance
    P1IES &= ~BIT1;                           // P1.1 Lo/Hi edge
    P1IFG &= ~BIT1;                           // P1.1 IFG cleared
    P1IE |= BIT1;                             // P1.1 interrupt enabled

    //enable interrupts here
    //__enable_interrupt();
    __bis_SR_register(GIE);

    volatile unsigned int i;        // volatile to prevent optimization

    while(1)
    {
        //P1OUT ^= 0x01;              // toggle P1.0
//        P1OUT ^= 0x01;
        P1OUT ^= one;
        for(i=50000; i>0; i--);     // delay

        P1OUT ^= two;
        for(i=50000; i>0; i--);

        P1OUT ^= three;
        for(i=50000; i>0; i--);

        P1OUT ^= four;
        for(i=50000; i>0; i--);

        P1OUT ^= five;
        for(i=50000; i>0; i--);

        P1OUT ^= six;
        for(i=50000; i>0; i--);

        P1OUT ^= seven;
        for(i=50000; i>0; i--);

        P1OUT ^= eight;
        for(i=50000; i>0; i--);
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    //Debounce here
    // and disable interrupts?
//    __disable_interrupt();
    P1IFG &= ~BIT1;                           // P1.1 IFG cleared
    P1IE &= ~BIT1;                            // P1.1 interrupt disabled
    P1OUT ^= 0x01;
    P1OUT &= 0x01;


    if(state == 1){
        state = 2;
        one = THIRD;
        two = SECOND;
        three = FIRST;
        four = FIFTH;
        five = FIRST;
        six = SECOND;
        seven = THIRD;
        eight = FIRST;
    }else if(state == 2){
        state = 3;
        one = SECOND;
        two = FIRST;
        three = FIFTH;
        four = SECOND;
        five = FIRST;
        six = FIFTH;
        seven = SECOND;
        eight = FIRST;
    }else if(state == 3){
        state = 4;
        one = THIRD;
        two = FIRST;
        three = FIFTH;
        four = THIRD;
        five = FIRST;
        six = THIRD;
        seven = FIFTH;
        eight = FIRST;
    }else if(state == 4){
        state = 5;
        one = SECOND;
        two = FIRST;
        three = SECOND;
        four = FIRST;
        five = FIFTH;
        six = SECOND;
        seven = FIRST;
        eight = FIFTH;
    }else if(state == 5){
        state = 6;
        one = FIRST;
        two = SECOND;
        three = FIFTH;
        four = FIRST;
        five = SECOND;
        six = FIFTH;
        seven = SECOND;
        eight = FIRST;
    }else if(state == 6){
        state = 7;
        one = FIRST;
        two = SECOND;
        three = FIRST;
        four = FIFTH;
        five = FIRST;
        six = SECOND;
        seven = FIRST;
        eight = FIFTH;
    }else if(state == 7){
        state = 8;
        one = SECOND;
        two = THIRD;
        three = SECOND;
        four = FIRST;
        five = SECOND;
        six = THIRD;
        seven = SECOND;
        eight = FIRST;
    }else if(state == 8){
        state = 1;
        one = THIRD;
        two = SECOND;
        three = FIFTH;
        four = FIRST;
        five = FOURTH;
        six = SECOND;
        seven = FIFTH;
        eight = FIRST;
    }

    P1REN |= BIT1;                            // Enable P1.1 internal resistance
    P1OUT |= BIT1;                            // Set P1.1 as pull-Up resistance
    P1IES &= ~BIT1;                           // P1.1 Lo/Hi edge
    P1IFG &= ~BIT1;                           // P1.1 IFG cleared
    P1IE |= BIT1;                             // P1.1 interrupt enabled
}








