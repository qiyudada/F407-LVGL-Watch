#include "../ui.h"

Page_t Page_Navigation = {ui_Navigation_screen_init, ui_Navigation_screen_deinit, &ui_Navigation};
/*--------------------SCREEN: ui_Navigation------------------------------*/

void ui_Navigation_screen_init(void);

void ui_event_Navigation(lv_event_t *e);
lv_obj_t *ui_Navigation;

void ui_event_SettingPic(lv_event_t *e);
lv_obj_t *ui_SettingPic;
lv_obj_t *ui_SettingLabel;

void ui_event_DrainPic(lv_event_t *e);
lv_obj_t *ui_DrainPic;
lv_obj_t *ui_DrainLabel;
lv_obj_t *ui_ClockPic;
lv_obj_t *ui_ClockLabel;

void ui_event_NFCPic(lv_event_t *e);
lv_obj_t *ui_NFCPic;
lv_obj_t *ui_NFCLabel;

void ui_event_MusicPic(lv_event_t *e);
lv_obj_t *ui_MusicPic;
lv_obj_t *ui_MusicLabel;

void ui_event_CalculatorPic(lv_event_t *e);
lv_obj_t *ui_CalculatorPic;
lv_obj_t *ui_CalculatorLabel;

void ui_event_BluetoothPic(lv_event_t *e);
lv_obj_t *ui_BluetoothPic;

void ui_event_WifiPic(lv_event_t *e);
lv_obj_t *ui_WifiPic;


lv_obj_t *ui_Calendar;

/*--------------------SCREEN: ui_Navigation------------------------------*/

void ui_event_Navigation(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back_Bottom();
    }
}
void ui_event_SettingPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_Menu);
    }
}
void ui_event_DrainPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Drain_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Drain_Close(e);
    }
}


void ui_event_ClockPic(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_Alarm);
    }
}


void ui_event_NFCPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        NFC_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        NFC_Close(e);
    }
    if (event_code == LV_EVENT_LONG_PRESSED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_NFCCard);
    }
}
void ui_event_MusicPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_Music);
    }
}

void ui_event_CalculatorPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_SHORT_CLICKED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_Computer);
    }
}

void ui_event_BluetoothPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Bluetooth_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Bluetoorh_Close(e);
    }
}
void ui_event_WifiPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Wifi_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Wifi_Close(e);
    }
}

