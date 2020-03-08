/*This C file contains functions of all features that have been implemented*/
#include "ml4_header.h"
void isr_action()  // servicing ISR
{
    if(FLAG_BIT.FLAG_ISR0==1)
    {
        OCR0A=value;
        if(!(PIND & (1<<PD2)))
        {
            OCR0A = OCR0A +13;
            value = OCR0A;
            _delay_ms(500);
        }
        FLAG_BIT.FLAG_ISR0 = 0;
    }

    if (FLAG_BIT.FLAG_ISR1==1)
    {
        OCR0A = value;
        if(!(PIND & (1<<PD3)))
        {
            OCR0A = OCR0A - 13;
            value = OCR0A;
            _delay_ms(500);
        }
        FLAG_BIT.FLAG_ISR1=0;
    }
}

void seat()  // seat implementation
{
    if(ADC_value_seat <= 200)
    {

        SET_BIT(PORTB,PB5);
        SET_BIT(PORTB,PB4);
        CLR_BIT(PORTB,PB3);
        CLR_BIT(PORTB,PB2);
        _delay_ms(20);

        CLR_BIT(PORTB,PB5);
        SET_BIT(PORTB,PB4);
        SET_BIT(PORTB,PB3);
        CLR_BIT(PORTB,PB2);
        _delay_ms(20);

        CLR_BIT(PORTB,PB5);
        CLR_BIT(PORTB,PB4);
        SET_BIT(PORTB,PB3);
        SET_BIT(PORTB,PB2);
        _delay_ms(20);

        SET_BIT(PORTB,PB5);
        CLR_BIT(PORTB,PB4);
        CLR_BIT(PORTB,PB3);
        SET_BIT(PORTB,PB2);
        _delay_ms(20);
    }

    if(ADC_value_seat > 200 && ADC_value_seat < 400 )
    {
        SET_BIT(PORTB,PB5);
        CLR_BIT(PORTB,PB4);
        CLR_BIT(PORTB,PB3);
        SET_BIT(PORTB,PB2);
        _delay_ms(20);

        CLR_BIT(PORTB,PB5);
        CLR_BIT(PORTB,PB4);
        SET_BIT(PORTB,PB3);
        SET_BIT(PORTB,PB2);
        _delay_ms(20);


        CLR_BIT(PORTB,PB5);
        SET_BIT(PORTB,PB4);
        SET_BIT(PORTB,PB3);
        CLR_BIT(PORTB,PB2);
        _delay_ms(20);

        SET_BIT(PORTB,PB5);
        SET_BIT(PORTB,PB4);
        CLR_BIT(PORTB,PB3);
        CLR_BIT(PORTB,PB2);
        _delay_ms(20);
    }
}
void window()  // window implementation
{
    if (!(PINB&(1<<PB0)))  // obstacle
    {
        SET_BIT(PORTC,PC5);
        _delay_us(2500);
        CLR_BIT(PORTC,PC5);
        _delay_ms(2000);
    }
    if(!(PIND & (1<<PD1)))  // rain
    {
        SET_BIT(PORTC,PC5);
        _delay_us(1000);
        CLR_BIT(PORTC,PC5);
        _delay_ms(2000);
    }
    if(!(PINB & (1<<PB6)))  // power up
    {
        SET_BIT(PORTC,PC5);
        _delay_us(1000);
        CLR_BIT(PORTC,PC5);
        _delay_ms(2000);
    }
    if(!(PINB & (1<<PB7)))  // power down
    {
        SET_BIT(PORTC,PC5);
        _delay_us(2500);
        CLR_BIT(PORTC,PC5);
        _delay_ms(2000);
    }
}
void tpms()
{
    ADMUX&=0x00;   //ADC Configuration for ADC0
    SET_BIT(ADMUX,REFS0);
    SET_BIT(ADCSRA,ADEN);
    SET_BIT(ADMUX,MUX1);
    SET_BIT(ADCSRA,ADSC);
    while(ADCSRA & (1 << ADSC));  // Sampling ADC0
    CLR_BIT(ADCSRA,ADSC);
    adc2 = ADC;
    if((adc2 < 447) || (adc2 > 461))  // 447 - 26psi, 461 - 35psi
        SET_BIT(PORTD,PD4);
    if((adc2 >= 447) && (adc2 <= 461))
        CLR_BIT(PORTD,PD4);
    SET_BIT(ADMUX,MUX0);
    SET_BIT(ADCSRA,ADSC);
    while(ADCSRA & (1 << ADSC));   // Sampling ADC4
    adc3 = ADC;
    if((adc3 < 573) || (adc3 > 628))  // For Tires (573 - 70 F, 628 - 100F)
        SET_BIT(PORTD,PD5);
    if((adc3 >= 573) && (adc3 <= 628))
        CLR_BIT(PORTD,PD5);
}
void hvac()
{
    if(ADC_value_seat > 400 && ADC_value_seat < 600 )
    {
        SET_BIT(PORTC,PC6);
        CLR_BIT(PORTD,PD0);
        CLR_BIT(PORTB,PB1);
    }
    else if(ADC_value_seat > 600 && ADC_value_seat < 800 )
    {

        SET_BIT(PORTD,PD0);
        CLR_BIT(PORTB,PB1);
        CLR_BIT(PORTC,PC6);
    }
    else if(ADC_value_seat > 800 && ADC_value_seat < 1000 )
    {

        SET_BIT(PORTB,PB1);
        CLR_BIT(PORTD,PD0);
        CLR_BIT(PORTC,PC6);
    }
    else
    {
        CLR_BIT(PORTC,PC6);
        CLR_BIT(PORTD,PD0);
        CLR_BIT(PORTB,PB1);
    }
}
