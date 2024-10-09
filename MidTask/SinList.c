#include "SinList.h"

/**
 * @brief create a new node
 * @param
 */
AlarmNode *CreateNewNode(void)
{
    AlarmNode *newNode = (AlarmNode *)malloc(sizeof(AlarmNode));
    if (newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        Error_Handler();
    }
    else
    {
        newNode->next = NULL;
        return newNode;
    }
}

/**
 * @brief printf all node message
 * @param AlarmNode *head
 */
void PrintNode(AlarmNode *head)
{
    AlarmNode *temp = head;
    while (temp != NULL)
    {
        printf("---------------------------------------\r\n");
        printf("Alarm_index:%d\r\n", temp->alarm_index);
        printf("Alarm_TotalTime:%d\r\n", temp->alarmTotalTime);
        printf("Alarm_CalDay:%d\r\n", temp->calDay);
        printf("Alarm_Hour:%d\r\n", temp->hour);
        printf("Alarm_Minute:%d\r\n", temp->minute);
        printf("---------------------------------------\r\n");
        temp = temp->next;
    }
}

/**
 * @brief sort current node list
 * @param AlarmNode *head
 * @return 0 : no need to sort, 1: need to sort
 */
int SortNode(AlarmNode **head)
{
    /*if list is null or only one element in list, no need to sort*/
    if (*head == NULL || (*head)->next == NULL)
    {
        return 1;
    }

    AlarmNode *sorted = NULL;
    AlarmNode *current = *head;

    while (current != NULL)
    {
        AlarmNode *nextNode = current->next;

        if (sorted == NULL || current->alarmTotalTime < sorted->alarmTotalTime)
        {
            /*move original node on first position to second position,new smaller node will be inserted before it*/
            current->next = sorted;
            sorted = current;
        }
        else
        {
            AlarmNode *temp = sorted;
            while (temp->next != NULL && temp->next->alarmTotalTime < current->alarmTotalTime)
            {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    *head = sorted;

    return 1;
}

/**
 *@brief move specific node to the end of list
 *@param alarm_index
 */
void MoveSpecificNodeOut(int alarm_index)
{
    AlarmNode *prev = NULL;
    AlarmNode *current = Alarms_ActiveNodeList;

    while (current != NULL && current->alarm_index != alarm_index)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Alarm not found\n");
        return;
    }

    if (prev == NULL)
    {
        Alarms_ActiveNodeList = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    current->next = NULL;

    if (Alarms_InactiveNodeList == NULL)
    {
        Alarms_InactiveNodeList = current;
    }
    else
    {
        AlarmNode *inactiveCurrent = Alarms_InactiveNodeList;
        while (inactiveCurrent->next != NULL)
        {
            inactiveCurrent = inactiveCurrent->next;
        }
        inactiveCurrent->next = current;
    }
}

void MoveSpecificNodeIn(int alarm_index)
{
    AlarmNode *prev = NULL;
    AlarmNode *current = Alarms_InactiveNodeList;

    while (current != NULL && current->alarm_index != alarm_index)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Alarm not found in inactive list\n");
        return;
    }

    if (prev == NULL)
    {
        Alarms_InactiveNodeList = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    current->next = NULL;

    if (Alarms_ActiveNodeList == NULL)
    {
        Alarms_ActiveNodeList = current;
    }
    else
    {
        AlarmNode *activeCurrent = Alarms_ActiveNodeList;
        while (activeCurrent->next != NULL)
        {
            activeCurrent = activeCurrent->next;
        }
        activeCurrent->next = current;
    }

    printf("Alarm %d moved to active list\n", alarm_index);
}
