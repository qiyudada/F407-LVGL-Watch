#include "ui.h"
#include <stdlib.h>
#include "SinList.h"

Page_t Page_Settime = {ui_SetTimePage_screen_init, ui_SetTimePage_screen_deinit, &ui_SetTimePage};

/*-----------------------SCREEN: ui_SetTimePage------------------------------------*/
lv_obj_t *ui_SetTimePage;
lv_obj_t *ui_HourRoller;
lv_obj_t *ui_MinuteRoller;
lv_obj_t *ui_SetTimeLabel;
lv_obj_t *ui_ConfirmImage;
lv_obj_t *ui_CancelImg;
lv_obj_t *ui_Dropdown;

AlarmNode *Alarms_ActiveNodeList = NULL;

#define DEC_TO_BCD(val) (((val / 10) << 4) + (val % 10))
#define BCD_TO_DEC(val) (((val >> 4) * 10) + (val & 0x0F))

/**
 * @brief get weekday from string
 * @param weekday_str weekday string
 * @return weekday 0x01~0x07
 */
uint8_t GetUserInputWeekday(const char *weekday_str)
{
    if (strcmp(weekday_str, "Mon") == 0)
        return RTC_WEEKDAY_MONDAY;
    if (strcmp(weekday_str, "Tue") == 0)
        return RTC_WEEKDAY_TUESDAY;
    if (strcmp(weekday_str, "Wed") == 0)
        return RTC_WEEKDAY_WEDNESDAY;
    if (strcmp(weekday_str, "Thu") == 0)
        return RTC_WEEKDAY_THURSDAY;
    if (strcmp(weekday_str, "Fri") == 0)
        return RTC_WEEKDAY_FRIDAY;
    if (strcmp(weekday_str, "Sat") == 0)
        return RTC_WEEKDAY_SATURDAY;
    if (strcmp(weekday_str, "Sun") == 0)
        return RTC_WEEKDAY_SUNDAY;

    return RTC_WEEKDAY_MONDAY;
}

/**
 * @brief calculate the day offset between current weekday and target weekday
 * @param current_weekday current weekday from rtc
 * @param target_weekday target weekday from user input
 * @return day offset
 */
uint8_t CalculateDayOffset(uint8_t current_weekday, uint8_t target_weekday)
{
    if (target_weekday >= current_weekday)
    {
        return target_weekday - current_weekday;
    }
    else
    {
        return (7 - current_weekday) + target_weekday;
    }
}

/**
 * @brief set alarm time and enable alarm interrupt,only valid for the first alarm
 * @param void
 * @return None
 */
void RTC_Alarm_Set(void)
{
    if (Alarms_ActiveNodeList == NULL)
    {
        return;
    }

    RTC_AlarmTypeDef sAlarm = {0};

    sAlarm.AlarmTime.Hours = DEC_TO_BCD(Alarms_ActiveNodeList->hour);
    sAlarm.AlarmTime.Minutes = DEC_TO_BCD(Alarms_ActiveNodeList->minute);
    sAlarm.AlarmTime.Seconds = 0;
    sAlarm.AlarmTime.SubSeconds = 0x0;
    sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarm.AlarmMask = RTC_ALARMMASK_SECONDS;
    sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarm.AlarmDateWeekDay = DEC_TO_BCD(Alarms_ActiveNodeList->calDay);
    sAlarm.Alarm = RTC_ALARM_A;

    if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
    /* print the node list */
    PrintNode(Alarms_ActiveNodeList);
}
/**
 * @brief update alarm time
 * @param alarm_index current alarm index
 */
