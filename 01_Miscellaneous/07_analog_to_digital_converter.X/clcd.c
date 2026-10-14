/*
 * File:   clcd.c
 * Author: Harish
 *
 * Created on 14 October, 2026, 4:00 PM
 */


#include <xc.h>
#include "clcd.h"

// Write byte to CLCD with control bit (instruction or data command)
void clcd_write(unsigned char byte, unsigned char control_bit) {
	// Set RS pin: 0 for instruction, 1 for data
	CLCD_RS = control_bit;
	// Place data/instruction byte on CLCD data port
	CLCD_PORT = byte;

	// Generate enable pulse (minimum 200ns pulse width)
	CLCD_EN = HI;
	CLCD_EN = LO;

	// Configure data port as input for busy flag check
	PORT_DIR = INPUT;
	// Set RW to read mode (HI = read, LO = write)
	CLCD_RW = HI;
	// Force RS to instruction mode for busy flag read
	CLCD_RS = INSTRUCTION_COMMAND;

	// Poll busy flag until CLCD is ready (CLCD_BUSY = 1 when busy)
	do {
		// Generate enable pulse for busy flag read
		CLCD_EN = HI;
		CLCD_EN = LO;
	}
	while(CLCD_BUSY);

	// Return to write mode
	CLCD_RW = LO;
	// Configure data port as output for next write
	PORT_DIR = OUTPUT;
}

// Initialize 16x2 character LCD display
void init_clcd(void) {
	// Configure PORTD (pins 0-7) as output for CLCD data bus D0-D7
	TRISD = 0x00;
	
	// Configure PORTC (pins 3-5) as output for CLCD control signals
	// RS, RW, EN on RC3, RC4, RC5 respectively
	TRISC = TRISC & 0xF8;

	// Set RW to write mode (LO = write)
	CLCD_RW = LO;

	// CLCD power-up and stabilization delay
	__delay_ms(30);
	
	// Initialization sequence for 8-bit mode (HD44780 standard procedure)
	clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
	__delay_us(4100);
	clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
	__delay_us(100);
	clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);
	__delay_us(1);
	
	// Move cursor to home position (0,0)
	CURSOR_HOME;
	__delay_us(100);
	
	// Set display mode: 2-line, 5x8 character matrix, 8-bit interface
	TWO_LINE_5x8_MATRIX_8_BIT;
	__delay_us(100);
	
	// Clear display and move cursor home
	CLEAR_DISP_SCREEN;
	__delay_us(500);
	
	// Turn on display, cursor off, blinking off
	DISP_ON_AND_CURSOR_OFF;
	__delay_us(100);
}

// Print string on CLCD at specified address
void clcd_print(const unsigned char *data, unsigned char addr) {
	// Set cursor position via address command
	clcd_write(addr, INSTRUCTION_COMMAND);
	
	// Write each character until null terminator
	while(*data != '\0') {
		clcd_write(*data++, DATA_COMMAND);
	}
}

// Print single character at specified address
void clcd_putch(const unsigned char data, unsigned char addr) {
	// Set cursor position via address command
	clcd_write(addr, INSTRUCTION_COMMAND);
	// Write single character
	clcd_write(data, DATA_COMMAND);
}