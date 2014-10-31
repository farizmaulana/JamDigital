//File : digital_watch.h
//merujuk pada :
	/*
		File: fsm.h
		Author: waskita
		Created on March 6, 2011, 5:45 PM
	*/


#ifndef DIGITAL_WATCH_H
#define DIGITAL_WATCH_H

#ifdef __cplusplus

extern "C"
{
	#endif

	#define NO_STATE			00
	
	#define STATE_TIMEKEEPING	11
	#define STATE_SETTING 		21
	
	#define SUBSTATE_TIME		12
	#define SUBSTATE_DATE		13

	#define SUBSTATE_HOUR 		22
	#define SUBSTATE_MINUTE		23
	#define SUBSTATE_SECOND		24
	#define SUBSTATE_YEAR		25
	#define SUBSTATE_MONTH		26
	#define SUBSTATE_DAY 		27
	
	#define EVT_NONE			90
	#define EVT_MODE			91
	#define	EVT_SET				92
	#define	EVT_TICK			93

	void digital_watch_on(int *state, int *substate, int *input, int *hour, int *minute, int *second, int *day, int *month, int *year);
	#ifdef __cplusplus
}

#endif

#endif /* DIGITAL_WATCH_H */
