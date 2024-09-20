#include "../ui.h"

Page_t Page_MessageArc = {ui_MessageArcPage_screen_init, ui_MessageArcPage_screen_deinit, &ui_MessageArcPage};
/*--------------------SCREEN: ui_MessageArcPage------------------------------*/
void ui_MessageArcPage_screen_init(void);

void ui_event_MessageArcPage(lv_event_t *e);
lv_obj_t *ui_MessageArcPage;

void ui_event_StepArc(lv_event_t *e);
lv_obj_t *ui_StepArc;
lv_obj_t *ui_Stepimg;
void ui_event_StepArcLabel(lv_event_t *e);
lv_obj_t *ui_StepArcLabel;

void ui_event_TempatureArc(lv_event_t *e);
lv_obj_t *ui_TempatureArc;
lv_obj_t *ui_Tempimg;
void ui_event_TempArcLabel(lv_event_t *e);
lv_obj_t *ui_TempArcLabel;

void ui_event_HumidityArc(lv_event_t *e);
lv_obj_t *ui_HumidityArc;
lv_obj_t *ui_Humidimg;
void ui_event_HumidArcLabel(lv_event_t *e);
lv_obj_t *ui_HumidArcLabel;

void ui_event_LightBar(lv_event_t *e);
lv_obj_t *ui_LightBar;
lv_obj_t *ui_Image2;

lv_timer_t *ui_MessageArcPageTimer;

/*--------------------SCREEN: ui_MessageArcPage------------------------------*/

void ui_event_MessageArcPage(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back_Bottom();
    }
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Load(&Page_Music);
    }
}



