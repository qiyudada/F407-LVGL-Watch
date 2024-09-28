#include "ui/ui.h"

Page_t Page_Alarm = { ui_AlarmPage_screen_init, ui_AlarmPage_screen_deinit, &ui_AlarmPage };


/*-----------------------SCREEN: ui_AlarmPage--------------------------------*/

lv_obj_t* ui_AlarmPage;
lv_obj_t* ui_AddImage;

typedef struct {
    lv_obj_t* alarmSettingPage;
    lv_obj_t* alarmSettingSwitch;
    lv_obj_t* alarmSettingLabel;
    lv_obj_t* alarmImgContainer;
} Alarm_t;

#define Alarm_Number 4
static Alarm_t alarms[Alarm_Number];
int alarmCount = 0;

void ui_event_AlarmSettingSwitch(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    int index = (int)(uintptr_t)lv_event_get_user_data(e);

    if (event_code == LV_EVENT_VALUE_CHANGED&&lv_obj_has_state(target, LV_STATE_CHECKED))
    {   
        lv_obj_add_state(alarms[index].alarmImgContainer, LV_STATE_CHECKED);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        lv_obj_clear_state(alarms[index].alarmImgContainer, LV_STATE_CHECKED);

    }
}



void ui_event_MenuAlarmpage_cb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);

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


void ui_even_AddImage_cb(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Page_Load(&Page_Settime);
    }
}



void CreateAlarmSettingPage(lv_obj_t* parent,int index)
{
    if (index > 4) return;

    while(index)
    {
        alarms[index-1].alarmSettingPage = lv_obj_create(parent);
        lv_obj_set_width(alarms[index - 1].alarmSettingPage, 230);
        lv_obj_set_height(alarms[index - 1].alarmSettingPage, 60);
        lv_obj_set_x(alarms[index - 1].alarmSettingPage, 0);
        lv_obj_set_y(alarms[index - 1].alarmSettingPage, -70+(index-1)*65);

        lv_obj_set_align(alarms[index - 1].alarmSettingPage, LV_ALIGN_CENTER);
        lv_obj_clear_flag(alarms[index - 1].alarmSettingPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_obj_set_style_bg_color(alarms[index - 1].alarmSettingPage, lv_color_hex(0x8B8D9C), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(alarms[index - 1].alarmSettingPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_grad_dir(alarms[index - 1].alarmSettingPage, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(alarms[index - 1].alarmSettingPage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(alarms[index - 1].alarmSettingPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        alarms[index - 1].alarmSettingSwitch = lv_switch_create(alarms[index - 1].alarmSettingPage);
        lv_obj_set_width(alarms[index - 1].alarmSettingSwitch, 50);
        lv_obj_set_height(alarms[index - 1].alarmSettingSwitch, 25);
        lv_obj_set_x(alarms[index - 1].alarmSettingSwitch, 70);
        lv_obj_set_y(alarms[index - 1].alarmSettingSwitch, -1);
        lv_obj_set_align(alarms[index - 1].alarmSettingSwitch, LV_ALIGN_CENTER);

        lv_obj_set_style_bg_color(alarms[index - 1].alarmSettingSwitch, lv_color_hex(0x506753), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(alarms[index - 1].alarmSettingSwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(alarms[index - 1].alarmSettingSwitch, lv_color_hex(0x4D604F), LV_PART_INDICATOR | LV_STATE_CHECKED);
        lv_obj_set_style_bg_opa(alarms[index - 1].alarmSettingSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

        alarms[index - 1].alarmSettingLabel = lv_label_create(alarms[index - 1].alarmSettingPage);
        lv_obj_set_width(alarms[index - 1].alarmSettingLabel, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(alarms[index - 1].alarmSettingLabel, LV_SIZE_CONTENT);    /// 1
        lv_obj_set_x(alarms[index - 1].alarmSettingLabel, -30);
        lv_obj_set_y(alarms[index - 1].alarmSettingLabel, 0);
        lv_obj_set_align(alarms[index - 1].alarmSettingLabel, LV_ALIGN_CENTER);
        lv_label_set_text(alarms[index - 1].alarmSettingLabel, "12:00");
        lv_obj_set_style_text_color(alarms[index - 1].alarmSettingLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(alarms[index - 1].alarmSettingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(alarms[index - 1].alarmSettingLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);


        alarms[index - 1].alarmImgContainer = lv_obj_create(alarms[index - 1].alarmSettingPage);
        lv_obj_set_width(alarms[index - 1].alarmImgContainer, 30);
        lv_obj_set_height(alarms[index - 1].alarmImgContainer, 30);
        lv_obj_set_x(alarms[index - 1].alarmImgContainer, -88);
        lv_obj_set_y(alarms[index - 1].alarmImgContainer, -1);
        lv_obj_set_align(alarms[index - 1].alarmImgContainer, LV_ALIGN_CENTER);
        lv_obj_add_flag(alarms[index - 1].alarmImgContainer, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_clear_flag(alarms[index - 1].alarmImgContainer,LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_obj_set_style_bg_img_src(alarms[index - 1].alarmImgContainer, &ui_img_alarmoff_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_img_src(alarms[index - 1].alarmImgContainer, &ui_img_alarmon_png, LV_PART_MAIN | LV_STATE_CHECKED);


        lv_obj_add_event_cb(alarms[index - 1].alarmSettingSwitch, ui_event_AlarmSettingSwitch, LV_EVENT_ALL, (void*)(uintptr_t)(index - 1));

        index--;

    }
   
}



void ui_AlarmPage_screen_init(void)
{
    ui_AlarmPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_AlarmPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_AlarmPage, lv_color_hex(0x0D0F0D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_AlarmPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_AddImage = lv_img_create(ui_AlarmPage);
    lv_img_set_src(ui_AddImage, &ui_img_add_png);
    lv_obj_set_width(ui_AddImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AddImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AddImage, 1);
    lv_obj_set_y(ui_AddImage, -132);
    lv_obj_set_align(ui_AddImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_AddImage, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui_AddImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    CreateAlarmSettingPage(ui_AlarmPage, alarmCount);
   
    lv_obj_add_event_cb(ui_AddImage, ui_even_AddImage_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_AlarmPage, ui_event_MenuAlarmpage_cb, LV_EVENT_ALL, NULL);

}

void ui_AlarmPage_screen_deinit(void)
{

}
