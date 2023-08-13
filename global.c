/////////////////////////////
/* INCLUDES */
/////////////////////////////
#include "global.h"
#include <stdio.h> 

/////////////////////////////
/*LOCAL VARIABLES*/
/////////////////////////////
/* Timer Variables */
time_t rawtime;
struct tm *curr_time;

/////////////////////////////
/*FUNCTION BODY*/
/////////////////////////////

int getaccumulated_timestamp(float input)
{
    int input_hr = ((int)(input/1) >= 0 && (int)(input/1) <= 24)? (int)(input/1) : 0;
    int input_min = (int)((input - input_hr)*100); 
    int final_time = input_hr*100 + ((input_min > 59)? 59 : input_min);
    return final_time;
}

int remap_timestamp(int timestamp)
{
    int minute = timestamp%100;
    minute = (100*minute)/60;
    timestamp = (timestamp/100)*100 + minute;
    return timestamp;
}

void time_init(void)
{
    time( &rawtime );
}

int gethourstamp(void)
{
    time_init();
    curr_time = localtime(&rawtime);
    return curr_time->tm_hour;
}

int getminstamp(void)
{
    time_init();
    curr_time = localtime(&rawtime);
    return curr_time->tm_min;
}

int getsecstamp(void)
{
    time_init();
    curr_time = localtime(&rawtime);
    return curr_time->tm_sec;
}


