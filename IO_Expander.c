// IO_Expander.c
// Runs on TM4C123.
// Device driver for MCP23017 IO Expander.
// Configures master to transmit data at 100Kbps.
// Configures MCP23017 register GPIOA as output.
// Increments the value of the output from 0-255.
// LEDs connected to the output turn on/off while output increments in value.
// Uses I2C communication protocol.
// Uses I2C1 module.
// TM4C123 pins:
// PA6: SCL
// PA7: SDA
//
// Kirabo Nsereko
// 1/5/2021


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "I2C.h"


#define SLAVE_ADDR 0x20 // address of MCP23017
#define IODIRA_R   0x00 // address of IODIRA register
#define GPIOA_R    0x12 // address of GPIOA register 

void Delay10us(uint32_t time);// Approximate 10.1us delay.


int main(void){
	uint8_t leds = 0; // output to MCP23017 register GPIOA
  I2C1_Init();
	Set_Slave_Addr(SLAVE_ADDR);
	RW(0); // master transmit
	
	//**********************Set IODIRA as output******************************// 
	Send_Byte(IODIRA_R, I2C_MCS_RUN|I2C_MCS_START); // select  addr of IODIRA. Run, Start
	Send_Byte(IODIRA_R, I2C_MCS_RUN|I2C_MCS_STOP); // write 0x00 to IODIRA. Run, Stop
	//************************************************************************//
	
	while(1){
	  Send_Byte(GPIOA_R,(1<<0)|(1<<1)); // select addr of GPIOA. Run, Start
	  Send_Byte(leds,(1<<0)|(1<<2)); // write  GPIOA. Run, Stop
	  leds++;
		Delay10us(50000); // 0.5s delay
	}
}


// Approximate 10.1us delay.
// variable 'i' calculated from eqn: delay = i*clock period*6cycles.
// Value of 'i' adjusted through use of logic analyzer to get more accurate delay.
// i=37 @ 16MHz clock rate. 
// Input: timescale factor. E.g. if time = 2, delay = 10*2us.
// Output: none
void Delay10us(uint32_t time){
  uint32_t i;
	while(time){
	  i = 37; 
		while(i){
		  i--;
		}
		time--;
	}
}
