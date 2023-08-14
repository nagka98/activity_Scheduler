##HOW TO USE:

- run Makefile using make
- launch program.exe
- program triggers appropriate activities according to local timestamp
- additionally, user can request specific activities but giving timestamp as input(provide timestamp in hh.mm format, type "now" for current timestamp)

##HOW TO TEST:

- find "SCHEDULER_SPEED" define located in main.h line 16
- SCHEDULER_SPEED can be adjusted until 59
- increase SCHEDULER_SPEED to accelerate process, this would increase SCHEDULER_SPEED amount of minutees every second
- sit back and relax, program shows current timetamp every increment and display appropriate activity messages

## MODFICATIONS IF NEEDED

- All Activity Taskplan can be found in main.h in form of Defines, please modify if needed
- Each Task gets Start_Time and End_Time in hh:mm format