void UpdateAlarmTime(int alarm_index)
{
    RTC_TimeTypeDef currentTime = {0};
    RTC_DateTypeDef currentDate = {0};

    /*get current time*/
    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BCD);

    uint8_t current_weekday = BCD_TO_DEC(currentDate.WeekDay);
    uint8_t current_day = BCD_TO_DEC(currentDate.Date);

    /*get user time*/
    int user_hour = atoi(alarms[alarm_index].hour_str);
    int user_minute = atoi(alarms[alarm_index].min_str);
    char user_weekstr[4];
    strncpy(user_weekstr, alarms[alarm_index].week_str, sizeof(user_weekstr));

    int user_weekday = GetUserInputWeekday(user_weekstr);
    int user_day_offset = CalculateDayOffset(current_weekday, user_weekday);
    int user_calday = user_day_offset + current_day;
    int newAlarmTime = user_calday * 1440 + user_hour * 60 + user_minute;

    AlarmNode *prev = NULL;

    if (alarms[alarm_index].alarmEnable)
    {

        AlarmNode *current = Alarms_ActiveNodeList;

        while (current != NULL)
        {
            /*if the node is already on the list*/
            if (current->alarm_index == alarm_index)
            {
                /*calculate currentAlarmTime*/
                current->alarmTotalTime = current->calDay * 1440 + current->hour * 60 + current->minute;

                /*if the time is the same, return*/
                if (newAlarmTime == current->alarmTotalTime)
                {
                    return;
                }

                /*if the time is different, update the node time message*/
                current->hour = user_hour;
                current->minute = user_minute;
                strncpy(current->week_str, user_weekstr, sizeof(current->week_str));
                current->calDay = user_calday;

                /*sort the list*/
                if (SortNode(&Alarms_ActiveNodeList))
                {
                    goto rtc_set;
                }
            }
            /*if current is not target node, move to next node*/
            prev = current;
            current = current->next;
        }

        /*if current is NULL,now it is behind in the last alarm , create a new node*/
        if (current == NULL)
        {
            current = CreateNewNode();

            /*setting value*/
            current->alarm_index = alarm_index;
            current->hour = user_hour;
            current->minute = user_minute;
            strncpy(current->week_str, user_weekstr, sizeof(current->week_str));
            current->calDay = user_calday;
            current->alarmTotalTime = current->calDay * 1440 + current->hour * 60 + current->minute;

            /*active current alarm*/
            alarms[alarm_index].alarmState = true;

            if (Alarms_ActiveNodeList == NULL)
            {
                Alarms_ActiveNodeList = current;
            }
            else
            {
                prev->next = current;
            }

            if (SortNode(&Alarms_ActiveNodeList))
            {
                goto rtc_set;
            }
        }
    }
    else
    {

        AlarmNode *current = Alarms_InactiveNodeList;

        while (current != NULL)
        {
            /*if the node is already on the list*/
            if (current->alarm_index == alarm_index)
            {
                /*calculate currentAlarmTime*/
                current->alarmTotalTime = current->calDay * 1440 + current->hour * 60 + current->minute;

                /*if the time is the same, return*/
                if (newAlarmTime == current->alarmTotalTime)
                {
                    goto rtc_set;
                }
                else
                {
                    /*if the time is different, update the node time message*/
                    current->hour = user_hour;
                    current->minute = user_minute;
                    strncpy(current->week_str, user_weekstr, sizeof(current->week_str));
                    current->calDay = user_calday;
                    goto rtc_set;
                }
            }
            /*if current is not target node, move to next node*/
            prev = current;
            current = current->next;
        }
    }

rtc_set:
    /*update rtc alarm resource*/
    RTC_Alarm_Set();
}

void ui_event_SetTimepage_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back();
    }
}

/**
 * @brief Confirm button callback
 */
void ui_event_ConfirmImg_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        if (Add_option)
        {
            Add_option = false;
            ++alarmCount;
            if (alarmCount > 4)
            {
                --alarmCount;
                printf("Alarm number is full,current alarm counts are %d\r\n", alarmCount);
                /*back to previous page,but the function will continue to execute to end*/
                Page_Back();
                return;
            }

            lv_roller_get_selected_str(ui_HourRoller,
                                       alarms[alarmCount - 1].hour_str, sizeof(alarms[alarmCount].hour_str));
            lv_roller_get_selected_str(ui_MinuteRoller,
                                       alarms[alarmCount - 1].min_str, sizeof(alarms[alarmCount].min_str));
            lv_dropdown_get_selected_str(ui_Dropdown, alarms[alarmCount - 1].week_str, sizeof(alarms[alarmCount - 1].week_str));
            lv_snprintf(alarms[alarmCount - 1].time_str, sizeof(alarms[alarmCount - 1].time_str), "%s:%s-%s", alarms[alarmCount - 1].hour_str, alarms[alarmCount - 1].min_str, alarms[alarmCount - 1].week_str);
            alarms[alarmCount - 1].alarmEnable = true;
            UpdateAlarmTime(alarmCount - 1);
        }
        else /*label option*/
        {
            lv_roller_get_selected_str(ui_HourRoller,
                                       alarms[alarm_currentpointer].hour_str, sizeof(alarms[alarm_currentpointer].hour_str));
            lv_roller_get_selected_str(ui_MinuteRoller,
                                       alarms[alarm_currentpointer].min_str, sizeof(alarms[alarm_currentpointer].min_str));
            lv_dropdown_get_selected_str(ui_Dropdown, alarms[alarm_currentpointer].week_str, sizeof(alarms[alarm_currentpointer].week_str));
            lv_snprintf(alarms[alarm_currentpointer].time_str, sizeof(alarms[alarm_currentpointer].time_str), "%s:%s-%s", alarms[alarm_currentpointer].hour_str, alarms[alarm_currentpointer].min_str, alarms[alarm_currentpointer].week_str);
            UpdateAlarmTime(alarm_currentpointer);
        }
        /*back to alarmpage*/
        Page_Back();
    }
}

