/*
Author - Julio de Souza
Description - Vu Metter, using ADC and Port D and B*/

#include <util/delay.h> 
#include <avr/interrupt.h>

uint16_t  counter_timer = 0x0000;

ISR(ADC_vect){

  counter_timer = ADCH; //one with 0xffff other with 0xff
  counter_timer = counter_timer<<8;
}



int main(void){
  Serial.begin(9600); // open the serial port at 9600 bps:

  DDRB |= 0b00011111; // Set output in PB
  DDRD |= 0b11111100; // Set output in PD
    
  /*Configure the A/D converter in A0*/
  ADMUX &= 0b00111111; //Uses the AREF as input voltage for the ADC converter
  ADCSRB |= 0b00000000; //Register control B auto trigger selection 
  ADMUX |= 0b00100000; //Uses the ADLAR (ADC Left Adjust Result), only ADCH is read
  ADCSRA |= 0b11101100;//Register to controll the interruption and clock division of the ADC

  /*Enable the interruptions*/
  sei();
  SREG |= 0b10000000; /*Which interruption will be used, timer1 and counter*/
  PORTD |=
  PORTB |= 
  while(1){
  
  }

}