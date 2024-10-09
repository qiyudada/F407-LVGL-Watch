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
        return newNode;
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
        printf("Alarm_index:%d\n", temp->alarm_index);
        printf("Alarm_TotalTime:%d\n", temp->alarmTotalTime);
        printf("Alarm_CalDay:%d\n", temp->calDay);
        printf("Alarm_Hour:%d\n", temp->hour);
        printf("Alarm_Minute:%d\n", temp->minute);
        temp = temp->next;
    }
}

/**
 * @brief sort current node list
 * @param AlarmNode *head
 */
void SortNode(AlarmNode **head)
{
    /*if list is null or only one element in list, no need to sort*/
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
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
}
