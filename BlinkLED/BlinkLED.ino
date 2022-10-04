/*
Author = Julio de Souza 
Program Description - Simple blinking LED in port 5 but the delay time can be changed by external interruption Int 0 and Int 1 (port 2 and 3)
*/


#include <avr/interrupt.h>
#include <util/delay.h> 

volatile int cnt_zero = 1 ;

ISR (INT0_vect){          //External interrupt_zero ISR 0
  cnt_zero = 2;
}
ISR (INT1_vect){          //External interrupt_zero ISR 1
  cnt_zero = 1;
}

int main(void){
  DDRD |= 0b00100000; // The Port D Data Direction Register (Port 5 as output)

  EIMSK |= 0b00000011; //External Interrupt Mask Regist Enabling external interruption
  
  EICRA = EICRA|0b00001111; //External Interrupt Control Register A
  
  sei(); 

  while(1){
    if(cnt_zero == 1){
      _delay_ms(150); 
      PORTD |= 0b00100000;  
      _delay_ms(150);
      PORTD &= 0b11011111;
    }
    else{
      _delay_ms(600); 
      PORTD |= 0b00100000;  
      _delay_ms(600);
      PORTD &= 0b11011111;
    }

  }
  
return 1;
}
