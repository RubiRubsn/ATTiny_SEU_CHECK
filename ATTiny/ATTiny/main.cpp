#define __AVR_ATtiny20__
#include "uart_BitBang8Mhz.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
// #include "TMR_datatype.h"
#define RAM_START 0x0040
#define FLASH_START 0x00C0

uint8_t adr;
uint8_t val;

uint8_t counter = 0;
uint8_t counter_zwo = 0;

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
uint8_t *allocate_ram(unsigned short *);

tripple_uint8_t_ptr ram_pointer;
unsigned short ram_size;
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
			// uart_send_report((uint8_t)(short)&C, C);
			adr = (uint8_t)(short)&C;
			val = C;
			C = A;
		}
		else if (A == C)
		{
			// uart_send_report((uint8_t)(short)&B, B);
			adr = (uint8_t)(short)&B;
			val = B;
			B = A;
		}
		else
		{
			// uart_send_report((uint8_t)(short)&A, A);
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
			// uart_send_report((short)&A.C, A.C);
			A.C = A.A;
		}
		else if (A.A == A.C)
		{
			adr = (uint8_t)(short)&(A.B);
			val = (uint8_t)(short)(A.B);
			// uart_send_report((short)&A.B, A.B);
			A.B = A.A;
		}
		else
		{
			// uart_send_report((short)&A.A, A.A);
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

	ram_pointer.A = allocate_ram(&ram_size);
	ram_pointer.B = ram_pointer.A;
	ram_pointer.C = ram_pointer.A;
	UART_tx((char)('.'));
	for (tripple_uint8_t i = {0, 0, 0}; TMR(i) < ram_size; i.A++, i.B++, i.C++)
	{

		*(TMR(ram_pointer) + i.A) = TEST_PATTERN; // size optimisations i is tmr checked one line ahead
	}

	while (1)
	{
		test_memory(TEST_PATTERN);
		if (++counter == 0)
		{
			PORTA ^= 1 << PA5;
			if (++counter_zwo == 0)
			{
				UART_tx((char)('.'));
			}
		}
	}

	return 0;
}

uint8_t *allocate_ram(unsigned short *out_size)
{
	unsigned short i = FLASH_START - RAM_START;
	uint8_t *memory;
	while ((memory = (uint8_t *)malloc(--i)) == 0x00 && i > 0) // i muss TMR -----------------------------------------------------------
		;
	*out_size = i;
	return memory;
}

void test_memory(unsigned short test_pattern)
{
	for (tripple_uint8_t i = {0, 0, 0}; TMR(i) < ram_size; i.A++, i.B++, i.C++)
	{

		// uint8_t *help = TMR(ram_pointer);
		uint8_t *ram_help = TMR(ram_pointer);
		if (*(ram_help + i.A) != test_pattern) // i is TMR checked one line ahead -- size optimisation
		{

			// adr = (uint8_t)(short)TMR(ram_pointer) + TMR(i);
			// val = *(TMR(ram_pointer) + TMR(i));
			adr = (uint8_t)(short)ram_help + i.A;
			val = *(ram_help + i.A);
			uart_send_report(adr, val);
			*(ram_help + TMR(i)) = test_pattern;
		}
	}
}
