#include "../ui.h"

Page_t Page_Menu = {ui_MenuPage_screen_init, ui_MenuPage_screen_deinit, &ui_MenuPage};

/*--------------------SCREEN: ui_MenuPage------------------------------*/
void ui_MenuPage_screen_init(void);

lv_obj_t *ui_MenuPage;
lv_obj_t *ui_MenuContainer;
/*bluetoorh*/
void ui_event_BluetoothSwitch(lv_event_t* e);
lv_obj_t *ui_BluetoothPanel;
lv_obj_t *ui_MenuBluetoothImage;
lv_obj_t *ui_BluetoothSwitch;
lv_obj_t *ui_MenuBluetoothLabel;
/*wifi*/
lv_obj_t *ui_WifiPanel;
lv_obj_t *ui_MenuWifiImage;
lv_obj_t *ui_MenuWifiLabel;
lv_obj_t *ui_WifiGoMoreImg;
/*calendar*/
lv_obj_t *ui_CalendarPanel;
lv_obj_t *ui_MenuCalendarImage;
lv_obj_t *ui_MenuCalendarLabel;
lv_obj_t *ui_CalendarGoMoreImg;
/*card*/
void ui_event_CardGoMoreImg(lv_event_t* e);
lv_obj_t *ui_CardPanel;
lv_obj_t *ui_MenuCardImage;
lv_obj_t *ui_MenuCardLabel;
lv_obj_t *ui_CardGoMoreImg;
/*stoptime*/
void ui_event_CalculatorGoMoreImg(lv_event_t* e);
lv_obj_t *ui_StoptimePanel;
lv_obj_t *ui_StoptimeImage;
lv_obj_t *ui_StoptimeLabel;
lv_obj_t *ui_StoptimeGoMoreImg;
/*calculator*/
lv_obj_t *ui_CalculatorPanel;
lv_obj_t *ui_CalculatorImg;
lv_obj_t *ui_CalculatorLabelMenu;
lv_obj_t *ui_CalculatorGoMoreImg;
/*mpu6050 wrist*/
void ui_event_Mpu6050WristSwitch(lv_event_t* e);
lv_obj_t* ui_Mpu6050WristPanel;
lv_obj_t* ui_Mpu6050WristImage;
lv_obj_t* ui_Mpu6050WristSwitch;
lv_obj_t* ui_Mpu6050WristLabel;

/*--------------------SCREEN: ui_MenuPage------------------------------*/

void ui_event_BluetoothSwitch(lv_event_t *e)
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

void ui_event_Mpu6050WristSwitch(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        WristWake_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        WristWake_Close(e);
    }
}

void ui_event_CardGoMoreImg(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Page_Load(&Page_NFCCard);
    }
}

void ui_event_CardDormancySwitch(lv_event_t *e)
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

void ui_event_CalculatorGoMoreImg(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Page_Load(&Page_Computer);
    }
}

void ui_event_CalendarGoMoreImg(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        Page_Load(&Page_Calender);
    }
}

void ui_event_ui_MenuPage(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back_Bottom();
    }
}


