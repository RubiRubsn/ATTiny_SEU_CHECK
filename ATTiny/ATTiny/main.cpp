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

#define nr_zells 50 // 90 // 47
uint8_t test[nr_zells];

uint8_t adr;
uint8_t val;
uint8_t counter_two = 0;

uint8_t counter = 0;

void test_register()
{
	if ((PORTCR & 0x03) != 0)
	{
		adr = 0x08 | (1 << 7);
		val = PORTCR & 0x3;
		PORTCR = PORTCR & ~(0x3);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (PCMSK0 != 0)
	{
		adr = 0x09 | (1 << 7);
		val = PCMSK0;
		PCMSK0 = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((PCMSK1 & (0x0F)) != 0)
	{
		adr = 0x0A | (1 << 7);
		val = PCMSK1 & (0x0F);
		PCMSK1 = PCMSK1 & ~(0x0F);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (DIDR0 != 0)
	{
		adr = 0x0D | (1 << 7);
		val = DIDR0;
		DIDR0 = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	// else if (ADCL != 0)
	// {
	// 	adr = 0x0E | (1 << 7);
	// 	val = ADCL;
	// 	ADCL = 0x00;
	// 	UART_tx('$');
	// 	uart_send_report(adr, val);
	// }
	// else if (ADCH != 0)
	// {
	// 	adr = 0x0F | (1 << 7);
	// 	val = ADCH;
	// 	ADCH = 0x00;
	// 	UART_tx('$');
	// 	uart_send_report(adr, val);
	// }
	else if ((ADMUX & (0x7F)) != 0)
	{
		adr = 0x10 | (1 << 7);
		val = ADMUX & 0x7F;
		ADMUX = ADMUX & ~(0x7F);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((ADCSRB & (0xCF)) != 0)
	{
		adr = 0x11 | (1 << 7);
		val = ADCSRB & (0xCF);
		ADCSRB = ADCSRB & ~(0xCF);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (ADCSRA != 0)
	{
		adr = 0x12 | (1 << 7);
		val = ADCSRA;
		ADCSRA = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((ACSRB & 0xEF) != 0)
	{
		adr = 0x13 | (1 << 7);
		val = ACSRB & 0xEF;
		ACSRB = ACSRB & ~0xEF;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((ACSRA & 0xCF) != 0)
	{
		adr = 0x14 | (1 << 7);
		val = ACSRA & 0xCF;
		ACSRA = ACSRA & ~0xCF;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (OCR0B != 0)
	{
		adr = 0x15 | (1 << 7);
		val = OCR0B;
		OCR0B = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	// else if (TCCR0B != 0)
	// {
	// 	adr = 0x18 | (1 << 7);
	// 	val = TCCR0B;
	// 	UART_tx('$');
	// 	uart_send_report(adr, val);
	// 	TCCR0B = 0x00;
	// }
	else if (TCNT1L != 0)
	{
		adr = 0x20 | (1 << 7);
		val = TCNT1L;
		TCNT1L = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (TCNT1H != 0)
	{
		adr = 0x21 | (1 << 7);
		val = TCNT1H;
		TCNT1H = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	// else if ((TCCR1C & 0xC0) != 0)
	// {
	// 	adr = 0x22 | (1 << 7);
	// 	val = TCCR1C & 0xC0;
	// 	TCCR1C = TCCR1C & ~(0xC0);
	// 	UART_tx('$');
	// 	uart_send_report(adr, val);
	// }
	else if ((TCCR1B & 0xDF) != 0)
	{
		adr = 0x23 | (1 << 7);
		val = TCCR1B & 0xDF;
		TCCR1B = TCCR1B & ~(0xDF);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((TCCR1A & 0xF3) != 0)
	{
		adr = 0x24 | (1 << 7);
		val = TCCR1A & 0xF3;
		TCCR1A = TCCR1A & ~(0xf3);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	// else if (TIMSK != 0)
	// {
	// 	adr = 0xff;
	// 	val = 0x26;
	// 	uart_send_report(adr, val);
	// 	TIMSK = 0x00;
	// }
	else if ((GTCCR & 0x81) != 0)
	{
		adr = 0x27 | (1 << 7);
		val = GTCCR & 0x81;
		GTCCR = GTCCR & ~0x81;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (TWSD != 0)
	{
		adr = 0x28 | (1 << 7);
		val = TWSD;
		TWSD = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (TWSAM != 0)
	{
		adr = 0x29 | (1 << 7);
		val = TWSAM;
		TWSAM = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (TWSA != 0)
	{
		adr = 0x2A | (1 << 7);
		val = TWSA;
		TWSA = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((TWSSRA & 0xCF) != 0)
	{
		adr = 0x2B | (1 << 7);
		val = TWSSRA & 0xCF;
		TWSSRA = TWSSRA & ~0xCF;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((TWSCRB & 0x04) != 0)
	{
		adr = 0x2C | (1 << 7);
		val = TWSCRB & 0x04;
		TWSCRB = TWSCRB & ~(0x04);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((TWSCRA & 0xBF) != 0)
	{
		adr = 0x2D | (1 << 7);
		val = TWSCRA & 0xBF;
		TWSCRA = TWSCRA & ~(0xBF);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if (SPCR != 0)
	{
		adr = 0x30 | (1 << 7);
		val = SPCR;
		SPCR = 0x00;
		UART_tx('$');
		uart_send_report(adr, val);
	}
	else if ((PRR & 0x1F) != 0)
	{
		adr = 0x35 | (1 << 7);
		val = PRR & 0x1F;
		PRR = PRR & ~(0x1F);
		UART_tx('$');
		uart_send_report(adr, val);
	}
	// else if (OSCCAL != 0)
	// {
	// 	adr = 0xff;
	// 	val = 0x39;
	// 	uart_send_report(adr, val);
	// 	OSCCAL = 0x00;
	// }
	else if ((MCUCR & 0xDF) != 0)
	{
		adr = 0x3A | (1 << 7);
		val = MCUCR & 0xDF;
		MCUCR = MCUCR & ~(0xDF);
		UART_tx('$');
		uart_send_report(adr, val);
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

tripple_uint8_t i;

#define TEST_PATTERN 0xAA

void test_memory();

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
	i.A = 0;
	i.B = 0;
	i.C = 0;
	for (i.A = 0; TMR(i) < nr_zells; i.A++, i.B++, i.C++)
	{
		test[TMR(i)] = TEST_PATTERN;
	}

	while (1)
	{
		test_memory();
		test_register();
		if (++counter == 0)
		{
			PORTA ^= 1 << PA5;
			if (++counter_two == 10)
			{

				UART_tx((char)('.'));
				counter_two = 0;
			}
		}
	}

	return 0;
}

void test_memory()
{
	i.A = 0;
	i.B = 0;
	i.C = 0;
	for (i.A = 0; TMR(i) < nr_zells; i.A++, i.B++, i.C++)
	{
		if (test[TMR(i)] != TEST_PATTERN)
		{
			adr = (uint8_t)(short)&test[TMR(i)];
			val = test[TMR(i)];
			test[TMR(i)] = TEST_PATTERN;
			UART_tx('$');
			uart_send_report(adr, val);
		}
	}
}
