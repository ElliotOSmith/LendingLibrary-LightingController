#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

int main(void)
{
    
    DDRB &= ~(1 << PB5); //PB5 Input

    DDRB |= (1 << PB0);   //set PB0 as output
    DDRB |= (1 << PB1);   //set PB1 as output
    DDRB |= (1 << PB2);   //set PB2 as output
    DDRB |= (1 << PB3);   //set PB3 as output
    DDRB |= (1 << PB4);   //set PB4 as output

    bool doorClosed;
    bool countedDown = false;
    int timer = 0;

    while (1)
    {
        bool doorClosed = PINB & (1 << PB5);

        if(doorClosed){
            PORTB &= ~(1 << PB0); //turn off
            PORTB &= ~(1 << PB1);
            PORTB &= ~(1 << PB2);
            PORTB &= ~(1 << PB3);
            PORTB &= ~(1 << PB4);

            countedDown = false;
            timer = 0;
        }else{
            if(!countedDown){
                PORTB |= (1 << PB0); //turn on led
                PORTB |= (1 << PB1);
                PORTB |= (1 << PB2);
                PORTB |= (1 << PB3);
                PORTB |= (1 << PB4);
                
                while(!doorClosed){
                    _delay_ms(1000);
                    timer ++;
                    if(timer >= 120){
                        timer = 0;
                        countedDown = true;
                        PORTB &= ~(1 << PB0);// turn off
                        PORTB &= ~(1 << PB1);
                        PORTB &= ~(1 << PB2);
                        PORTB &= ~(1 << PB3);
                        PORTB &= ~(1 << PB4);
                        break;
                    }
                }
            }
        }
    }

}