void ui_Navigation_screen_init(void)
{
    char Navi_value_strbuf[15];
    ui_Navigation = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Navigation, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Navigation, lv_color_hex(0x0D000C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Navigation, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Navigation, lv_color_hex(0x8454E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Navigation, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Navigation, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Navigation, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_SettingPic, 50);
    lv_obj_set_height(ui_SettingPic, 50);
    lv_obj_set_x(ui_SettingPic, -75);
    lv_obj_set_y(ui_SettingPic, -100);
    lv_obj_set_align(ui_SettingPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SettingPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_SettingPic, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SettingPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SettingPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_SettingPic, &ui_img_setting_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_SettingPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_SettingPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SettingLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_SettingLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_SettingLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_SettingLabel, -75);
    lv_obj_set_y(ui_SettingLabel, -65);
    lv_obj_set_align(ui_SettingLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SettingLabel, "Settings");
    lv_obj_set_style_text_color(ui_SettingLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SettingLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DrainPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_DrainPic, 50);
    lv_obj_set_height(ui_DrainPic, 50);
    lv_obj_set_x(ui_DrainPic, 0);
    lv_obj_set_y(ui_DrainPic, -100);
    lv_obj_set_align(ui_DrainPic, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_DrainPic, LV_OBJ_FLAG_CHECKABLE);    /// Flags
    lv_obj_clear_flag(ui_DrainPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_DrainPic, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DrainPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_DrainPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_DrainPic, &ui_img_drain_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_DrainPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_DrainPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_DrainPic, lv_color_hex(0x8AE6F2), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_DrainPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_DrainLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_DrainLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_DrainLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_DrainLabel, 1);
    lv_obj_set_y(ui_DrainLabel, -65);
    lv_obj_set_align(ui_DrainLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DrainLabel, "Drain");
    lv_obj_set_style_text_color(ui_DrainLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DrainLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ClockPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_ClockPic, 50);
    lv_obj_set_height(ui_ClockPic, 50);
    lv_obj_set_x(ui_ClockPic, 75);
    lv_obj_set_y(ui_ClockPic, -100);
    lv_obj_set_align(ui_ClockPic, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ClockPic, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui_ClockPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_ClockPic, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_ClockPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ClockPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_ClockPic, &ui_img_clock_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ClockPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ClockPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ClockLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_ClockLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ClockLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ClockLabel, 76);
    lv_obj_set_y(ui_ClockLabel, -65);
    lv_obj_set_align(ui_ClockLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ClockLabel, "Alarm");
    lv_obj_set_style_text_color(ui_ClockLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ClockLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ClockLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NFCPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_NFCPic, 50);
    lv_obj_set_height(ui_NFCPic, 50);
    lv_obj_set_x(ui_NFCPic, -75);
    lv_obj_set_y(ui_NFCPic, 2);
    lv_obj_set_align(ui_NFCPic, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_NFCPic, LV_OBJ_FLAG_CHECKABLE);    /// Flags
    lv_obj_clear_flag(ui_NFCPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    
    if (!lv_obj_has_state(ui_NFCPic, LV_STATE_CHECKED) && (!MW_Interface.NFC.ConnectionState))
    {
        lv_obj_add_state(ui_NFCPic, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_NFCPic, LV_STATE_CHECKED);
    }

    lv_obj_set_style_radius(ui_NFCPic, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NFCPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NFCPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_NFCPic, &ui_img_card_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NFCPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NFCPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NFCPic, lv_color_hex(0x616FF5), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_NFCPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_NFCLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_NFCLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_NFCLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_NFCLabel, -75);
    lv_obj_set_y(ui_NFCLabel, 37);
    lv_obj_set_align(ui_NFCLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_NFCLabel, "NFC");
    lv_obj_set_style_text_color(ui_NFCLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_NFCLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_NFCLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MusicPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_MusicPic, 50);
    lv_obj_set_height(ui_MusicPic, 50);
    lv_obj_set_x(ui_MusicPic, 0);
    lv_obj_set_y(ui_MusicPic, 2);
    lv_obj_set_align(ui_MusicPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MusicPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_MusicPic, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MusicPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MusicPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_MusicPic, &ui_img_cat_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_MusicPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_MusicPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MusicLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_MusicLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MusicLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MusicLabel, 1);
    lv_obj_set_y(ui_MusicLabel, 37);
    lv_obj_set_align(ui_MusicLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MusicLabel, "Music");
    lv_obj_set_style_text_color(ui_MusicLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MusicLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MusicLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalculatorPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_CalculatorPic, 50);
    lv_obj_set_height(ui_CalculatorPic, 50);
    lv_obj_set_x(ui_CalculatorPic, 71);
    lv_obj_set_y(ui_CalculatorPic, 2);
    lv_obj_set_align(ui_CalculatorPic, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CalculatorPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_CalculatorPic, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CalculatorPic, lv_color_hex(0x2D2C2C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CalculatorPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_CalculatorPic, &ui_img_calculator_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CalculatorPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CalculatorPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalculatorLabel = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_CalculatorLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalculatorLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalculatorLabel, 74);
    lv_obj_set_y(ui_CalculatorLabel, 37);
    lv_obj_set_align(ui_CalculatorLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CalculatorLabel, "Calculator");
    lv_obj_set_style_text_color(ui_CalculatorLabel, lv_color_hex(0xF5FAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CalculatorLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CalculatorLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BluetoothPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_BluetoothPic, 25);
    lv_obj_set_height(ui_BluetoothPic, 30);
    lv_obj_set_x(ui_BluetoothPic, -18);
    lv_obj_set_y(ui_BluetoothPic, 111);
    lv_obj_set_align(ui_BluetoothPic, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BluetoothPic, LV_OBJ_FLAG_CHECKABLE);    /// Flags
    lv_obj_clear_flag(ui_BluetoothPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    if (!lv_obj_has_state(ui_BluetoothPic, LV_STATE_CHECKED) && MW_Interface.BLE.ConnectionState)
    {
        lv_obj_add_state(ui_BluetoothPic, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_BluetoothPic, LV_STATE_CHECKED);
    }

    lv_obj_set_style_bg_color(ui_BluetoothPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_BluetoothPic, &ui_img_1688708748, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_BluetoothPic, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BluetoothPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BluetoothPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_src(ui_BluetoothPic, &ui_img_1508907960, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_recolor(ui_BluetoothPic, lv_color_hex(0x4A45F9), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_recolor_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui_BluetoothPic, lv_color_hex(0x4A45F9), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_BluetoothPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_WifiPic = lv_obj_create(ui_Navigation);
    lv_obj_set_width(ui_WifiPic, 25);
    lv_obj_set_height(ui_WifiPic, 30);
    lv_obj_set_x(ui_WifiPic, 13);
    lv_obj_set_y(ui_WifiPic, 111);
    lv_obj_set_align(ui_WifiPic, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiPic, LV_OBJ_FLAG_CHECKABLE);    /// Flags
    lv_obj_clear_flag(ui_WifiPic, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_WifiPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_WifiPic, &ui_img_876457220, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui_WifiPic, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_WifiPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_WifiPic, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_src(ui_WifiPic, &ui_img_876444160, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_recolor(ui_WifiPic, lv_color_hex(0x0DE3EA), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_img_recolor_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_color(ui_WifiPic, lv_color_hex(0x0DE3EA), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_border_opa(ui_WifiPic, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    ui_Calendar = lv_label_create(ui_Navigation);
    lv_obj_set_width(ui_Calendar, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Calendar, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Calendar, -2);
    lv_obj_set_y(ui_Calendar, 290);
    lv_obj_set_align(ui_Calendar, LV_ALIGN_TOP_MID);

    /*update time label*/
    sprintf(Navi_value_strbuf, "%d/%02d %s", (char)ui_DateMonthValue, (char)ui_DateDayValue, ui_Days[ui_DataWeekdayValue - 1]);
    lv_label_set_text(ui_Calendar, Navi_value_strbuf);

    lv_obj_set_style_text_color(ui_Calendar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Calendar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_SettingPic, ui_event_SettingPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DrainPic, ui_event_DrainPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ClockPic, ui_event_ClockPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NFCPic, ui_event_NFCPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MusicPic, ui_event_MusicPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CalculatorPic, ui_event_CalculatorPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BluetoothPic, ui_event_BluetoothPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiPic, ui_event_WifiPic, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Navigation, ui_event_Navigation, LV_EVENT_ALL, NULL);
}

void ui_Navigation_screen_deinit(void)
{
}
