#include <stdio.h>
#include <string.h>
#include "NUC1xx.h"
#include "SYS.h"
#include "LCD.h"
#include "SPI.h"
#include "GPIO.h"
#include "digital_watch.h"
#include "Scankey.h"

int32_t second = 0;
int32_t minute = 0;
int32_t hour = 0;
int32_t day = 0;
int32_t month = 0;
int32_t year = 0;
int32_t state = STATE_TIMEKEEPING;
int32_t substate = SUBSTATE_TIME;
int32_t input;
int32_t number;
char TEXT[10]; 
	
void init_timer0(void)
{
	// Enable timer and select clock source 
	SYSCLK->CLKSEL1.TMR0_S = 0;
	SYSCLK->APBCLK.TMR0_EN = 1;
	
	// Select operation mode
	TIMER0->TCSR.MODE = 1; // Periodic
	
	// Calculate timeout period
	TIMER0->TCSR.PRESCALE = 255;
	TIMER0->TCMPR = 46875;
	
	// Enable interrupt
	TIMER0->TCSR.IE = 1;
	// Clear interrupt flag register
	TIMER0->TISR.TIF = 1;
	// Enable timer0 interrupt vector
	NVIC_EnableIRQ(TMR0_IRQn);
	
	// Reset counter
	TIMER0->TCSR.CRST = 1;
	// Start timer0
	TIMER0->TCSR.CEN = 1;
}

void TMR0_IRQHandler(void)
{
	second++;
	if (second > 59)
	{
		second = 0;
		minute++;
	}
	if (minute > 59)
	{
		minute = 0;
		hour++;
	}
	if (hour > 23)
	{
		hour = 0;
		day++;
	}
	if(month > 12)
	{
		month = 1;
	}
	if ((month == 1 ) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		if (day > 31)
		{
			day = 1;
			month++;
		}
		if (month > 12)
		{
			month = 1;
			year++;
		}
	}
	if ((month == 4 ) || (month == 6) || (month == 9) || (month == 11))
	{
		if (day > 30)
		{
			day = 1;
			month++;
		}
	}
	if (month == 2)
	{
		if (((year % 4) == 0) && ~((year % 100) == 0))
		{
			if (day > 29)
			{
				day = 1;
				month++;
			}
		}
		else 
		{
			if (day > 28)
			{
				day = 1;
				month++;
			}
		}
	}
	TIMER0->TISR.TIF = 1;
}

void init_LcdBackLight(void)
{
	init_LCD();
	clear_LCD();
	DrvGPIO_Open(E_GPD,14,E_IO_OUTPUT);
	DrvGPIO_ClrBit(E_GPD,14);
}

void display_clock(void)
{
	switch(state)
	{
		case STATE_TIMEKEEPING:
		{
			switch (substate)
			{
				case SUBSTATE_TIME:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",hour/10,hour%10,minute/10,minute%10,second/10,second%10);
					printS(28,20, TEXT);
					printS(28, 36, "TIME");
					clear_LCD();
					break;
				}
				case SUBSTATE_DATE:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",day/10,day%10,month/10,month%10,year/10,year%10);
					printS(28,20, TEXT);
					printS(28, 36, "DATE");
					clear_LCD();
					break;
				}
			}
		}
		case STATE_SETTING:
		{
			switch (substate)
			{
				case SUBSTATE_SECOND:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",hour/10,hour%10,minute/10,minute%10,second/10,second%10);
					printS(28,20, TEXT);
					printS(28, 36, "SECOND");
					clear_LCD();
					break;
				}
				case SUBSTATE_MINUTE:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",hour/10,hour%10,minute/10,minute%10,second/10,second%10);
					printS(28,20, TEXT);
					printS(28, 36, "MINUTE");
					clear_LCD();
					break;
				}
				case SUBSTATE_HOUR:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",hour/10,hour%10,minute/10,minute%10,second/10,second%10);
					printS(28,20, TEXT);
					printS(28, 36, "HOUR");
					clear_LCD();
					break;
				}
				case SUBSTATE_DAY:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",day/10,day%10,month/10,month%10,year/10,year%10);
					printS(28,20, TEXT);
					printS(28, 36, "DAY");
					clear_LCD();
					break;
				}
				case SUBSTATE_MONTH:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",day/10,day%10,month/10,month%10,year/10,year%10);
					printS(28,20, TEXT);
					printS(28, 36, "MONTH");
					clear_LCD();
					break;
				}
				case SUBSTATE_YEAR:
				{
					sprintf(TEXT,"%d%d:%d%d:%d%d",day/10,day%10,month/10,month%10,year/10,year%10);
					printS(28,20, TEXT);
					printS(28, 36, "YEAR");
					clear_LCD();
					break;
				}
			}
		}
	}
}

void delay_ms(uint32_t ms)
{
	int i;
	for (i=0;i<ms;i++)
	{
		DrvSYS_Delay(1000);
	}
}

int main(void)
{
	DrvSYS_UnlockProtectedReg();
	SYSCLK->PWRCON.XTL12M_EN = 1;
	DrvSYS_Delay(5000);
	SYSCLK->CLKSEL0.HCLK_S = 0;
	DrvSYS_LockProtectedReg();
	
	init_LCD();
	clear_LCD();
	OpenKeyPad();
	init_LcdBackLight();
	init_timer0();
	
	while(1)
	{
		input = 0;
		number = ScanKey();
		delay_ms(20);
		switch(number)
		{
			case 1:
				input = EVT_TICK;
			  break;
			case 3 :									
				input = EVT_MODE;
				break;
			case 4 :									
				input = EVT_SET;
				break;
		}
		digital_watch_on(&state,&substate,&input,&hour,&minute,&second,&day,&month,&year);
		display_clock();
	}
}
