#include "ui.h"
///////////////////// VARIABLES ////////////////////

/*--------------------SCREEN: ui_HomePage------------------------------*/
uint8_t Img_Index = 0;
void ui_HomePage1_screen_init(void);
void ui_event_HomePage1(lv_event_t *e);
lv_obj_t *ui_HomePage;
void ui_event_ClockNumberLabel(lv_event_t *e);
lv_obj_t *ui_ClockNumberLabel;
void ui_event_DateLabel(lv_event_t *e);
lv_obj_t *ui_DateLabel;
lv_timer_t *ui_HomePage1Timer;

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

void ui_event_Calendar(lv_event_t *e);
lv_obj_t *ui_Calendar;

/*--------------------SCREEN: ui_MessageArcPage------------------------------*/
extern Page_t Page_MessageArc;

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

/*--------------------SCREEN: ui_MenuPage------------------------------*/
void ui_MenuPage_screen_init(void);
lv_obj_t *ui_MenuPage;
lv_obj_t *ui_MenuContainer;
lv_obj_t *ui_BluetoothPanel;
lv_obj_t *ui_MenuBluetoothImage;
void ui_event_BluetoothSwitch(lv_event_t *e);
lv_obj_t *ui_BluetoothSwitch;
lv_obj_t *ui_MenuBluetoothLabel;
lv_obj_t *ui_WifiPanel;
lv_obj_t *ui_MenuWifiImage;
lv_obj_t *ui_MenuWifiLabel;
lv_obj_t *ui_WifiGoMoreImg;
lv_obj_t *ui_CalendarPanel;
lv_obj_t *ui_MenuCalendarImage;
lv_obj_t *ui_MenuCalendarLabel;
lv_obj_t *ui_CalendarGoMoreImg;
lv_obj_t *ui_CardPanel;
lv_obj_t *ui_MenuCardImage;
lv_obj_t *ui_MenuCardLabel;
void ui_event_CardGoMoreImg(lv_event_t *e);
lv_obj_t *ui_CardGoMoreImg;
lv_obj_t *ui_StoptimePanel;
lv_obj_t *ui_StoptimeImage;
lv_obj_t *ui_StoptimeLabel;
lv_obj_t *ui_StoptimeGoMoreImg;
void ui_event_CalculatorGoMoreImg(lv_event_t *e);
lv_obj_t *ui_CalculatorPanel;
lv_obj_t *ui_CalculatorImg;
lv_obj_t *ui_CalculatorLabelMenu;
lv_obj_t *ui_CalculatorGoMoreImg;

/*--------------------SCREEN: ui_MusicPage------------------------------*/
void ui_MusicPage_screen_init(void);
void ui_event_MusicPage(lv_event_t *e);
lv_obj_t *ui_MusicPage;
lv_obj_t *ui_MusicControl;
lv_obj_t *ui_Next;
lv_obj_t *ui_Back;
lv_obj_t *ui_IUPanel;
lv_obj_t *ui_HeartImage;
lv_obj_t *ui_SongnameLabel;
lv_obj_t *ui_SingerLabel;
lv_obj_t *ui_SongwordLabel;
lv_obj_t *ui_ShareImage;
lv_obj_t *ui_GomoreImage;

/*--------------------SCREEN: ui_NFCCardPage------------------------------*/
extern Page_t Page_NFCCard;
void ui_NFCCardPage_screen_init(void);
lv_obj_t *ui_NFCCardPage;
lv_obj_t *ui_WriteCardPanel;
lv_obj_t *ui_WriteCardImage;
lv_obj_t *ui_writeCardLabel;
lv_obj_t *ui_WriteCardGoMoreImg;
lv_obj_t *ui_ReadCardPanel;
lv_obj_t *ui_ReadCardImage;
lv_obj_t *ui_ReadCardLabel;
lv_obj_t *ui_ReadCardGoMoreImg;
lv_obj_t *ui_CardDormancyPanel;
lv_obj_t *ui_CardDormancyImage;
void ui_event_CardDormancySwitch(lv_event_t *e);
lv_obj_t *ui_CardDormancySwitch;
lv_obj_t *ui_CardDormancyLabel;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_calculator[1] = {&ui_img_calculator1_png};
const lv_img_dsc_t *ui_imgset_gomore[1] = {&ui_img_gomore3_png};
const lv_img_dsc_t *ui_imgset_iu[1] = {&ui_img_iu1_png};
const lv_img_dsc_t *ui_imgset_iu_bg[2] = {&ui_img_iu_bg2_png, &ui_img_iu_bg3_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

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

void ui_event_ClockNumberLabel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Home_Time(e);
    }
}

void ui_event_DateLabel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Home_Date(e);
    }
}

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
    if (event_code == LV_EVENT_CLICKED)
    {
        page_stack_pop(&PageStack);
        Page_Load(&Page_Music);
    }
}

void ui_event_CalculatorPic(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
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
void ui_event_Calendar(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Navi_Date(e);
    }
}

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
void ui_event_StepArc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Step(e);
    }
}
void ui_event_TempatureArc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Tempature(e);
    }
}
void ui_event_HumidityArc(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Humidity(e);
    }
}
void ui_event_HumidArcLabel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Humidity_Arc(e);
    }
}
void ui_event_TempArcLabel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Tempature_Arc(e);
    }
}
void ui_event_StepArcLabel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Step_Arc(e);
    }
}
void ui_event_LightBar(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        Update_Light_Intensity(e);
    }
}

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
/*--------------------SCREEN: ui_MusicPage------------------------------*/

void ui_event_MusicPage(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back_Bottom();
    }
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back();
    }
}

///////////////////// SCREENS-Initiation ////////////////////

/**
 *@brief  Initialize the screen
 */
void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    Pages_init();
    ui____initial_actions0 = lv_obj_create(NULL);
}
