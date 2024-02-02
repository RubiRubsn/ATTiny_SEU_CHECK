#define __AVR_ATtiny20__
#include "uart_BitBang8Mhz.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>
#include "TMR_datatype.h"
#define RAM_START 0x0040
#define FLASH_START 0x00C0

uint8_t a;
#define TEST_PATTERN 0xAA
uint8_t *allocate_ram(unsigned short *);

uint8_t *ram_pointer;
unsigned short ram_size;
void test_memory(unsigned short test_pattern);

int main(void)
{

	CCP = 0xD8;	  // disable Configuration Change Protection Register
	CLKPSR = 0x0; // Clock Division Factor = 1			//vielleicht doch durch 8
	a = 5;
	// b = a;
	UART_init();
	DDRA |= 1 << PA5; /* set PA5 to output (LED)*/

	ram_pointer = allocate_ram(&ram_size);
	for (unsigned short i = 0; i < ram_size; i++)
	{
		*(ram_pointer + i) = TEST_PATTERN;
	}
	//UART_tx_str("test 123");

	while (1)
	{
		test_memory(TEST_PATTERN);
		//UART_tx_str("Hello world!\n");

		//PORTA ^= 1 << PA5; // blink
	}

	return 0;
}

uint8_t *allocate_ram(unsigned short *out_size)
{
	unsigned short
		i = FLASH_START - RAM_START;
	uint8_t *memory;
	while ((memory = (uint8_t *)malloc(--i)) == 0x00 && i > 0)
		;
	*out_size = i;
	return memory;
}

void test_memory(unsigned short test_pattern)
{
	unsigned short i;
	for (i = 0; i < ram_size; i++)
	{
		if (*(ram_pointer + i) != test_pattern)
		{
			// send error and reset register
			uart_send_report((short)ram_pointer + i, *(ram_pointer + i));
			*(ram_pointer + i) = test_pattern;
		}
	}
}