void ui_MenuPage_screen_init(void)
{
    ui_MenuPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MenuPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_MenuPage, lv_color_hex(0x040801), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MenuPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_MenuPage, lv_color_hex(0xA5ACB0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_MenuPage, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_MenuPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_MenuPage, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuContainer = lv_obj_create(ui_MenuPage);
    lv_obj_remove_style_all(ui_MenuContainer);
    lv_obj_set_width(ui_MenuContainer, 240);
    lv_obj_set_height(ui_MenuContainer, 320);
    lv_obj_set_x(ui_MenuContainer, 1);
    lv_obj_set_y(ui_MenuContainer, 2);
    lv_obj_set_align(ui_MenuContainer, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_MenuContainer, LV_OBJ_FLAG_CLICKABLE); /// Flags

    ui_BluetoothPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_BluetoothPanel, 230);
    lv_obj_set_height(ui_BluetoothPanel, 60);
    lv_obj_set_x(ui_BluetoothPanel, 0);
    lv_obj_set_y(ui_BluetoothPanel, -123);
    lv_obj_set_align(ui_BluetoothPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BluetoothPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_BluetoothPanel, lv_color_hex(0x8180DF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BluetoothPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_BluetoothPanel, lv_color_hex(0x3719E1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_BluetoothPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_BluetoothPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_BluetoothPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_BluetoothPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_BluetoothPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuBluetoothImage = lv_img_create(ui_BluetoothPanel);
    lv_img_set_src(ui_MenuBluetoothImage, &ui_img_bibluetooth_png);
    lv_obj_set_width(ui_MenuBluetoothImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuBluetoothImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuBluetoothImage, -90);
    lv_obj_set_y(ui_MenuBluetoothImage, 0);
    lv_obj_set_align(ui_MenuBluetoothImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuBluetoothImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuBluetoothImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_BluetoothSwitch = lv_switch_create(ui_BluetoothPanel);
    lv_obj_set_width(ui_BluetoothSwitch, 50);
    lv_obj_set_height(ui_BluetoothSwitch, 25);
    lv_obj_set_x(ui_BluetoothSwitch, 70);
    lv_obj_set_y(ui_BluetoothSwitch, -1);
    lv_obj_set_align(ui_BluetoothSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_BluetoothSwitch, lv_color_hex(0x7B7BDE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BluetoothSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_BluetoothSwitch, lv_color_hex(0x7B79DE), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BluetoothSwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_BluetoothSwitch, lv_color_hex(0x6059EC), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_BluetoothSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_BluetoothSwitch, lv_color_hex(0x391CE6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BluetoothSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    
    if (!lv_obj_has_state(ui_BluetoothSwitch, LV_STATE_CHECKED) && MW_Interface.BLE.ConnectionState)
    {
        lv_obj_add_state(ui_BluetoothSwitch, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_BluetoothSwitch, LV_STATE_CHECKED);
    }
    
    ui_MenuBluetoothLabel = lv_label_create(ui_BluetoothPanel);
    lv_obj_set_width(ui_MenuBluetoothLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuBluetoothLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuBluetoothLabel, -30);
    lv_obj_set_y(ui_MenuBluetoothLabel, 0);
    lv_obj_set_align(ui_MenuBluetoothLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuBluetoothLabel, "BlueTooth");
    lv_obj_set_style_text_color(ui_MenuBluetoothLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuBluetoothLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_WifiPanel, 230);
    lv_obj_set_height(ui_WifiPanel, 60);
    lv_obj_set_x(ui_WifiPanel, 0);
    lv_obj_set_y(ui_WifiPanel, -58);
    lv_obj_set_align(ui_WifiPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_WifiPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_WifiPanel, lv_color_hex(0xDD58A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_WifiPanel, lv_color_hex(0xE83C56), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_WifiPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_WifiPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_WifiPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_WifiPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_WifiPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuWifiImage = lv_img_create(ui_WifiPanel);
    lv_img_set_src(ui_MenuWifiImage, &ui_img_wifi_png);
    lv_obj_set_width(ui_MenuWifiImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuWifiImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuWifiImage, -90);
    lv_obj_set_y(ui_MenuWifiImage, 0);
    lv_obj_set_align(ui_MenuWifiImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuWifiImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuWifiImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuWifiLabel = lv_label_create(ui_WifiPanel);
    lv_obj_set_width(ui_MenuWifiLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuWifiLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuWifiLabel, -20);
    lv_obj_set_y(ui_MenuWifiLabel, 1);
    lv_obj_set_align(ui_MenuWifiLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuWifiLabel, "WIFI Connect");
    lv_obj_set_style_text_color(ui_MenuWifiLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuWifiLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiGoMoreImg = lv_img_create(ui_WifiPanel);
    lv_img_set_src(ui_WifiGoMoreImg, &ui_img_ggmoreo_png);
    lv_obj_set_width(ui_WifiGoMoreImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_WifiGoMoreImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_WifiGoMoreImg, 70);
    lv_obj_set_y(ui_WifiGoMoreImg, -1);
    lv_obj_set_align(ui_WifiGoMoreImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiGoMoreImg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_WifiGoMoreImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_CalendarPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_CalendarPanel, 230);
    lv_obj_set_height(ui_CalendarPanel, 60);
    lv_obj_set_x(ui_CalendarPanel, 0);
    lv_obj_set_y(ui_CalendarPanel, 8);
    lv_obj_set_align(ui_CalendarPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CalendarPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_CalendarPanel, lv_color_hex(0x57CC95), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CalendarPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_CalendarPanel, lv_color_hex(0x0A5B26), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_CalendarPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_CalendarPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CalendarPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CalendarPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CalendarPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuCalendarImage = lv_img_create(ui_CalendarPanel);
    lv_img_set_src(ui_MenuCalendarImage, &ui_img_phcalendar_png);
    lv_obj_set_width(ui_MenuCalendarImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuCalendarImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuCalendarImage, -90);
    lv_obj_set_y(ui_MenuCalendarImage, 0);
    lv_obj_set_align(ui_MenuCalendarImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuCalendarImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuCalendarImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuCalendarLabel = lv_label_create(ui_CalendarPanel);
    lv_obj_set_width(ui_MenuCalendarLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuCalendarLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuCalendarLabel, -30);
    lv_obj_set_y(ui_MenuCalendarLabel, 0);
    lv_obj_set_align(ui_MenuCalendarLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuCalendarLabel, "Calendar");
    lv_obj_set_style_text_color(ui_MenuCalendarLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuCalendarLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalendarGoMoreImg = lv_img_create(ui_CalendarPanel);
    lv_img_set_src(ui_CalendarGoMoreImg, &ui_img_open_png);
    lv_obj_set_width(ui_CalendarGoMoreImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalendarGoMoreImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalendarGoMoreImg, 70);
    lv_obj_set_y(ui_CalendarGoMoreImg, -1);
    lv_obj_set_align(ui_CalendarGoMoreImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CalendarGoMoreImg, LV_OBJ_FLAG_CLICKABLE);    /*img obj must be clickable*/
    lv_obj_clear_flag(ui_CalendarGoMoreImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_CardPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_CardPanel, 230);
    lv_obj_set_height(ui_CardPanel, 60);
    lv_obj_set_x(ui_CardPanel, 0);
    lv_obj_set_y(ui_CardPanel, 75);
    lv_obj_set_align(ui_CardPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CardPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_CardPanel, lv_color_hex(0xEEE765), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_CardPanel, lv_color_hex(0xFABB09), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_CardPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_CardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CardPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CardPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MenuCardImage = lv_img_create(ui_CardPanel);
    lv_img_set_src(ui_MenuCardImage, &ui_img_nfc_png);
    lv_obj_set_width(ui_MenuCardImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuCardImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuCardImage, -90);
    lv_obj_set_y(ui_MenuCardImage, 0);
    lv_obj_set_align(ui_MenuCardImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MenuCardImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_MenuCardImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_MenuCardLabel = lv_label_create(ui_CardPanel);
    lv_obj_set_width(ui_MenuCardLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MenuCardLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MenuCardLabel, -43);
    lv_obj_set_y(ui_MenuCardLabel, 0);
    lv_obj_set_align(ui_MenuCardLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MenuCardLabel, "NFC");
    lv_obj_set_style_text_color(ui_MenuCardLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MenuCardLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CardGoMoreImg = lv_img_create(ui_CardPanel);
    lv_img_set_src(ui_CardGoMoreImg, &ui_img_tokenolt_png);
    lv_obj_set_width(ui_CardGoMoreImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CardGoMoreImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CardGoMoreImg, 70);
    lv_obj_set_y(ui_CardGoMoreImg, -1);
    lv_obj_set_align(ui_CardGoMoreImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CardGoMoreImg, LV_OBJ_FLAG_CLICKABLE);    /*img obj must be clickable*/
    lv_obj_clear_flag(ui_CardGoMoreImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_StoptimePanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_StoptimePanel, 230);
    lv_obj_set_height(ui_StoptimePanel, 60);
    lv_obj_set_x(ui_StoptimePanel, 0);
    lv_obj_set_y(ui_StoptimePanel, 140);
    lv_obj_set_align(ui_StoptimePanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_StoptimePanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_StoptimePanel, lv_color_hex(0xE56FF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StoptimePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_StoptimePanel, lv_color_hex(0x9E0CAC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_StoptimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_StoptimePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_StoptimePanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_StoptimePanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_StoptimePanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StoptimeImage = lv_img_create(ui_StoptimePanel);
    lv_img_set_src(ui_StoptimeImage, &ui_img_stoptime_png);
    lv_obj_set_width(ui_StoptimeImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_StoptimeImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_StoptimeImage, -90);
    lv_obj_set_y(ui_StoptimeImage, 0);
    lv_obj_set_align(ui_StoptimeImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_StoptimeImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_StoptimeImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_StoptimeLabel = lv_label_create(ui_StoptimePanel);
    lv_obj_set_width(ui_StoptimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_StoptimeLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_StoptimeLabel, -33);
    lv_obj_set_y(ui_StoptimeLabel, 0);
    lv_obj_set_align(ui_StoptimeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_StoptimeLabel, "Stoptime");
    lv_obj_set_style_text_color(ui_StoptimeLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_StoptimeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StoptimeGoMoreImg = lv_img_create(ui_StoptimePanel);
    lv_img_set_src(ui_StoptimeGoMoreImg, &ui_img_gomore3_png);
    lv_obj_set_width(ui_StoptimeGoMoreImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_StoptimeGoMoreImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_StoptimeGoMoreImg, 70);
    lv_obj_set_y(ui_StoptimeGoMoreImg, -1);
    lv_obj_set_align(ui_StoptimeGoMoreImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_StoptimeGoMoreImg, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui_StoptimeGoMoreImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_CalculatorPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_CalculatorPanel, 230);
    lv_obj_set_height(ui_CalculatorPanel, 60);
    lv_obj_set_x(ui_CalculatorPanel, 0);
    lv_obj_set_y(ui_CalculatorPanel, 201);
    lv_obj_set_align(ui_CalculatorPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CalculatorPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_CalculatorPanel, lv_color_hex(0xD8D5D8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CalculatorPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_CalculatorPanel, lv_color_hex(0x6B696B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_CalculatorPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_CalculatorPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CalculatorPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CalculatorPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CalculatorPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalculatorImg = lv_img_create(ui_CalculatorPanel);
    lv_img_set_src(ui_CalculatorImg, &ui_img_calculator1_png);
    lv_obj_set_width(ui_CalculatorImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalculatorImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalculatorImg, -90);
    lv_obj_set_y(ui_CalculatorImg, 0);
    lv_obj_set_align(ui_CalculatorImg, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CalculatorImg, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_CalculatorImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_CalculatorLabelMenu = lv_label_create(ui_CalculatorPanel);
    lv_obj_set_width(ui_CalculatorLabelMenu, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalculatorLabelMenu, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalculatorLabelMenu, -31);
    lv_obj_set_y(ui_CalculatorLabelMenu, 0);
    lv_obj_set_align(ui_CalculatorLabelMenu, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CalculatorLabelMenu, "Calculator");
    lv_obj_set_style_text_color(ui_CalculatorLabelMenu, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CalculatorLabelMenu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalculatorGoMoreImg = lv_img_create(ui_CalculatorPanel);
    lv_img_set_src(ui_CalculatorGoMoreImg, &ui_img_opencal_png);
    lv_obj_set_width(ui_CalculatorGoMoreImg, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalculatorGoMoreImg, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalculatorGoMoreImg, 70);
    lv_obj_set_y(ui_CalculatorGoMoreImg, -1);
    lv_obj_set_align(ui_CalculatorGoMoreImg, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_CalculatorGoMoreImg, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(ui_CalculatorGoMoreImg, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    /*MPU6050*/
    ui_Mpu6050WristPanel = lv_obj_create(ui_MenuContainer);
    lv_obj_set_width(ui_Mpu6050WristPanel, 230);
    lv_obj_set_height(ui_Mpu6050WristPanel, 60);
    lv_obj_set_x(ui_Mpu6050WristPanel, 0);
    lv_obj_set_y(ui_Mpu6050WristPanel, 262);
    lv_obj_set_align(ui_Mpu6050WristPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Mpu6050WristPanel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Mpu6050WristPanel, lv_color_hex(0x8FF3F0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Mpu6050WristPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Mpu6050WristPanel, lv_color_hex(0x13BFAC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Mpu6050WristPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Mpu6050WristPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Mpu6050WristPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Mpu6050WristPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Mpu6050WristPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mpu6050WristImage = lv_img_create(ui_Mpu6050WristPanel);
    lv_img_set_src(ui_Mpu6050WristImage, &ui_img_wrist_png);
    lv_obj_set_width(ui_Mpu6050WristImage, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Mpu6050WristImage, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Mpu6050WristImage, -90);
    lv_obj_set_y(ui_Mpu6050WristImage, 0);
    lv_obj_set_align(ui_Mpu6050WristImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Mpu6050WristImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Mpu6050WristImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Mpu6050WristSwitch = lv_switch_create(ui_Mpu6050WristPanel);
    lv_obj_set_width(ui_Mpu6050WristSwitch, 50);
    lv_obj_set_height(ui_Mpu6050WristSwitch, 25);
    lv_obj_set_x(ui_Mpu6050WristSwitch, 70);
    lv_obj_set_y(ui_Mpu6050WristSwitch, -1);
    lv_obj_set_align(ui_Mpu6050WristSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Mpu6050WristSwitch, lv_color_hex(0x19EEE7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Mpu6050WristSwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Mpu6050WristSwitch, lv_color_hex(0x99F4E9), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Mpu6050WristSwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Mpu6050WristSwitch, lv_color_hex(0x67EEE0), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Mpu6050WristSwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_Mpu6050WristSwitch, lv_color_hex(0x0C949B), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Mpu6050WristSwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);


    if (!lv_obj_has_state(ui_Mpu6050WristSwitch, LV_STATE_CHECKED) && MW_Interface.IMU.wrist_is_enabled)
    {
        lv_obj_add_state(ui_Mpu6050WristSwitch, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui_Mpu6050WristSwitch, LV_STATE_CHECKED);
    }

    ui_Mpu6050WristLabel = lv_label_create(ui_Mpu6050WristPanel);
    lv_obj_set_width(ui_Mpu6050WristLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Mpu6050WristLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Mpu6050WristLabel, -25);
    lv_obj_set_y(ui_Mpu6050WristLabel, 0);
    lv_obj_set_align(ui_Mpu6050WristLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Mpu6050WristLabel, "Wrist Enable");
    lv_obj_set_style_text_color(ui_Mpu6050WristLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Mpu6050WristLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    /*event callbacks */
    lv_obj_add_event_cb(ui_BluetoothSwitch, ui_event_BluetoothSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CardGoMoreImg, ui_event_CardGoMoreImg, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CalculatorGoMoreImg, ui_event_CalculatorGoMoreImg, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CalendarGoMoreImg, ui_event_CalendarGoMoreImg, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MenuPage, ui_event_ui_MenuPage, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Mpu6050WristSwitch, ui_event_Mpu6050WristSwitch, LV_EVENT_ALL, NULL);


}

void ui_MenuPage_screen_deinit(void)
{
}
