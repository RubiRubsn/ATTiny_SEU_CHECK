/*  Software ("bit-bang") UART Transmitter (8 data bits, 1 stop bit, no parity)
    for Attiny24A/44A/84A using the internal 8MHz oscillator as clock source
    (c) 2018 Marcel Meyer-Garcia
    see LICENCE.txt
 */

/* NOTE: since the internal 8MHz oscillator is not very accurate, the value for OCR0A can be tuned
   to achieve the desired baud rate (nominal value is 103)
*/

#pragma once
void UART_tx(char);
void UART_tx_str(char *);
void UART_init();

#include <avr/io.h>
#include <avr/interrupt.h>
// #include "TMR_datatype.h"
// #include <util/delay.h>

#define TX_PORT PORTB
#define TX_PIN PB1
#define TX_DDR DDRB
#define TX_DDR_PIN DDB1

#ifndef F_CPU
#define F_CPU (8000000UL) // 8 MHz
#endif                    /* !F_CPU */

struct tripple_uint8_t
{
   uint8_t A;
   uint8_t B;
   uint8_t C;
};

struct tripple_uint16_t
{
   uint16_t A;
   uint16_t B;
   uint16_t C;
};

uint8_t TMRNU(uint8_t &A, uint8_t &B, uint8_t &C)
{
   if ((A == B) && (B == C))
   {
      return A;
   }
   else
   {
      if (A == B)
      {
         C = A;
      }
      else if (A == C)
      {
         B = A;
      }
      else
      {
         A = B;
      }
   }
   return A;
};
uint8_t TMRNU(tripple_uint8_t &A)
{
   return TMRNU(A.A, A.B, A.C);
};

uint16_t TMRNU(uint16_t &A, uint16_t &B, uint16_t &C)
{
	if ((A == B) && (B == C))
	{
		return A;
	}
	else
	{
		if (A == B)
		{
			C = A;
		}
		else if (A == C)
		{
			B = A;
		}
		else
		{
			A = B;
		}
	}
	return A;
};
uint8_t TMRNU(tripple_uint16_t &A)
{
	return TMRNU(A.A, A.B, A.C);
};



void UART_tx(tripple_uint8_t character)
{

   tripple_uint16_t send_buffer;
   send_buffer.A = (uint16_t)(character.A << 1) | (uint16_t)(1 << 9);
   send_buffer.B = (uint16_t)(character.B << 1) | (uint16_t)(1 << 9);
   send_buffer.C = (uint16_t)(character.C << 1) | (uint16_t)(1 << 9);
   TMRNU(send_buffer);


   // start timer0 with a prescaler of 8
   TCCR0B = (1 << CS01);
   while (TMRNU(send_buffer) != 0)
   {
      while ((TIFR &= (1 << OCF0A)) == 0)
      {
      }
      if (TMRNU(send_buffer) & 0x01)
      {
         TX_PORT |= (1 << TX_PIN);
      }
      else
      {
         TX_PORT &= ~(1 << TX_PIN);
      }
      send_buffer.A >>= 1;
      send_buffer.B >>= 1;
      send_buffer.C >>= 1;
      TMRNU(send_buffer);
   }
   TCCR0B = 0;
   TCNT0 = 0;
}

void UART_tx(char character)
{
   tripple_uint8_t help;
   help.A = character;
   help.B = character;
   help.C = character;
   UART_tx(help);
}

void UART_init()
{
   // set TX pin as output
   TX_DDR |= (1 << TX_DDR_PIN);
   TX_PORT |= (1 << TX_PIN);

   // set timer0 to CTC mode clear timer on compare match
   TCCR0A = (1 << WGM01);

   // set compare value to 103 to achieve a 9600 baud rate (i.e. 104µs)
   // together with the 8MHz/8=1MHz timer0 clock
   /*
   NOTE: since the internal 8MHz oscillator is not very accurate, this value can be tuned
   to achieve the desired baud rate, so if it doesn't work with the nominal value (103), try
   increasing or decreasing the value by 1 or 2
   */

   OCR0A = 103; // Default == 103


}

void uart_send_report(uint8_t address, uint8_t content, uint8_t corr_cont)
{
   tripple_uint8_t h_adress;
   tripple_uint8_t h_content;
   tripple_uint8_t h_corr_cont;
   h_adress.A = address;
   h_adress.B = address;
   h_adress.C = address;
   h_content.A = content;
   h_content.B = content;
   h_content.C = content;
   h_corr_cont.A = corr_cont;
   h_corr_cont.B = corr_cont;
   h_corr_cont.C = corr_cont;
   UART_tx(h_adress);
   UART_tx(h_content);
   UART_tx(h_corr_cont);
}
