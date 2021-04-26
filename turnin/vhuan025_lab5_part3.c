/*	Author: vhuan025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES { SM_Start, SM_Wait, SM_Release } SM_STATE;

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; //configure portA as inputs
        DDRB = 0xFF; PORTB = 0x00; //configure portB as outputs
        unsigned char tmpA = 0x00; //temp var to hold value of A
	unsigned char tmpB = 0; //temp var to hold value of B
	unsigned char back = 0;
	unsigned char release = 1;
	SM_STATE = SM_Start;
        while (1) {		
		tmpA = ~PINA & 0x01; //get PA0
		switch(SM_STATE) {
			case SM_Start:
				SM_STATE = SM_Wait;
				break;
			case SM_Wait:
				release = 1;
				if(tmpA == 0x01)
					SM_STATE = SM_Release;
				else
					SM_STATE = SM_Wait;
				break;
			case SM_Release:
				release = 0;
				if(tmpA == 0x00)
                                        SM_STATE = SM_Wait;
				else
					SM_STATE = SM_Release;
                                break;
			default:
				SM_STATE = SM_Wait;
				break;
		}
		switch(SM_STATE) {
			case SM_Start:
				break;
			case SM_Wait:
				break;
			case SM_Release:
				if(release) {
				if(!back) {
					tmpB = (tmpB << 1) + 1 ;
					if(tmpB > 0x4F)	{
						tmpB = 0;
						back = 1;
					}
				}
				else {
					if(tmpB == 0)
						tmpB = 0x4F;
					else {
						tmpB = (tmpB >> 1);
						if(tmpB == 0) {
							back = 0;
						}
					}
				}
				}
				break;
		}
		PORTB = tmpB;
        }
        return 0;
}
