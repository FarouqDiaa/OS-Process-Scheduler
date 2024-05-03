#pragma once

#include "Clock/headers.h"

typedef struct Pcb
{
    int uid;
    int wait_time;
    int burst_time;
    int state;
    int arrival_time;
    int remaining_time;
    int last_run_time;
    int total_time;
    int memory_location;
} Pcb;