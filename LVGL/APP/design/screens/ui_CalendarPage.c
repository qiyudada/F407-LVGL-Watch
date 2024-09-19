#include "RTE_Components.h"             // Component selection
#include "ui.h"
#include "ui_helpers.h"
#include "User_DataManagement.h"

///////////////////// Page Manager //////////////////
Page_t Page_Calender = {ui_CalendarPage_screen_init, ui_CalendarPage_screen_deinit, &ui_CalendarPage};

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_CalendarPage;
lv_obj_t * ui_CalendarShowPage;

///////////////////// FUNCTIONS ////////////////////
void ui_event_CalendarPage_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        if(Page_Get_SecondPage()->page_obj==&ui_MenuPage)
        {
            Page_Back();
        }
    }
}

///////////////////// SCREEN init ////////////////////
void ui_CalendarPage_screen_init(void)
{
    MW_DateTimeTypeDef DateTime;
    MW_Interface.RealTime.GetTimeDate(&DateTime);

    ui_CalendarPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_CalendarPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_CalendarShowPage = lv_calendar_create(ui_CalendarPage);
    
    lv_calendar_set_today_date(ui_CalendarShowPage, 2000+DateTime.Year, DateTime.Month, DateTime.Date);
    lv_calendar_set_showed_date(ui_CalendarShowPage, 2000+DateTime.Year, DateTime.Month);
    lv_obj_t * ui_CalendarPageCalendar_header = lv_calendar_header_arrow_create(ui_CalendarShowPage);
    lv_obj_set_width(ui_CalendarShowPage, 240);
    lv_obj_set_height(ui_CalendarShowPage, 320);
    lv_obj_set_align(ui_CalendarShowPage, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_CalendarShowPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_CalendarShowPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_add_event_cb(ui_CalendarPage, ui_event_CalendarPage_cb, LV_EVENT_ALL, NULL);
    

}

///////////////////// SCREEN deinit ////////////////////
void ui_CalendarPage_screen_deinit(void)
{
    
}
