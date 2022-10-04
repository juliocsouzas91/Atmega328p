/*
Author - Julio de Souza
Description - Changing the Blinking Frequency of the LED using a potentiometer*/

#include <util/delay.h> 
#include <avr/interrupt.h>

uint16_t  counter_timer = 0xACFF;

ISR(TIMER1_OVF_vect) {                             //interrupção do TIMER1 
  TCNT1 = counter_timer; // Load the timer (overflow in FFFF)
  PORTB ^= (1<<PORTB0); //toogle the PortB0
  ADCSRA |= 0b01000000;
}

ISR(ADC_vect){

  counter_timer = ADCH; //one with 0xffff other with 0xff
  counter_timer = counter_timer<<8;
  PORTB ^= (1<<PORTB1);


}

int main(void){
  Serial.begin(9600); // open the serial port at 9600 bps:

  DDRB |= 0b00000011; // Set output in port 1 in PB
  /*Timer configuration TCCR1A and TCCR1B are two registers used to configure the timer 1 operation. It is set to overflow interruption*/
  TCCR1A &= 0b11111100; //WFM 11 and 10 set to zero
  TCCR1B |= 0b00000101; //CS10 and CS12 set to 1 and CS11 to zero (clock frequency of the timer counter)
  TCCR1B &= 0b11100111; //WFM 13 and 12 set to zero
  TCNT1 = counter_timer; // Load the timer (overflow in FFFF)

  /*Configure the A/D converter in A0*/
  ADMUX &= 0b00111111; //Uses the AREF as input voltage for the ADC converter
  ADCSRB |= 0b00000000; //Register control B auto trigger selection 
  ADMUX |= 0b00100000; //Uses the ADLAR (ADC Left Adjust Result), only ADCH is read
  ADCSRA |= 0b11101100;//Register to controll the interruption and clock division of the ADC


  
  /*Enable the interruptions*/

  TIMSK1 |= (1 << TOIE1);  
  sei();
  SREG |= 0b10000000; /*Which interruption will be used, timer1 and counter*/

  
  while(1){
  
  }

}