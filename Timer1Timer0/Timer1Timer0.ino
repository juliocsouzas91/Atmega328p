#include <avr/interrupt.h>

uint16_t  counter_timer = 0xACFF;


ISR(TIMER1_OVF_vect) {                             //interrupção do TIMER1 
  TCNT1 = 0xAFFF; // Load the timer (overflow in FFFF)
  PORTB ^= (1<<PORTB0); //toogle the PortB0
  PRR |= 0b00010000; //Shut Down Timer 1
  PRR &= 0b11011111; //Enable Timer 0  

}

ISR(TIMER0_OVF_vect) {                             //interrupção do TIMER1 
  TCNT1 = 0xAF; // Load the timer (overflow in FFFF)
  PORTB ^= (1<<PORTB1); //toogle the PortB0
  PRR |= 0b00100000; //Shut Down Timer 0
  PRR &= 0b11101111; //Enable Timer 1
}

int main(void){
  DDRB |= 0b00000011; // Set output in port 1 in PB
  /*Timer configuration TCCR1A and TCCR1B are two registers used to configure the timer 1 operation. It is set to overflow interruption*/
  TCCR1A &= 0b11111100; //WFM 11 and 10 set to zero
  TCCR1B |= 0b00000101; //CS10 and CS12 set to 1 and CS11 to zero (clock frequency of the timer counter)
  TCCR1B &= 0b11100111; //WFM 13 and 12 set to zero
  TCNT1 = counter_timer; // Load the timer (overflow in FFFF)
  TIMSK1 |= (1 << TOIE1);  
  sei();




  /*Enable Interruptions*/
  SREG |= 0b10000000; /*Which interruption will be used, timer1 and counter*/  
  while(1){
    
  }
}