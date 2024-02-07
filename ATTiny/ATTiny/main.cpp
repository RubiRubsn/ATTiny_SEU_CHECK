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

void test_register()
{
	if (PORTCR != 0)
	{
		adr = *PORTCR;
	}

	uart_send_report(adr, val);
}