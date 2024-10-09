#include "ui.h"
#include "rtc.h"
#include <stdlib.h>
#include "SinList.h"

Page_t Page_Settime = {ui_SetTimePage_screen_init, ui_SetTimePage_screen_deinit, &ui_SetTimePage};

/*-----------------------SCREEN: ui_SetTimePage------------------------------------*/
lv_obj_t *ui_SetTimePage;
lv_obj_t *ui_HourRoller;
lv_obj_t *ui_MinuteRoller;
lv_obj_t *ui_SetTimeLabel;
lv_obj_t *ui_ConfirmImage;
lv_obj_t *ui_DeleteImg;
lv_obj_t *ui_Dropdown;

AlarmNode *Alarms_NodeList = NULL;

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
 * @brief set alarm time and enable alarm interrupt
 * @param alarmType RTC_ALARM_A or RTC_ALARM_B
 * @return None
 */
void RTC_Alarm_Set(void)
{
    if (Alarms_NodeList == NULL)
    {
        return;
    }

    RTC_AlarmTypeDef sAlarm = {0};

    sAlarm.AlarmTime.Hours = DEC_TO_BCD(Alarms_NodeList->hour);
    sAlarm.AlarmTime.Minutes = DEC_TO_BCD(Alarms_NodeList->minute);
    sAlarm.AlarmTime.Seconds = 0;
    sAlarm.AlarmTime.SubSeconds = 0x0;
    sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarm.AlarmMask = RTC_ALARMMASK_SECONDS;
    sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarm.AlarmDateWeekDay = DEC_TO_BCD(Alarms_NodeList->calDay);
    sAlarm.Alarm = RTC_ALARM_A;

    if (HAL_RTC_SetAlarm_IT(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
}
/**
 * @brief update alarm time
 * @param alarm_index current alarm index
 */
void UpdateAlarmTime(int alarm_index)
{
    RTC_TimeTypeDef currentTime = {0};
    RTC_DateTypeDef currentDate = {0};

    HAL_RTC_GetTime(&hrtc, &currentTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&hrtc, &currentDate, RTC_FORMAT_BCD);

    uint8_t current_weekday = BCD_TO_DEC(currentDate.WeekDay);
    uint8_t current_day = BCD_TO_DEC(currentDate.Date);

    int user_hour = atoi(alarms[alarm_index].hour_str);
    int user_minute = atoi(alarms[alarm_index].min_str);
    char user_weekstr[4];
    strncpy(user_weekstr, alarms[alarm_index].week_str, sizeof(user_weekstr));

    int user_weekday = GetUserInputWeekday(user_weekstr);
    int user_day_offset = CalculateDayOffset(current_weekday, user_weekday);
    int user_calday = user_day_offset + current_day;
    int newAlarmTime = user_calday * 1440 + user_hour * 60 + user_minute;

    AlarmNode *prev = NULL;
    AlarmNode *current = Alarms_NodeList;

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

            /*condition 1 :if node isn't the first node and the previous node's time is less than or equal to the new time*/
            
            
          
        }
        prev = current;
        current = current->next;
    }

    /*if current is NULL, create a new node*/
    if (current == NULL)
    {
        current = (AlarmNode *)malloc(sizeof(AlarmNode));
        if (current == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        current->alarm_index = alarm_index;
        current->hour = user_hour;
        current->minute = user_minute;
        strncpy(current->week_str, user_weekstr, sizeof(current->week_str));
        current->calDay = user_calday;
        current->next = NULL;

        alarms[alarm_index].alarmState = true;
    }

    /*look for new place to insert*/
    AlarmNode *insertPrev = NULL;
    AlarmNode *insertCurrent = Alarms_NodeList;

    while (insertCurrent != NULL)
    {

        int insertCurrentTime = insertCurrent->calDay * 1440 + insertCurrent->hour * 60 + insertCurrent->minute;

        if (newAlarmTime < insertCurrentTime)
        {
            break;
        }
        insertPrev = insertCurrent;
        insertCurrent = insertCurrent->next;
    }

    if (insertPrev == NULL)
    {
        current->next = Alarms_NodeList;
        Alarms_NodeList = current;
    }
    else
    {

        insertPrev->next = current;
        current->next = insertCurrent;
    }
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

void ui_event_ConfirmImg_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        if (Add_option)
        {
            Add_option = false;
            alarmCount++;
            if (alarmCount > 4)
            {
                return;
            }
            lv_roller_get_selected_str(ui_HourRoller,
                                       alarms[alarmCount - 1].hour_str, sizeof(alarms[alarmCount].hour_str));
            lv_roller_get_selected_str(ui_MinuteRoller,
                                       alarms[alarmCount - 1].min_str, sizeof(alarms[alarmCount].min_str));
            lv_dropdown_get_selected_str(ui_Dropdown, alarms[alarmCount - 1].week_str, sizeof(alarms[alarmCount - 1].week_str));
            lv_snprintf(alarms[alarmCount - 1].time_str, sizeof(alarms[alarmCount - 1].time_str), "%s:%s-%s", alarms[alarmCount - 1].hour_str, alarms[alarmCount - 1].min_str, alarms[alarmCount - 1].week_str);
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

void ui_event_DeleteImg_cb(lv_event_t *e)
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

    if (!Add_option)
    {
        ui_DeleteImg = lv_img_create(ui_SetTimePage);
        lv_img_set_src(ui_DeleteImg, &ui_img_delete_png);
        lv_obj_set_width(ui_DeleteImg, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_DeleteImg, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_DeleteImg, 100);
        lv_obj_set_y(ui_DeleteImg, -141);
        lv_obj_set_align(ui_DeleteImg, LV_ALIGN_CENTER);
        lv_obj_add_flag(ui_DeleteImg, LV_OBJ_FLAG_CLICKABLE);    /// Flags
        lv_obj_clear_flag(ui_DeleteImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

        lv_obj_add_event_cb(ui_DeleteImg, ui_event_DeleteImg_cb, LV_EVENT_ALL, NULL);
    }

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

    lv_obj_add_event_cb(ui_ConfirmImage, ui_event_ConfirmImg_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SetTimePage, ui_event_SetTimepage_cb, LV_EVENT_ALL, NULL);
}

void ui_SetTimePage_screen_deinit(void)
{
}
