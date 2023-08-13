#ifndef MAIN_HEADER
#define MAIN_HEADER

/////////////////////////////
/* INCLUDES */
/////////////////////////////
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

/////////////////////////////
/* COMPILER DEFINES */
/////////////////////////////
#define SCHEDULER_SPEED 1

#if SCHEDULER_SPEED > 59
#undef SCHEDULER_SPEED
#define SCHEDULER_SPEED 59
#endif

/* all defines in 24H hour.min format */
#define DEFAULT_JOGGING_START 6 
#define DEFAULT_JOGGING_END 7 

#define DEFAULT_BREAKFAST_START 8.30f
#define DEFAULT_BREAKFAST_END 9

#define DEFAULT_NEWS_START 9.30f
#define DEFAULT_NEWS_END 10

#define DEFAULT_COOKING_START 11.30f
#define DEFAULT_COOKING_END 12

#define DEFAULT_LUNCH_START 12.30f
#define DEFAULT_LUNCH_END 13.30f

#define DEFAULT_NAP_START 14
#define DEFAULT_NAP_END 16

#define DEFAULT_WALK_START 16
#define DEFAULT_WALK_END 19 

#define DEFAULT_DINNER_START 19
#define DEFAULT_DINNER_END 20

/////////////////////////////
/* ENUM DEFINITIONS*/
/////////////////////////////
typedef enum 
{
    jogging = 0,
    breakfast = 1,
    news_reading = 2,
    cooking = 3,
    lunch = 4,
    afternoon_nap = 5,
    evening_walk = 6,
    dinner = 7,
    Activity_max
}Activity;

typedef enum 
{
    UNDONE = 0,
    DONE = 1
}TaskState;

typedef enum 
{
    scheduled_request = 0,
    user_request = 1
}Trigger_Type;

/////////////////////////////
/*STRUCTURE DEFINITIONS */
/////////////////////////////
typedef struct 
{
    Activity activity_name; 
    TaskState activity_status;
    bool info_status;
    bool warning_status;
    float start_time;
    float end_time;
}activity_state;

/////////////////////////////
/*FUNCTION DEFINITIONS*/
/////////////////////////////
void activity_init(void);
activity_state* getactivity(int timestamp);

#endif /*MAIN_HEADER*/