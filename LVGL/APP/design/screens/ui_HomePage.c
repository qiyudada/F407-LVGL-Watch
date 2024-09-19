#include "../ui.h"

Page_t Page_Home = {ui_HomePage1_screen_init, ui_HomePage_screen_deinit, &ui_HomePage};
/*--------------------SCREEN: ui_HomePage------------------------------*/
uint8_t Img_Index = 0;
void ui_HomePage1_screen_init(void);
void ui_event_HomePage1(lv_event_t *e);

lv_obj_t *ui_HomePage;

lv_obj_t *ui_ClockNumberLabel;

lv_obj_t *ui_DateLabel;
lv_timer_t *ui_HomePageTimer;

// variables
uint8_t ui_TimeHourValue = 20;
uint8_t ui_TimeMinuteValue = 30;
const char *ui_Days[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
uint8_t ui_DateMonthValue = 9;
uint8_t ui_DateDayValue = 19;
uint8_t ui_DataWeekdayValue = 4;

/*--------------------SCREEN: ui_HomePage------------------------------*/

void ui_event_HomePage1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    /*change background by clicking*/
    if (event_code == LV_EVENT_CLICKED)
    {
        Img_Index++;
        if (Img_Index > 1)
        {
            Img_Index = 0;
            lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        if (Img_Index == 1)
        {
            lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    /*Skip Navigation page*/
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Load(&Page_Navigation);
    }
    /*Skip MessageArcPage*/
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Load(&Page_MessageArc);
    }
    /*Skip Music Page*/
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Load(&Page_Music);
    }
}

static void HomePage_timer_cb(lv_timer_t *timer)
{
    char value_strbuf[10];
    MW_DateTimeTypeDef DateTime;
    MW_Interface.RealTime.GetTimeDate(&DateTime);

    if ((ui_TimeMinuteValue != DateTime.Minutes) && (ui_TimeHourValue != DateTime.Hours))
    {
        ui_TimeMinuteValue = DateTime.Minutes;
        ui_TimeHourValue = DateTime.Hours;
        sprintf(value_strbuf, "%02d:%02d", (char)ui_TimeHourValue, (char)ui_TimeMinuteValue);
        lv_label_set_text(ui_ClockNumberLabel, value_strbuf);
    }

    if (ui_DateDayValue != DateTime.Date)
    {
        ui_DateDayValue = DateTime.Date;
        ui_DataWeekdayValue = DateTime.WeekDay;
        sprintf(value_strbuf, "%s %02d", ui_Days[ui_DataWeekdayValue - 1], (char)ui_DateDayValue);
        lv_label_set_text(ui_DateLabel, value_strbuf);
    }
}

void ui_HomePage1_screen_init(void)
{
    ui_HomePage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_HomePage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    switch (Img_Index)
    {
    case 0:
        lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case 1:
        lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    default:
        break;
    }

    /*create clock*/
    ui_ClockNumberLabel = lv_label_create(ui_HomePage);
    lv_obj_set_width(ui_ClockNumberLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockNumberLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockNumberLabel, -1);
    lv_obj_set_y(ui_ClockNumberLabel, 72);
    lv_obj_set_align(ui_ClockNumberLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ClockNumberLabel, "15:20");
    lv_obj_set_style_text_color(ui_ClockNumberLabel, lv_color_hex(0xF3E7F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ClockNumberLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ClockNumberLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ClockNumberLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DateLabel = lv_label_create(ui_HomePage);
    lv_obj_set_width(ui_DateLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DateLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DateLabel, -2);
    lv_obj_set_y(ui_DateLabel, 107);
    lv_obj_set_align(ui_DateLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DateLabel, "Tue 17");
    lv_obj_set_style_text_color(ui_DateLabel, lv_color_hex(0xF3E7F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DateLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_HomePage, ui_event_HomePage1, LV_EVENT_ALL, NULL);

    lv_timer_t *ui_HomePageTimer = lv_timer_create(HomePage_timer_cb, 500, NULL);
}

void ui_HomePage_screen_deinit(void)
{
}
