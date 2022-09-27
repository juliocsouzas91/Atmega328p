/*
Author - Julio de Souza
Description - Changing the Blinking Frequency of the LED using a potentiometer*/

#include <util/delay.h> 
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {                             //interrupção do TIMER1 
  TCNT1 = 0xC2F7;                                 // Renicia TIMER
  PORTB ^= (1<<PORTB0);
}

int main(void){
  DDRB |= 0b00000001; // Set output in port 5

  TCCR1A &= 0b11111100; //WFM 11 and 10 set to zero
  TCCR1B |= 0b00000101;
  TCCR1B &= 0b11100111; //WFM 13 and 12 set to zero
  PORTB ^= (1<<PORTB0);
  
  TCCR1A = 0;
  TCCR1B = 0;                        //limpa registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
  TCNT1 = 0xC2F7;
  TIMSK1 |= (1 << TOIE1);  
  SREG |= 0b10000000;
  
  
  while(1){
    
  }

}