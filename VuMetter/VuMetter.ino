/*
Author - Julio de Souza
Description - Vu Metter, using ADC and Port D and B*/

#include <util/delay.h> 
#include <avr/interrupt.h>

uint8_t  counter_timer = 0x00;

ISR(ADC_vect){

  counter_timer = ADCH; //one with 0xffff other with 0xff
  //counter_timer = counter_timer<<8;
  ADCSRA |= 0b01000000;
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

  while(1){
    Serial.print(counter_timer);
    Serial.print("\n");

    if(counter_timer<21){
    PORTD |= 0b00000100;
  }
    else if(counter_timer<2*21){
    PORTD |= 0b00001100;
  }
    else if(counter_timer<3*21){
    PORTD |= 0b00011100;
  }
    else if(counter_timer<4*21){
    PORTD |= 0b00111100;
  }
    else if(counter_timer<5*21){
    PORTD |= 0b01111100;
  }
    else if(counter_timer<6*21){
    PORTD |= 0b11111100;
  }
    else if(counter_timer<7*21){
    PORTD |= 0b11111100;
    PORTB |= 0b00000001;
  }
    else if(counter_timer<8*21){
    PORTD |= 0b11111100;
    PORTB |= 0b00000011;
  }
    else if(counter_timer<9*21){
    PORTD |= 0b11111100;
    PORTB |= 0b00000111;
  }
    else if(counter_timer<10*21){
    PORTD |= 0b11111100;
    PORTB |= 0b00001111;
  }
    else if(counter_timer<11*21){
    PORTD |= 0b11111100;
    PORTB |= 0b00011111;
  }
    else if(counter_timer<=255){
    PORTD |= 0b11111100;
    PORTB |= 0b00011111;
  }
    PORTD &= 0b00000011;
    PORTB &= 0b11100000;
  }

}