void ui_event_CancelImg_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Page_Back();
    }
}

void ui_SetTimePage_screen_init(void)
{
    ui_SetTimePage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_SetTimePage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_SetTimePage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SetTimePage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HourRoller = lv_roller_create(ui_SetTimePage);
    lv_roller_set_options(ui_HourRoller,
                          "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23",
                          LV_ROLLER_MODE_NORMAL);
    if (!Add_option)
    {
        lv_roller_set_selected(ui_HourRoller, atoi(alarms[alarm_currentpointer].hour_str), LV_ANIM_OFF);
    }
    lv_obj_set_height(ui_HourRoller, 100);
    lv_obj_set_width(ui_HourRoller, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_HourRoller, -50);
    lv_obj_set_y(ui_HourRoller, 0);
    lv_obj_set_align(ui_HourRoller, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_HourRoller, lv_color_hex(0x8F8E99), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HourRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_HourRoller, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_HourRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_HourRoller, lv_color_hex(0x282C2D), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HourRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_MinuteRoller = lv_roller_create(ui_SetTimePage);
    lv_roller_set_options(ui_MinuteRoller,
                          "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59",
                          LV_ROLLER_MODE_NORMAL);
    if (!Add_option)
    {
        lv_roller_set_selected(ui_MinuteRoller, atoi(alarms[alarm_currentpointer].min_str), LV_ANIM_OFF);
    }
    lv_obj_set_height(ui_MinuteRoller, 100);
    lv_obj_set_width(ui_MinuteRoller, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MinuteRoller, 50);
    lv_obj_set_y(ui_MinuteRoller, 0);
    lv_obj_set_align(ui_MinuteRoller, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_MinuteRoller, lv_color_hex(0x8F8E99), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MinuteRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MinuteRoller, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MinuteRoller, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_MinuteRoller, lv_color_hex(0x282C2D), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MinuteRoller, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_SetTimeLabel = lv_label_create(ui_SetTimePage);
    lv_obj_set_width(ui_SetTimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SetTimeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SetTimeLabel, 0);
    lv_obj_set_y(ui_SetTimeLabel, -140);
    lv_obj_set_align(ui_SetTimeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SetTimeLabel, "Setting Time");
    lv_obj_set_style_text_color(ui_SetTimeLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SetTimeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ConfirmImage = lv_img_create(ui_SetTimePage);
    lv_img_set_src(ui_ConfirmImage, &ui_img_confirm_png);
    lv_obj_set_width(ui_ConfirmImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ConfirmImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ConfirmImage, 0);
    lv_obj_set_y(ui_ConfirmImage, 100);
    lv_obj_set_align(ui_ConfirmImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ConfirmImage, LV_OBJ_FLAG_CLICKABLE);    /// Flags
    lv_obj_clear_flag(ui_ConfirmImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_CancelImg = lv_img_create(ui_SetTimePage);
    lv_img_set_src(ui_CancelImg, &ui_img_delete_png);
    lv_obj_set_width(ui_CancelImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CancelImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CancelImg, 100);
    lv_obj_set_y(ui_CancelImg, -141);
    lv_obj_set_align(ui_CancelImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CancelImg, LV_OBJ_FLAG_CLICKABLE);    /// Flags
    lv_obj_clear_flag(ui_CancelImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Dropdown = lv_dropdown_create(ui_SetTimePage);
    lv_dropdown_set_options(ui_Dropdown, "Mon\nTue\nWed\nThu\nFri\nSat\nSun");
    if (!Add_option)
    {
        int week_index = GetUserInputWeekday(alarms[alarm_currentpointer].week_str);
        lv_dropdown_set_selected(ui_Dropdown, week_index - 1);
    }
    lv_obj_set_width(ui_Dropdown, 150);
    lv_obj_set_height(ui_Dropdown, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Dropdown, 0);
    lv_obj_set_y(ui_Dropdown, -90);
    lv_obj_set_align(ui_Dropdown, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Dropdown, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_set_style_bg_color(ui_Dropdown, lv_color_hex(0x8F8E99), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Dropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Dropdown, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Dropdown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_Dropdown, lv_color_hex(0x808080), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Dropdown, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(lv_dropdown_get_list(ui_Dropdown), lv_color_hex(0x8B8D9C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(lv_dropdown_get_list(ui_Dropdown), 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(lv_dropdown_get_list(ui_Dropdown), lv_color_hex(0x000000),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(lv_dropdown_get_list(ui_Dropdown), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_CancelImg, ui_event_CancelImg_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ConfirmImage, ui_event_ConfirmImg_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SetTimePage, ui_event_SetTimepage_cb, LV_EVENT_ALL, NULL);
}

void ui_SetTimePage_screen_deinit(void)
{
}
