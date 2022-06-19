#include <avr/io.h>

int main (void){

  DDRB |= (1 << DDB2); //PB2 output
  OCR0A = 128; // 50% duty cycle (128/256) at 8 bit
  CLKPR = (1 << CLKPCE); //clock divider enable bit
  CLKPR = (1 << CLKPS2); //clock divide by 2
  
  TCCR0A |= (1 << COM0A1); //set Phase correct PWM mode
  TCCR0A |= (1 << WGM00) ; //set Phase correct PWM to upcount (0 to 255)
  TCCR0B |= (1 << CS01); //Pre-scaler set to 1 (used for frequency)
  
while (1) {
    }//end while
    
}//end main