
#include <avr/io.h>
#define F_CPU 8000000U
#include <util/delay.h>
#include <stdint.h>
int a = 1000 ;
 int b = 1000; 
 int c;

const  void eteindre(){
    PORTA &= (1 << PA1) & (1<<PA0);
}

const void allumerVert(){
     PORTA |= (1 << PA1);
}

int main()
{
    DDRA |= 0xff;
    DDRD |= 0x00;
    
    for(int i = 0; i < b ; i++)
    {
        
        c = b-a;
        a--;
        for(int i = 0; i < a ; i++)
        {
            allumerVert();
            _delay_us(1);
        }
        for(int i = 0; i < c ; i++)
        {
            eteindre();
            _delay_us(1);
        }
        
        
        
    }


}