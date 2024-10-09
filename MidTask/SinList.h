#pragma once

#include<stdlib.h>
#include<assert.h>
#include "ui.h"

typedef struct AlarmNode{
    int alarm_index;
    int hour;               
    int minute;
    int calDay;
    int alarmTotalTime;           
    char week_str[4];       
    struct AlarmNode *next; 
}AlarmNode;

extern AlarmNode *Alarms_NodeList;


