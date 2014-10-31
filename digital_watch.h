//File : digital_watch.c

#include "digital_watch.h"

//********************************************************************************************
//Implementasi bahasa C dari state chart jam tangan digital

void digital_watch_on(int *state, int *substate, int *input, int *hour, int *minute, int *second, int *day, int *month, int *year)
{

	if (*state == STATE_TIMEKEEPING) 
	{
		switch(*input)
		{			
			case EVT_SET:
			{
				*state = STATE_SETTING;
				*substate = SUBSTATE_HOUR;
				break;
			}

			case EVT_MODE:
			{
				if (*substate == SUBSTATE_TIME)
				{
					*substate = SUBSTATE_DATE;
					*state = STATE_TIMEKEEPING;
				}
				else if (*substate == SUBSTATE_DATE)
				{
					*substate = SUBSTATE_TIME;
					*state = STATE_TIMEKEEPING;
				}
				break;
			}
		}
	} 
	else  if(*state == STATE_SETTING)
	{
		switch(*input)
		{
			case EVT_TICK:
			{
				*state = STATE_SETTING;
				switch(*substate)
				{
					case (SUBSTATE_HOUR) :
					{
						*hour = *hour + 1;
						break;
					}
					case (SUBSTATE_MINUTE):
					{
						*minute = *minute + 1;
						break;
					}
					case (SUBSTATE_SECOND):
					{
						*second = *second + 1;
						break;
					}
					case (SUBSTATE_DAY) :
					{
						*day = *day + 1;
						break;
					}
					case (SUBSTATE_MONTH):
					{
						*month = *month + 1;
						break;
					}
					case (SUBSTATE_YEAR):
					{
						*year = *year + 1;
						break;
					}
				}
				break;
			}		
			case EVT_SET:
			{
				if(*substate == SUBSTATE_TIME || *substate == SUBSTATE_HOUR || *substate == SUBSTATE_MINUTE || *substate == SUBSTATE_SECOND)
				{
					*substate = SUBSTATE_YEAR;
					*state = STATE_SETTING;
				}	
				else if(*substate == SUBSTATE_DATE || *substate == SUBSTATE_YEAR || *substate == SUBSTATE_MONTH || *substate == SUBSTATE_DAY)
				{
					*state = STATE_TIMEKEEPING;
					*substate = SUBSTATE_TIME;
				}
				break;
			}
			case EVT_MODE:
			{
				switch(*substate)
				{
					case (SUBSTATE_TIME):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_HOUR;
						break;
					}
					case (SUBSTATE_HOUR):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_MINUTE;
						break;
					}
					case (SUBSTATE_MINUTE):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_SECOND;
						break;
					}
					case (SUBSTATE_SECOND):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_HOUR;
						break;
					}
					case (SUBSTATE_DATE):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_YEAR;
						break;
					}
					case (SUBSTATE_YEAR):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_MONTH;
						break;
					}
					case (SUBSTATE_MONTH):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_DAY;
						break;
					}
					case (SUBSTATE_DAY):
					{
						*state = STATE_SETTING;
						*substate = SUBSTATE_YEAR;
						break;
					}
				}
			}
		}
	}
}


