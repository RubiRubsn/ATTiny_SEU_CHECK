#define __AVR_ATtiny20__
#include "uart_BitBang8Mhz.h"
#include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdint.h>
#include <stdlib.h>
// #include "TMR_datatype.h"
#define RAM_START 0x0040
#define FLASH_START 0x00C0
// zellen 43

#define nr_zells 47
uint8_t test[nr_zells];

uint8_t adr;
uint8_t val;

uint8_t counter = 0;

void test_register()
{
	if (PORTCR != 0)
	{
		adr = 0xff;
		val = 0x08;
		uart_send_report(adr, val);
		PORTCR = 0x00;
	}
	else if (PCMSK0 != 0)
	{
		adr = 0xff;
		val = 0x09;
		uart_send_report(adr, val);
		PCMSK0 = 0x00;
	}
	else if (PCMSK1 != 0)
	{
		adr = 0xff;
		val = 0x0A;
		uart_send_report(adr, val);
		PCMSK1 = 0x00;
	}
	else if (DIDR0 != 0)
	{
		adr = 0xff;
		val = 0x0D;
		uart_send_report(adr, val);
		DIDR0 = 0x00;
	}
	else if (ADCL != 0)
	{
		adr = 0xff;
		val = 0x0E;
		uart_send_report(adr, val);
		ADCL = 0x00;
	}
	else if (ADCH != 0)
	{
		adr = 0xff;
		val = 0x0F;
		uart_send_report(adr, val);
		ADCH = 0x00;
	}
	else if (ADMUX != 0)
	{
		adr = 0xff;
		val = 0x10;
		uart_send_report(adr, val);
		ADMUX = 0x00;
	}
	else if (ADCSRB != 0)
	{
		adr = 0xff;
		val = 0x11;
		uart_send_report(adr, val);
		ADCSRB = 0x00;
	}
	else if (ADCSRA != 0)
	{
		adr = 0xff;
		val = 0x12;
		uart_send_report(adr, val);
		ADCSRA = 0x00;
	}
	else if (ACSRB != 0)
	{
		adr = 0xff;
		val = 0x13;
		uart_send_report(adr, val);
		ACSRB = 0x00;
	}
	else if (ACSRA != 0)
	{
		adr = 0xff;
		val = 0x14;
		uart_send_report(adr, val);
		ACSRA = 0x00;
	}
	else if (OCR0B != 0)
	{
		adr = 0xff;
		val = 0x15;
		uart_send_report(adr, val);
		OCR0B = 0x00;
	}
	// else if (TCCR0B != 0)
	// {
	// 	adr = 0xff;
	// 	val = 0x18;
	// 	uart_send_report(adr, val);
	// 	TCCR0B = 0x00;
	// }
	else if (TCCR0B != 0)
	{
		adr = 0xff;
		val = 0x18;
		uart_send_report(adr, val);
		TCCR0B = 0x00;
	}
	else if (TCNT1L != 0)
	{
		adr = 0xff;
		val = 0x20;
		uart_send_report(adr, val);
		TCNT1L = 0x00;
	}
	else if (TCNT1H != 0)
	{
		adr = 0xff;
		val = 0x21;
		uart_send_report(adr, val);
		TCNT1H = 0x00;
	}
	else if (TCCR1C != 0)
	{
		adr = 0xff;
		val = 0x22;
		uart_send_report(adr, val);
		TCCR1C = 0x00;
	}
	else if (TCCR1B != 0)
	{
		adr = 0xff;
		val = 0x23;
		uart_send_report(adr, val);
		TCCR1B = 0x00;
	}
	else if (TCCR1A != 0)
	{
		adr = 0xff;
		val = 0x24;
		uart_send_report(adr, val);
		TCCR1A = 0x00;
	}
	// else if (TIMSK != 0)
	// {
	// 	adr = 0xff;
	// 	val = 0x26;
	// 	uart_send_report(adr, val);
	// 	TIMSK = 0x00;
	// }
	else if (GTCCR != 0)
	{
		adr = 0xff;
		val = 0x27;
		uart_send_report(adr, val);
		GTCCR = 0x00;
	}
	else if (TWSD != 0)
	{
		adr = 0xff;
		val = 0x28;
		uart_send_report(adr, val);
		TWSD = 0x00;
	}
	else if (TWSAM != 0)
	{
		adr = 0xff;
		val = 0x29;
		uart_send_report(adr, val);
		TWSAM = 0x00;
	}
	else if (TWSA != 0)
	{
		adr = 0xff;
		val = 0x2A;
		uart_send_report(adr, val);
		TWSA = 0x00;
	}
	else if (TWSSRA != 0)
	{
		adr = 0xff;
		val = 0x2B;
		uart_send_report(adr, val);
		TWSSRA = 0x00;
	}
	else if (TWSCRB != 0)
	{
		adr = 0xff;
		val = 0x2C;
		uart_send_report(adr, val);
		TWSCRB = 0x00;
	}
	else if (TWSCRA != 0)
	{
		adr = 0xff;
		val = 0x2D;
		uart_send_report(adr, val);
		TWSCRA = 0x00;
	}
	else if (SPCR != 0)
	{
		adr = 0xff;
		val = 0x30;
		uart_send_report(adr, val);
		SPCR = 0x00;
	}
	else if (PRR != 0)
	{
		adr = 0xff;
		val = 0x35;
		uart_send_report(adr, val);
		PRR = 0x00;
	}
	// else if (OSCCAL != 0)
	// {
	// 	adr = 0xff;
	// 	val = 0x39;
	// 	uart_send_report(adr, val);
	// 	OSCCAL = 0x00;
	// }
	else if (MCUCR != 0)
	{
		adr = 0xff;
		val = 0x3A;
		uart_send_report(adr, val);
		MCUCR = 0x00;
	}
	// uart_send_report(adr, val);
}

