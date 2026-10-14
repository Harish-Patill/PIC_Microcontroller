/*
 * File:   main.c
 * Author: Harish
 *
 * Created on 14 October, 2026, 3:44 PM
 */


#include "main.h"
#include "adc.h"
#include "clcd.h"
#include <xc.h>

// Function to control LED1 based on ADC threshold
void glow_led(unsigned short adc_reg_val) {
	// LED glows if ADC value exceeds 512 (half of 10-bit max 1024)
	if(adc_reg_val > 512) {
		LED1 = ON;
	}
	else {
		LED1 = OFF;
	}
}

// Initialize all peripherals and pins
static void init_config(void) {
	// Initialize LED1 to OFF state
	LED1 = OFF;

	// Configure RB0 as output (TRISB0 = 0 means output)
	TRISB0 = 0;

	// Initialize ADC module for analog input reading
	init_adc();
	
	// Initialize character LCD display (16x2)
	init_clcd();
}

void main(void) {
	// Variable to store ADC reading from analog input (0-1023 for 10-bit ADC)
	unsigned short adc_reg_val;

	// Initialize all peripherals
	init_config();
	
	// String buffer to store converted ADC value as 4-digit ASCII string
	char str[5];

	// Display header message on LCD line 1
	clcd_print("ADC VALUE:", LINE1(0));
	
	// Main loop: continuous ADC reading and display update
	while(1) {
		// Read ADC value from CHANNEL4
		adc_reg_val = read_adc(CHANNEL4);
		
		// Update LED based on threshold comparison
		glow_led(adc_reg_val);
		
		// Convert ADC value to 4-digit decimal ASCII string
		str[0] = (adc_reg_val / 1000) + '0';      // 1000s place
		str[1] = ((adc_reg_val / 100) % 10) + '0'; // 100s place
		str[2] = ((adc_reg_val / 10) % 10) + '0';  // 10s place
		str[3] = (adc_reg_val % 10) + '0';         // 1s place
		str[4] = '\0';                             // Null terminator

		// Display converted ADC value on LCD line 2, column offset 4
		clcd_print(str, LINE2(4));
		
		// 200ms delay for readable display refresh and debounce
		__delay_ms(200);
	}
}