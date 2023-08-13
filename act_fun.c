/////////////////////////////
/* INCLUDES */
/////////////////////////////
#include "act_fun.h"
#include "global.h"
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#ifndef SCHEDULER_SPEED
#define SCHEDULER_SPEED 1
#endif

/////////////////////////////
/* FUNCTION DEFINITION */
/////////////////////////////
char* get_activityname(Activity activity_id);

/////////////////////////////
/*FUNCTION BODY*/
/////////////////////////////

void activity_function(activity_state* activity_pointer, int timestamp, Trigger_Type trigger)
{
    fflush(stdout);
    activity_state *current_activity = activity_pointer; /* create a pointer to access activity variables */
    int deadline = getaccumulated_timestamp(current_activity->end_time); /* get timestamp in hhmm format*/
    timestamp = remap_timestamp(timestamp); /* remap timestamp from 0-60 to 0-100*/

    switch (trigger)
    {
    case scheduled_request:
        if(deadline - timestamp > 10)
        {
            if(!current_activity->info_status)
            {
                printf("\nTime for %s\n",get_activityname(current_activity->activity_name));
                printf("\nEnter custom Time Here: ");
                current_activity->info_status = true;
                fflush(stdout);
            }
        }
        else
        {
            if(!current_activity->warning_status)
            {
                printf("Last 10 minute warning, You have to Finish %s soon\n",get_activityname(current_activity->activity_name));
                printf("\nEnter custom Time Here: ");
                current_activity->warning_status = true;
                fflush(stdout);
            }
        }
        break;
    case user_request:
        if(current_activity->activity_status == UNDONE)
        {
            char input[10];
            printf("\n*********************");
            printf("\n%s Time !!!!\n",get_activityname(current_activity->activity_name));
            printf("*********************\n");
            fflush(stdout);
            sleep(3);
            printf("scheduled Activity : %s \nDid you Finish %s (yes/no : please use lowecase) : ",get_activityname(current_activity->activity_name),get_activityname(current_activity->activity_name));
            fflush(stdout);
            scanf("%s",input);
            while(strcmp((char*)input, "yes") != 0 && strcmp((char*)input,"no") != 0)
            {
                printf ("invalid input, please try again (yes/no : please use lowecase) : ");
                scanf("%s",input);
            }
            if(!strcmp((char*)input, "yes"))
            {
                current_activity->activity_status = DONE;
            }
        }
        else
        {
            printf("Hoorah!! you finished %s already\n",get_activityname(current_activity->activity_name));
        }
        printf("\nEnter custom Time Here: ");
        break;
    default:
        break;
    }
    fflush(stdout);     
}

char* get_activityname(Activity activity_id)
{
    static char activity_name[20];
    switch(activity_id)
    {
        case jogging:
            sprintf((char*)activity_name, "Jogging");
            break;
        case breakfast:
            sprintf((char*)activity_name, "Breakfast");
            break;
        case news_reading:
            sprintf((char*)activity_name, "News_Reading");
            break;
        case cooking:
            sprintf((char*)activity_name, "Cooking");
            break;
        case lunch:
            sprintf((char*)activity_name, "Lunch");
            break;
        case afternoon_nap:
            sprintf((char*)activity_name, "Afternoon_Nap");
            break;
        case evening_walk:
            sprintf((char*)activity_name, "Evening_walk");
            break;        
        case dinner:
            sprintf((char*)activity_name, "Dinner");
            break;
        default:
        break;
    }
    return (char*)activity_name;
}

