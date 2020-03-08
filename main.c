/*This C file is the main file of the ML4 integrated embedded C implementation

Version: 1.0
Authors:
        Nitesh Dhiman (Seat Adjustment)
        Aamir Suhail Burhan - (TPMS)
        Darshan N - (HVAC)
        Darrel Reesha Pinto - (Power Window)
*/
#include "ml4_header.h"
int main()
{
    value = 128;
    port_config();
    while(1)
    {
        isr_action(); // check for isr
        OCR0A = value;  // initiate hvac
        ADMUX&=0x00;
        SET_BIT(ADMUX,REFS0);
        SET_BIT(ADCSRA,ADEN);
        ADCSRA|=(1<<ADSC);
        while(ADCSRA&(1<<ADSC));
        ADC_value_seat = ADC;
        while(ADC_value_seat >= 0 && ADC_value_seat <400)
        {

            isr_action();
            ADMUX&=0x00;
            SET_BIT(ADMUX,REFS0);
            SET_BIT(ADCSRA,ADEN);
            SET_BIT(ADCSRA,ADSC);
            while(ADCSRA&(1<<ADSC));
            ADC_value_seat = ADC;
            seat();  // execute seat feature
            window();  // execute power window feature
            tpms();  // execute tpms feature
        }
        hvac();  // execute hvac feature
        window();
        tpms();
    }
    return 0;
}



