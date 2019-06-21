#define FOSC 18432000 // Clock Speed
#define BAUD 115200// baud rate
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <stdlib.h>

void USART_Init(unsigned int);
void USART_Transmit( char data );
void USART_Print_String(char string[]);
void USART_Print_Value(float value);
void Start_Screen(void);
void Receive_User_Input(void);
volatile unsigned char user_input;
volatile unsigned char option;

void USART_Init(unsigned int ubrr)
{
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void USART_Print_String(char string[])
{
	unsigned char i;
	for(i=0;string[i];i++)
	{	
		USART_Transmit(string[i]);
	}
}

void USART_Print_Value(float value)
{
	char string[10];
  itoa(value,string,10);
	USART_Print_String(string);
}

void Receive_User_Input(void)
{
	while ( !(UCSR0A & (1<<RXC0)) );
    {
		user_input = UDR0;
		USART_Transmit(user_input);	
	}
}

void Receive_User_Input_No_Echo(void)
{
	while ( !(UCSR0A & (1<<RXC0)) );
    {
		user_input = UDR0;
	}
	return user_input;
}



