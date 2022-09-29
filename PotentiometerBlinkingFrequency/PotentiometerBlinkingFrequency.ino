/*
Author - Julio de Souza
Description - Changing the Blinking Frequency of the LED using a potentiometer*/

#include <util/delay.h> 
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {                             //interrupção do TIMER1 
  TCNT1 = 0xACFF; // Load the timer (overflow in FFFF)
  PORTB ^= (1<<PORTB0); //toogle the PortB0
}

int main(void){
  DDRB |= 0b00000001; // Set output in port 1 in PB
  /*Timer configuration TCCR1A and TCCR1B are two registers used to configure the timer 1 operation. It is set to overflow interruption*/
  TCCR1A &= 0b11111100; //WFM 11 and 10 set to zero
  TCCR1B |= 0b00000101; //CS10 and CS12 set to 1 and CS11 to zero (clock frequency of the timer counter)
  TCCR1B &= 0b11100111; //WFM 13 and 12 set to zero

  TCNT1 = 0xACFF; // Load the timer (overflow in FFFF)


  TIMSK1 |= (1 << TOIE1);  //Enable interruptions
  sei();
  SREG |= 0b10000000;
  
  
  
  while(1){
    
  }

}