#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart_io.h"
#define F_CPU 18432000UL
#include <util/delay.h>
 
/*ADC Conversion Complete Interrupt Service Routine (ISR)*/
ISR(ADC_vect)
{ 
 	USART_Print_Value(ADC);    
 	USART_Print_String("\n\r");
	ADCSRA |= (1<<ADSC);		// Start Conversion
}
 
int main(void)

{
	USART_Init(MYUBRR);

	ADCSRA |= (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	/********

	ADCSRA Register – ADC Control and Status Register A
    +----+----+-----+----+----+-----+-----+-----+
	|ADEN|ADSC|ADATE|ADIF|ADIE|ADPS2|ADPS1|ADPS0| 
	+----+----+-----+----+----+-----+-----+-----+
	 7    6    5     4    3    2     1     0     bit
	 R/W  R/W   R/W  R/W  R/W   R/W   R/W        read/write
	 0    0    0     0    0    0     0     0     initial value

	Bit 7 – ADEN: ADC Enable
        Writing this bit to one enables the ADC.
    Bit 6 – ADSC: ADC Start Conversion
        Write this bit to one to start each conversion. 
    Bit 5 – ADATE: ADC Auto Trigger Enable
        When this bit is written to one, Auto Triggering of the ADC is enabled. 
        The ADC will start a conversion on a positive edge of the selected trigger signal. 
        The trigger source is selected by setting the ADC Trigger Select bits, ADTS in ADCSRB.
    Bit 4 – ADIF: ADC Interrupt Flag
        This bit is set when an ADC conversion completes and the Data Registers are updated. 
        The ADC Conversion Complete Interrupt is executed if the ADIE bit and the I-bit in SREG are set.
        ADIF is cleared by hardware when executing the corresponding interrupt handling vector. 
        Alternatively, ADIF is cleared by writing a logical one to the flag. 
        Beware that if doing a Read-ModifyWrite on ADCSRA, a pending interrupt can be disabled. 
        This also applies if the SBI and CBI instructions are used.
	Bit 3 – ADIE: ADC Interrupt Enable
        When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
	Bit 2 – ADPS2 ADC Prescaler Select 2
	Bit 1 – ADPS2 ADC Prescaler Select 1
	Bit 0 – ADPS2 ADC Prescaler Select 0
        These bits determine the division factor between the system clock frequency and the input clock to the ADC.
	
	********/

	ADMUX = (1<<REFS0); // set voltage ref to AVCC
    
	/********

	ADMUX – ADC Multiplexer Selection Register
    +-----+-----+-----+---+----+----+----+----+
	|REFS1|REFS0|ADLAR| - |MUX3|MUX2|MUX1|MUX0| 
	+-----+-----+-----+---+----+----+----+----+
	 7     6     5     4   3    2    1    0     bit
	 R/W   R/W   R/W   R   R/W  R/W  R/W  R/W   read/write
	 0     0     0     0   0    0    0    0     initial value

    Bit 7 - REFS1 Reference Selection Bit
    Bit 6 - REFS1 Reference Selection Bit
        These bits select the voltage reference for the ADC.
        See table below. 

    Voltage Reference Selections Table
    +------+------+--------------------------------------------------------------------+
    |REFS1 |REFS0 |Voltage Reference Selection                                         |
    +------+------+--------------------------------------------------------------------+
    |0     |0     |AREF, Internal Vref turned off                                      |
    +------+------+--------------------------------------------------------------------+
    |0     |1     |AVCC with external capacitor at AREF pin                            |
    +------+------+--------------------------------------------------------------------+
    |1     |0     |Reserved                                                            |
    +------+------+--------------------------------------------------------------------+
    |1     |1     |Internal 1.1V Voltage Reference with external capacitor at AREF pin |
    +------+------+--------------------------------------------------------------------+
	
	Bit 5 - ADLAR: ADC Left Adjust Result
	Bit 4 - Reserved Bit
	    This bit is an unused bit in the ATmega48P/88P/168P/328P, and will always read as zero.
    Bit 3 - MUX3 Analog Channel Selection Bit
    Bit 2 - MUX2 Analog Channel Selection Bit
    Bit 1 - MUX1 Analog Channel Selection Bit
    Bit 0 - MUX0 Analog Channel Selection Bit
        The value of these bits selects which analog inputs are connected to the ADC. 
        See Table below.

    Input Channel Selection Table
    +--------+--------------------+
    |MUX3..0 | Single Ended Input |
    +--------+--------------------+
    |0000    | ADC0               |
    +--------+--------------------+
    |0001    |ADC1                |
    +--------+--------------------+
    |0010    |ADC2                |
    +--------+--------------------+
    |0011    |ADC3                |
    +--------+--------------------+
    |0100    |ADC4                |
    +--------+--------------------+
    |0101    |ADC5                |
    +--------+--------------------+
    |0110    |ADC6                |
    +--------+--------------------+
    |0111    |ADC7                |
    +--------+--------------------+
    |1000    |ADC8(1)             |
    +--------+--------------------+
    |1001    |(reserved)          |
    +--------+--------------------+
    |1010    |(reserved)          |
    +--------+--------------------+
    |1011    |(reserved)          |
    +--------+--------------------+
    |1100    |(reserved)          |
    +--------+--------------------+
    |1101    |(reserved)          |
    +--------+--------------------+
    |1110    |1.1V (VBG)          |
    +--------+--------------------+
    |1111    |0V (GND)            |
    +--------+--------------------+

	********/
	sei();				// Enable Global Interrupts
	ADCSRA |= 1<<ADSC;	// Start Conversion
 
	while(1)
	{
		
	    _delay_ms(1000); 
	}			
} 