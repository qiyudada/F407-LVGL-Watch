#include "ui.h"
#include <stdlib.h>

Page_t Page_Alarm = {ui_AlarmPage_screen_init, ui_AlarmPage_screen_deinit, &ui_AlarmPage};

/*-----------------------SCREEN: ui_AlarmPage--------------------------------*/

lv_obj_t *ui_AlarmPage;
lv_obj_t *ui_AddImage;

Alarm_t alarms[Alarm_Number];

int alarmCount = 0;
bool Add_option = false;
int alarm_currentpointer;

void Trigger_Alarm_A(int index)
{
    LED1(0);
}

void Trigger_Alarm_B(int index)
{
    LED1(1);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    RTC_TimeTypeDef alarmTime = {0};
    RTC_DateTypeDef alarmDate = {0};

    HAL_RTC_GetTime(hrtc, &alarmTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc, &alarmDate, RTC_FORMAT_BIN);

    uint8_t current_hours = alarmTime.Hours;
    uint8_t current_minutes = alarmTime.Minutes;

    for (int i = 0; i < 4; i++)
    {
        if (alarms[i].alarmState && atoi(alarms[i].hour_str) == current_hours && atoi(alarms[i].min_str) == current_minutes)
        {
            Trigger_Alarm_A(i);
        }
    }
}

void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc)
{
    RTC_TimeTypeDef alarmTime = {0};
    RTC_DateTypeDef alarmDate = {0};

    HAL_RTC_GetTime(hrtc, &alarmTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(hrtc, &alarmDate, RTC_FORMAT_BIN);

    uint8_t current_hours = alarmTime.Hours;
    uint8_t current_minutes = alarmTime.Minutes;

    for (int i = 0; i < 4; i++)
    {
        if (alarms[i].alarmState && atoi(alarms[i].hour_str) == current_hours && atoi(alarms[i].min_str) == current_minutes)
        {
            Trigger_Alarm_B(i);
        }
    }
}

void ui_event_AlarmSettingSwitch(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    int index = (int)(uintptr_t)lv_event_get_user_data(e);

    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        alarms[index].alarmState = true;
        lv_obj_add_state(alarms[index].alarmImgContainer, LV_STATE_CHECKED);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        alarms[index].alarmState = false;
        lv_obj_clear_state(alarms[index].alarmImgContainer, LV_STATE_CHECKED);
    }
}

void ui_event_AlarmLabelSettime(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    int alarmpointer = (int)(uintptr_t)lv_event_get_user_data(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        alarm_currentpointer = alarmpointer;
        Page_Load(&Page_Settime);
    }
}

void ui_event_AlarmImgDel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    int alarmpointer = (int)(uintptr_t)lv_event_get_user_data(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {

        alarm_currentpointer = alarmpointer;
        if (alarm_currentpointer < 0 || alarm_currentpointer >= alarmCount)
            return;

        lv_obj_del(alarms[alarm_currentpointer].alarmSettingPage);

        for (int i = alarm_currentpointer; i < alarmCount - 1; i++)
        {

            alarms[i] = alarms[i + 1];
            lv_obj_set_y(alarms[i].alarmSettingPage, -70 + i * 65);

            lv_obj_remove_event_cb(alarms[i].alarmImgContainer, ui_event_AlarmImgDel);
            lv_obj_remove_event_cb(alarms[i].alarmSettingLabel, ui_event_AlarmLabelSettime);
            lv_obj_remove_event_cb(alarms[i].alarmSettingSwitch, ui_event_AlarmSettingSwitch);

            lv_obj_add_event_cb(alarms[i].alarmImgContainer, ui_event_AlarmImgDel, LV_EVENT_ALL, (void *)(uintptr_t)i);
            lv_obj_add_event_cb(alarms[i].alarmSettingLabel, ui_event_AlarmLabelSettime, LV_EVENT_ALL, (void *)(uintptr_t)i);
            lv_obj_add_event_cb(alarms[i].alarmSettingSwitch, ui_event_AlarmSettingSwitch, LV_EVENT_ALL, (void *)(uintptr_t)i);
        }
        memset(&alarms[alarmCount - 1], 0, sizeof(alarms[0]));
        if (alarmCount > 0)
        {
            --alarmCount;
        }
    }
}

void ui_event_MenuAlarmpage_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        if (Page_Get_SecondPage()->page_obj == &ui_MenuPage)
        {
            Page_Back();
        }
        else
            Page_Back_Bottom();
    }
}

void ui_even_AddImage_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Add_option = true;
        Page_Load(&Page_Settime);
    }
}

