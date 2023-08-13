#ifndef GLOBAL_HEADER
#define GLOBAL_HEADER

/////////////////////////////
/* INCLUDES */
/////////////////////////////
#include <time.h>

/////////////////////////////
/*FUNCTION DEFINITIONS*/
/////////////////////////////
int getaccumulated_timestamp(float input);
int remap_timestamp(int timestamp);
void time_init(void);
int gethourstamp(void);
int getminstamp(void);
int getsecstamp(void);

#endif /* GLOBAL_HEADER */