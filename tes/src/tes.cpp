//tes.cpp
//#include "Arduino.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void){
    // put your main code here:
    DDRB=0b11101100;  //DDRX=1OUTPUT 0 INPUT
    //PORTB=0B101111101;//MSB----LSB
    PORTB=0B00010011;
    while(1){
    	//if((PINB & (1 << PINB4)) == (1 << PINB4)){
    		PORTB=0B000100000;
    		_delay_ms(1000);
    		PORTB=0B000000000;
    		_delay_ms(1000);
   // }
    } 
}