static void ui_timer_cb_MessageArcPage(lv_timer_t *timer)
{
    if (Page_Get_NowPage()->page_obj == &ui_MessageArcPage)
    {
        char Value_buf[6];
        lv_arc_set_value(ui_TempatureArc, MW_Interface.DTH11.temperature);
        lv_arc_set_value(ui_HumidityArc, MW_Interface.DTH11.humidity);
        sprintf(Value_buf, "%d", MW_Interface.DTH11.temperature);
        lv_label_set_text(ui_TempArcLabel, Value_buf);
        sprintf(Value_buf, "%d", MW_Interface.DTH11.humidity);
        lv_label_set_text(ui_HumidArcLabel, Value_buf);
    }
}
void ui_MessageArcPage_screen_init(void)
{

    char Value_Buffer[10];
    ui_MessageArcPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MessageArcPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_set_style_bg_color(ui_MessageArcPage, lv_color_hex(0xC47871), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MessageArcPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_MessageArcPage, lv_color_hex(0xD0B79C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_MessageArcPage, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_MessageArcPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_MessageArcPage, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StepArc = lv_arc_create(ui_MessageArcPage);
    lv_obj_set_width(ui_StepArc, 210);
    lv_obj_set_height(ui_StepArc, 210);
    lv_obj_set_align(ui_StepArc, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_StepArc, LV_OBJ_FLAG_CHECKABLE);   /// Flags
    lv_obj_clear_flag(ui_StepArc, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_arc_set_range(ui_StepArc, 0, 10000);
    lv_arc_set_value(ui_StepArc, 3500);
    lv_obj_set_style_arc_color(ui_StepArc, lv_color_hex(0x6A6D73), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StepArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StepArc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_StepArc, lv_color_hex(0xFF0C00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_StepArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_StepArc, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_StepArc, lv_color_hex(0xFF0C00), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StepArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_StepArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_StepArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_StepArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_StepArc, -1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_TempatureArc = lv_arc_create(ui_MessageArcPage);
    lv_obj_set_width(ui_TempatureArc, 160);
    lv_obj_set_height(ui_TempatureArc, 160);
    lv_obj_set_x(ui_TempatureArc, 1);
    lv_obj_set_y(ui_TempatureArc, 0);
    lv_obj_set_align(ui_TempatureArc, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_TempatureArc, LV_OBJ_FLAG_CHECKABLE);   /// Flags
    lv_obj_clear_flag(ui_TempatureArc, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_arc_set_value(ui_TempatureArc, 29);
    lv_obj_set_style_arc_color(ui_TempatureArc, lv_color_hex(0x6C6C70), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_TempatureArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_TempatureArc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_TempatureArc, lv_color_hex(0x1FB308), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_TempatureArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_TempatureArc, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_TempatureArc, lv_color_hex(0x18B208), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TempatureArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_TempatureArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_TempatureArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_TempatureArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_TempatureArc, -1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_HumidityArc = lv_arc_create(ui_MessageArcPage);
    lv_obj_set_width(ui_HumidityArc, 110);
    lv_obj_set_height(ui_HumidityArc, 110);
    lv_obj_set_x(ui_HumidityArc, 1);
    lv_obj_set_y(ui_HumidityArc, 0);
    lv_obj_set_align(ui_HumidityArc, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_HumidityArc, LV_OBJ_FLAG_CHECKABLE);   /// Flags
    lv_obj_clear_flag(ui_HumidityArc, LV_OBJ_FLAG_CLICKABLE); /// Flags
    lv_arc_set_value(ui_HumidityArc, 55);
    lv_obj_set_style_arc_color(ui_HumidityArc, lv_color_hex(0x6A6D73), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_HumidityArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_HumidityArc, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_color(ui_HumidityArc, lv_color_hex(0x00CEF6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_HumidityArc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_HumidityArc, 20, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_HumidityArc, lv_color_hex(0x00CEF6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HumidityArc, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_HumidityArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_HumidityArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_HumidityArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_HumidityArc, -1, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Stepimg = lv_img_create(ui_MessageArcPage);
    lv_img_set_src(ui_Stepimg, &ui_img_step_png);
    lv_obj_set_width(ui_Stepimg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Stepimg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Stepimg, -70);
    lv_obj_set_y(ui_Stepimg, 65);
    lv_obj_set_align(ui_Stepimg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Stepimg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Stepimg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Tempimg = lv_img_create(ui_MessageArcPage);
    lv_img_set_src(ui_Tempimg, &ui_img_tempature_png);
    lv_obj_set_width(ui_Tempimg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Tempimg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Tempimg, -50);
    lv_obj_set_y(ui_Tempimg, 47);
    lv_obj_set_align(ui_Tempimg, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Tempimg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Tempimg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Humidimg = lv_img_create(ui_MessageArcPage);
    lv_img_set_src(ui_Humidimg, &ui_img_humidity_png);
    lv_obj_set_width(ui_Humidimg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Humidimg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Humidimg, -32);
    lv_obj_set_y(ui_Humidimg, 29);
    lv_obj_set_align(ui_Humidimg, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Humidimg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Humidimg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    /*Set humidity label*/
    ui_HumidArcLabel = lv_label_create(ui_MessageArcPage);
    lv_obj_set_width(ui_HumidArcLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_HumidArcLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_HumidArcLabel, 0);
    lv_obj_set_y(ui_HumidArcLabel, 37);
    lv_obj_set_align(ui_HumidArcLabel, LV_ALIGN_CENTER);

    sprintf(Value_Buffer, "%d", MW_Interface.DTH11.humidity);
    lv_label_set_text(ui_HumidArcLabel, Value_Buffer);

    lv_obj_set_style_text_color(ui_HumidArcLabel, lv_color_hex(0x00CEF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_HumidArcLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Set tempatire label*/
    ui_TempArcLabel = lv_label_create(ui_MessageArcPage);
    lv_obj_set_width(ui_TempArcLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TempArcLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_TempArcLabel, 0);
    lv_obj_set_y(ui_TempArcLabel, 57);
    lv_obj_set_align(ui_TempArcLabel, LV_ALIGN_CENTER);

    sprintf(Value_Buffer, "%d", MW_Interface.DTH11.temperature);
    lv_label_set_text(ui_TempArcLabel, Value_Buffer);

    // lv_obj_add_flag(ui_TempArcLabel, LV_OBJ_FLAG_CHECKABLE); /// Flags

    lv_obj_set_style_text_color(ui_TempArcLabel, lv_color_hex(0x18B208), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TempArcLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StepArcLabel = lv_label_create(ui_MessageArcPage);
    lv_obj_set_width(ui_StepArcLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_StepArcLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_StepArcLabel, 0);
    lv_obj_set_y(ui_StepArcLabel, 78);
    lv_obj_set_align(ui_StepArcLabel, LV_ALIGN_CENTER);

    sprintf(Value_Buffer, "%d", MW_Interface.IMU.Steps);
    lv_label_set_text(ui_StepArcLabel, Value_Buffer);

    lv_obj_set_style_text_color(ui_StepArcLabel, lv_color_hex(0xFF0C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StepArcLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LightBar = lv_bar_create(ui_MessageArcPage);
    lv_bar_set_value(ui_LightBar, 20, LV_ANIM_OFF);
    lv_bar_set_start_value(ui_LightBar, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_LightBar, 150);
    lv_obj_set_height(ui_LightBar, 10);
    lv_obj_set_x(ui_LightBar, 7);
    lv_obj_set_y(ui_LightBar, -133);
    lv_obj_set_align(ui_LightBar, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_LightBar, LV_OBJ_FLAG_CHECKABLE); /// Flags

    lv_obj_set_style_bg_color(ui_LightBar, lv_color_hex(0xF3EF6B), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_LightBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_Image2 = lv_img_create(ui_MessageArcPage);
    lv_img_set_src(ui_Image2, &ui_img_light_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Image2, -91);
    lv_obj_set_y(ui_Image2, -133);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_add_event_cb(ui_MessageArcPage, ui_event_MessageArcPage, LV_EVENT_ALL, NULL);

    ui_MessageArcPageTimer = lv_timer_create(ui_timer_cb_MessageArcPage, 500, NULL);
}

void ui_MessageArcPage_screen_deinit(void)
{
}