void CreateAlarmSettingPage(lv_obj_t *parent, int Number)
{
    if (Number > 4 || Number == 0)
        return;

    for (int i = 0; i < Number; i++)
    {
        /*alarmSettingPage*/
        alarms[i].alarmSettingPage = lv_obj_create(parent);
        lv_obj_set_width(alarms[i].alarmSettingPage, 230);
        lv_obj_set_height(alarms[i].alarmSettingPage, 60);
        lv_obj_set_x(alarms[i].alarmSettingPage, 0);
        lv_obj_set_y(alarms[i].alarmSettingPage, -70 + i * 65);

        lv_obj_set_align(alarms[i].alarmSettingPage, LV_ALIGN_CENTER);
        lv_obj_clear_flag(alarms[i].alarmSettingPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_bg_color(alarms[i].alarmSettingPage, lv_color_hex(0x8B8D9C), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(alarms[i].alarmSettingPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_dir(alarms[i].alarmSettingPage, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(alarms[i].alarmSettingPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(alarms[i].alarmSettingPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        /*alarmImg : long press will be delete current alarm page*/
        alarms[i].alarmImgContainer = lv_obj_create(alarms[i].alarmSettingPage);
        lv_obj_set_width(alarms[i].alarmImgContainer, 30);
        lv_obj_set_height(alarms[i].alarmImgContainer, 30);
        lv_obj_set_x(alarms[i].alarmImgContainer, -88);
        lv_obj_set_y(alarms[i].alarmImgContainer, -1);
        lv_obj_set_align(alarms[i].alarmImgContainer, LV_ALIGN_CENTER);
        lv_obj_clear_flag(alarms[i].alarmImgContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
        lv_obj_set_style_bg_img_src(alarms[i].alarmImgContainer, &ui_img_alarmoff_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_img_src(alarms[i].alarmImgContainer, &ui_img_alarmon_png, LV_PART_MAIN | LV_STATE_CHECKED);

        /*alarmSwitch: check on to open alarm function other wise close */
        alarms[i].alarmSettingSwitch = lv_switch_create(alarms[i].alarmSettingPage);
        lv_obj_set_width(alarms[i].alarmSettingSwitch, 50);
        lv_obj_set_height(alarms[i].alarmSettingSwitch, 25);
        lv_obj_set_x(alarms[i].alarmSettingSwitch, 70);
        lv_obj_set_y(alarms[i].alarmSettingSwitch, -1);
        lv_obj_set_align(alarms[i].alarmSettingSwitch, LV_ALIGN_CENTER);
        lv_obj_set_style_bg_color(alarms[i].alarmSettingSwitch, lv_color_hex(0x506753), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(alarms[i].alarmSettingSwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(alarms[i].alarmSettingSwitch, lv_color_hex(0x4D604F), LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(alarms[i].alarmSettingSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

        /*synchronize the switch turn state setting before*/
        if (!lv_obj_has_state(alarms[i].alarmSettingSwitch, LV_STATE_CHECKED) && alarms[i].alarmState)
        {
            lv_obj_add_state(alarms[i].alarmSettingSwitch, LV_STATE_CHECKED);
            lv_obj_add_state(alarms[i].alarmImgContainer, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(alarms[i].alarmSettingSwitch, LV_STATE_CHECKED);
            lv_obj_clear_state(alarms[i].alarmImgContainer, LV_STATE_CHECKED);
        }

        /*alarmSettingLabel*/
        alarms[i].alarmSettingLabel = lv_label_create(alarms[i].alarmSettingPage);
        lv_obj_set_width(alarms[i].alarmSettingLabel, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(alarms[i].alarmSettingLabel, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(alarms[i].alarmSettingLabel, -15);
        lv_obj_set_y(alarms[i].alarmSettingLabel, 0);
        lv_obj_set_align(alarms[i].alarmSettingLabel, LV_ALIGN_CENTER);

        /*setting time*/
        lv_label_set_text(alarms[i].alarmSettingLabel, alarms[i].time_str);
        lv_obj_add_flag(alarms[i].alarmSettingLabel, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_text_color(alarms[i].alarmSettingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(alarms[i].alarmSettingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(alarms[i].alarmSettingLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

        /*callback function*/
        lv_obj_add_event_cb(alarms[i].alarmImgContainer, ui_event_AlarmImgDel, LV_EVENT_ALL, (void *)(uintptr_t)i);
        lv_obj_add_event_cb(alarms[i].alarmSettingLabel, ui_event_AlarmLabelSettime, LV_EVENT_ALL, (void *)(uintptr_t)i);
        lv_obj_add_event_cb(alarms[i].alarmSettingSwitch, ui_event_AlarmSettingSwitch, LV_EVENT_ALL, (void *)(uintptr_t)i);
    }
}

void ui_AlarmPage_screen_init(void)
{
    ui_AlarmPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_AlarmPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_AlarmPage, lv_color_hex(0x0D0F0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AlarmPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_AddImage = lv_img_create(ui_AlarmPage);
    lv_img_set_src(ui_AddImage, &ui_img_add_png);
    lv_obj_set_width(ui_AddImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_AddImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_AddImage, 1);
    lv_obj_set_y(ui_AddImage, -132);
    lv_obj_set_align(ui_AddImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_AddImage, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui_AddImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    CreateAlarmSettingPage(ui_AlarmPage, alarmCount);

    lv_obj_add_event_cb(ui_AddImage, ui_even_AddImage_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_AlarmPage, ui_event_MenuAlarmpage_cb, LV_EVENT_ALL, NULL);
}

void ui_AlarmPage_screen_deinit(void)
{
}
