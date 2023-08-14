/////////////////////////////
/* INCLUDES */
/////////////////////////////
#include "main.h"
#include "global.h"
#include <stdlib.h>
#include "act_fun.h"
#include <string.h>
#include <pthread.h>

/////////////////////////////
/*LOCAL VARIABLES*/
/////////////////////////////
activity_state g_activity[Activity_max] = {0};
pthread_t user_req_thread, sys_thread;
int last_timestamp_hr = 5;
int last_timestamp_min = 0;

/////////////////////////////
/*FUNCTION BODY*/
/////////////////////////////

void print_logo(void)
{
    printf("\n******** Welcome to Activity Scheduler program ********\n");
    printf("       /^-^\\     \n");
    printf("      / o o \\ \n");
    printf("     /   Y   \\ \n");
    printf("     V \\ v / V \n");
    printf("       / - \\ \n");
    printf("      /    | \n");
    printf("(    /     | \n");
    printf(" ===/___) ||     \n");       
    printf("\n"); 
}

void activity_init(void)
{
     for(int i =0; i < Activity_max; i++)
     {
        g_activity[i].activity_name = i;
     }
     g_activity[jogging].start_time = DEFAULT_JOGGING_START;
     g_activity[jogging].end_time  = DEFAULT_JOGGING_END;

     g_activity[breakfast].start_time = DEFAULT_BREAKFAST_START;
     g_activity[breakfast].end_time  = DEFAULT_BREAKFAST_END;

     g_activity[news_reading].start_time = DEFAULT_NEWS_START;
     g_activity[news_reading].end_time  = DEFAULT_NEWS_END;
    
     g_activity[cooking].start_time = DEFAULT_COOKING_START;
     g_activity[cooking].end_time  = DEFAULT_COOKING_START;

     g_activity[lunch].start_time = DEFAULT_LUNCH_START;
     g_activity[lunch].end_time  = DEFAULT_LUNCH_END;

     g_activity[afternoon_nap].start_time = DEFAULT_NAP_START;
     g_activity[afternoon_nap].end_time  = DEFAULT_NAP_END;
     
     g_activity[evening_walk].start_time = DEFAULT_WALK_START;
     g_activity[evening_walk].end_time  = DEFAULT_WALK_END;

     g_activity[dinner].start_time = DEFAULT_DINNER_START;
     g_activity[dinner].end_time  = DEFAULT_DINNER_END;

}

activity_state* getactivity(int timestamp)
{
    for(int i = 0; i < sizeof(g_activity); i++)
    {
        int temp_start = getaccumulated_timestamp(g_activity[i].start_time);
        int temp_end = getaccumulated_timestamp(g_activity[i].end_time);

        if(timestamp >= temp_start && timestamp < temp_end)
        {
            return &g_activity[i];
        }

    }
    return NULL;
}

/* trigger activity function according to current timestamp */
void request(int timestamp, Trigger_Type request_type)
{
    activity_state* corr_Activity = getactivity(timestamp); /* check matching activity */
    if(corr_Activity == NULL)
    {
        if(request_type == user_request)
        {
            printf("No Associated Activity found \n");
            printf("\nEnter custom Time Here: ");
            fflush(stdout);
        }
    }
    else
    {
        if(request_type == scheduled_request)
        {
            fflush(stdout);
            activity_function(corr_Activity, timestamp, scheduled_request);
        }
        else if(request_type == user_request)
        {
            fflush(stdout);
            activity_function(corr_Activity, timestamp, user_request); 
        }
    }
}

/* let system get timestamp and call appropriate activity */
void* system_thread(void *arg)
{
    (void*)arg;

    while(1)
    {
        fflush(stdout);
#if SCHEDULER_SPEED == 1
        int curr_time = gethourstamp()*100 + getminstamp();
        request(curr_time, scheduled_request);
#else
        last_timestamp_min = last_timestamp_min + SCHEDULER_SPEED;
        if(last_timestamp_min > 59)
        {
            last_timestamp_hr += 1;
            last_timestamp_min = last_timestamp_min - 60;
        }
        printf("\ncurrent time : %d:%d\n",last_timestamp_hr,last_timestamp_min);
        request((last_timestamp_hr*100) + last_timestamp_min, scheduled_request);
#endif
#if SCHEDULER_SPEED > 1
        sleep(1);
#else
        sleep(60);
#endif
    }
}

/* waits for timestamp from user and triggers appropriate timestamp */
void* user_thread(void *arg)
{
    (void*)arg;
    while(true)
    {
        int user_time = 0;
        fflush(stdout);
        char input_time[10];
        scanf("%s",input_time);
        if(strcmp((char*)input_time,"now") == 0)
        {
            user_time = gethourstamp()*100 + getminstamp();
            printf("current timestamp requested : %d:%d\n",user_time/100,user_time%100);
        }
        else
        {
            user_time = getaccumulated_timestamp((float)atof(input_time));
        }

        request(user_time, user_request);
    }
}

void main()
{
    activity_init(); /* initialize activity structures */
    print_logo();
    printf("Enter custom Time Here: ");
    pthread_create(&user_req_thread, NULL, &user_thread, NULL); /* create scheduler thread */
    pthread_create(&sys_thread, NULL, &system_thread, NULL); /* crete user process thread */
    pthread_join(user_req_thread,NULL);
    pthread_join(sys_thread,NULL);

} 