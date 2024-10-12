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

extern AlarmNode *Alarms_ActiveNodeList;
extern AlarmNode *Alarms_InactiveNodeList;

AlarmNode *CreateNewNode(void);

void PrintNode(AlarmNode *head);

int SortNode(AlarmNode **head);

void MoveSpecificNodeOutAct(int alarm_index);

void MoveSpecificNodeInAct(int alarm_index);

void UpdateAlarmActiveListIndex(AlarmNode *ACt);

void UpdateAlarmInactiveListIndex(AlarmNode *InACt);