struct tripple_uint8_t_ptr
{
	uint8_t *A;
	uint8_t *B;
	uint8_t *C;
};

struct tripple_uint8_t
{
	uint8_t A;
	uint8_t B;
	uint8_t C;
};
#define TEST_PATTERN 0xAA

void test_memory(unsigned short test_pattern);

uint8_t TMR(uint8_t &A, uint8_t &B, uint8_t &C)
{
	if ((A == B) && (B == C))
	{
		return A;
	}
	else
	{

		if (A == B)
		{
			adr = (uint8_t)(short)&C;
			val = C;
			C = A;
		}
		else if (A == C)
		{
			adr = (uint8_t)(short)&B;
			val = B;
			B = A;
		}
		else
		{
			adr = (uint8_t)(short)&A;
			val = A;
			A = B;
		}
		uart_send_report(adr, val);
	}
	return A;
};
uint8_t TMR(tripple_uint8_t &A)
{
	return TMR(A.A, A.B, A.C);
};

uint8_t *TMR(tripple_uint8_t_ptr &A)
{
	if ((A.A == A.B) && (A.B == A.C))
	{
		return A.A;
	}
	else
	{
		if (A.A == A.B)
		{
			adr = (uint8_t)(short)&(A.C);
			val = (uint8_t)(short)(A.C);
			A.C = A.A;
		}
		else if (A.A == A.C)
		{
			adr = (uint8_t)(short)&(A.B);
			val = (uint8_t)(short)(A.B);
			A.B = A.A;
		}
		else
		{
			adr = (uint8_t)(short)&(A.A);
			val = (uint8_t)(short)(A.A);
			A.A = A.B;
		}
		uart_send_report(adr, val);
	}
	return A.A;
};

int main(void)
{

	CCP = 0xD8;	  // disable Configuration Change Protection Register
	CLKPSR = 0x0; // Clock Division Factor = 1			//vielleicht doch durch 8
	UART_init();
	DDRA |= 1 << PA5; /* set PA5 to output (LED)*/

	for (tripple_uint8_t i = {0, 0, 0}; TMR(i) < nr_zells; i.A++, i.B++, i.C++)
	{
		test[TMR(i)] = TEST_PATTERN;
	}

	while (1)
	{
		test_memory(TEST_PATTERN);
		test_register();
		if (++counter == 0)
		{
			PORTA ^= 1 << PA5;
			UART_tx((char)('.'));
		}
	}

	return 0;
}

void test_memory(unsigned short test_pattern)
{
	for (tripple_uint8_t i = {0, 0, 0}; TMR(i) < nr_zells; i.A++, i.B++, i.C++)
	{
		if (test[TMR(i)] != test_pattern)
		{
			adr = (uint8_t)(short)&test[TMR(i)];
			val = test[TMR(i)];
			uart_send_report(adr, val);
			test[TMR(i)] = test_pattern;
		}
	}
}
