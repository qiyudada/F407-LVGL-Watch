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

void MoveSpecificNode_OutAct(int alarm_index);

void MoveSpecificNode_InAct(int alarm_index);

void UpdateAlarmActiveListIndex(AlarmNode *ACt);

void UpdateAlarmInactiveListIndex(AlarmNode *InACt);


