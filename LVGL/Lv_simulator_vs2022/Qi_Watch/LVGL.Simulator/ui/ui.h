﻿// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.11
// Project name: Qi_Watch

#ifndef _QI_WATCH_UI_H
#define _QI_WATCH_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "ui_events.h"
#include "ui_helpers.h"
#include "User_PageManagement.h"
#include "User_DataManagement.h"


/*--------------------SCREEN: ui_HomePage------------------------------*/

extern uint8_t ui_TimeHourValue;
extern uint8_t ui_TimeMinuteValue;
extern const char *ui_Days[7];
extern uint8_t ui_DateMonthValue;
extern uint8_t ui_DateDayValue;
extern uint8_t ui_DataWeekdayValue;


extern  uint8_t Img_Index;
extern  Page_t Page_Home;

void ui_HomePage_screen_init(void);

void ui_event_HomePage(lv_event_t * e);
extern lv_obj_t * ui_HomePage;

void ui_event_ClockNumberLabel(lv_event_t * e);
extern lv_obj_t * ui_ClockNumberLabel;

void ui_event_DateLabel(lv_event_t * e);
extern lv_obj_t * ui_DateLabel;

extern lv_timer_t* ui_HomePageTimer;
void ui_HomePage_screen_deinit(void);


/*--------------------SCREEN: ui_Navigation------------------------------*/
extern Page_t Page_Navigation;

void ui_Navigation_screen_init(void);

extern void ui_Navigation_screen_deinit(void);

void ui_event_Navigation(lv_event_t * e);
extern lv_obj_t * ui_Navigation;

void ui_event_SettingPic(lv_event_t * e);
extern lv_obj_t * ui_SettingPic;
extern lv_obj_t * ui_SettingLabel;

void ui_event_DrainPic(lv_event_t * e);
extern lv_obj_t * ui_DrainPic;
extern lv_obj_t * ui_DrainLabel;
extern lv_obj_t * ui_ClockPic;
extern lv_obj_t * ui_ClockLabel;

void ui_event_NFCPic(lv_event_t * e);
extern lv_obj_t * ui_NFCPic;
extern lv_obj_t * ui_NFCLabel;

void ui_event_MusicPic(lv_event_t * e);
extern lv_obj_t * ui_MusicPic;
extern lv_obj_t * ui_MusicLabel;

void ui_event_CalculatorPic(lv_event_t * e);
extern lv_obj_t * ui_CalculatorPic;
extern lv_obj_t * ui_CalculatorLabel;

void ui_event_BluetoothPic(lv_event_t * e);
extern lv_obj_t * ui_BluetoothPic;

void ui_event_WifiPic(lv_event_t * e);
extern lv_obj_t * ui_WifiPic;

extern lv_obj_t * ui_Calendar;

/*--------------------SCREEN: ui_MessageArcPage------------------------------*/
extern Page_t Page_MessageArc;

extern lv_obj_t * ui_MessageArcPage;

void ui_MessageArcPage_screen_init(void);

void ui_MessageArcPage_screen_deinit(void);

void ui_event_MessageArcPage(lv_event_t * e);



extern lv_obj_t * ui_StepArc;
extern lv_obj_t * ui_Stepimg;

extern lv_obj_t * ui_StepArcLabel;


extern lv_obj_t * ui_TempatureArc;
extern lv_obj_t * ui_Tempimg;

extern lv_obj_t * ui_TempArcLabel;



extern lv_obj_t * ui_HumidityArc;
extern lv_obj_t * ui_Humidimg;

extern lv_obj_t * ui_HumidArcLabel;



extern lv_obj_t * ui_LightBar;
extern lv_obj_t * ui_Image2;

/*--------------------SCREEN: ui_MenuPage------------------------------*/

extern Page_t Page_Menu;

void ui_MenuPage_screen_init(void);

void ui_MenuPage_screen_deinit(void);

extern lv_obj_t * ui_MenuPage;
extern lv_obj_t * ui_MenuContainer;



void ui_event_BluetoothSwitch(lv_event_t * e);
extern lv_obj_t* ui_BluetoothPanel;
extern lv_obj_t* ui_MenuBluetoothImage;
extern lv_obj_t * ui_BluetoothSwitch;
extern lv_obj_t * ui_MenuBluetoothLabel;

extern lv_obj_t * ui_WifiPanel;
extern lv_obj_t * ui_MenuWifiImage;
extern lv_obj_t * ui_MenuWifiLabel;
extern lv_obj_t * ui_WifiGoMoreImg;

extern lv_obj_t * ui_CalendarPanel;
extern lv_obj_t * ui_MenuCalendarImage;
extern lv_obj_t * ui_MenuCalendarLabel;
extern lv_obj_t * ui_CalendarGoMoreImg;

extern lv_obj_t * ui_CardPanel;
extern lv_obj_t * ui_MenuCardImage;
extern lv_obj_t * ui_MenuCardLabel;
void ui_event_CardGoMoreImg(lv_event_t * e);
extern lv_obj_t * ui_CardGoMoreImg;

extern lv_obj_t * ui_MenuAlarmPanel;
extern lv_obj_t * ui_MenuAlarmImage;
extern lv_obj_t * ui_MenuAlarmLabel;
extern lv_obj_t * ui_MenuAlarmGoMoreImg;

void ui_event_CalculatorGoMoreImg(lv_event_t *e);
extern lv_obj_t * ui_CalculatorPanel;
extern lv_obj_t * ui_CalculatorImg;
extern lv_obj_t * ui_CalculatorLabelMenu;
extern lv_obj_t * ui_CalculatorGoMoreImg;

void ui_event_Mpu6050WristSwitch(lv_event_t* e);
extern lv_obj_t* ui_Mpu6050WristPanel;
extern lv_obj_t* ui_Mpu6050WristImage;
extern lv_obj_t* ui_Mpu6050WristSwitch;
extern lv_obj_t* ui_Mpu6050WristLabel;

/*--------------------SCREEN: ui_MusicPage------------------------------*/

extern Page_t Page_Music;

void ui_MusicPage_screen_init(void);

extern void ui_MusicPage_screen_deinit(void);

void ui_event_MusicPage(lv_event_t * e);
extern lv_obj_t * ui_MusicPage;
extern lv_obj_t * ui_MusicControl;
extern lv_obj_t * ui_Next;
extern lv_obj_t * ui_Back;
extern lv_obj_t * ui_IUPanel;
extern lv_obj_t * ui_HeartImage;
extern lv_obj_t * ui_SongnameLabel;
extern lv_obj_t * ui_SingerLabel;
extern lv_obj_t * ui_SongwordLabel;
extern lv_obj_t * ui_ShareImage;
extern lv_obj_t * ui_GomoreImage;


/*--------------------SCREEN: ui_NFCCardPage------------------------------*/
extern Page_t Page_NFCCard;

void ui_NFCCardPage_screen_init(void);

void ui_NFCCardPage_screen_deinit(void);

void ui_event_NFCCardpage_cb(lv_event_t* e);
extern lv_obj_t * ui_NFCCardPage;

void ui_event_WriteCardGoMoreImg(lv_event_t* e);
extern lv_obj_t * ui_WriteCardPanel;
extern lv_obj_t * ui_WriteCardImage;
extern lv_obj_t * ui_writeCardLabel;
extern lv_obj_t * ui_WriteCardGoMoreImg;


void ui_event_ReadCardGoMoreImg(lv_event_t* e);
extern lv_obj_t * ui_ReadCardPanel;
extern lv_obj_t * ui_ReadCardImage;
extern lv_obj_t * ui_ReadCardLabel;
extern lv_obj_t * ui_ReadCardGoMoreImg;
extern lv_obj_t * ui_CardDormancyPanel;
extern lv_obj_t * ui_CardDormancyImage;

void ui_event_CardDormancySwitch(lv_event_t * e);
extern lv_obj_t * ui_CardDormancySwitch;
extern lv_obj_t * ui_CardDormancyLabel;
extern lv_obj_t * ui____initial_actions0;


/*--------------------SCREEN: ui_ComputerPage------------------------------*/

extern Page_t Page_Computer;

void ui_ComputerPage_screen_init(void);

void ui_ComputerPage_screen_deinit(void);

extern lv_obj_t * ui_Computerpage;
extern lv_obj_t * ui_CompageBtnM;
extern lv_obj_t * ui_CompageTextarea;
extern lv_obj_t * ui_CompageBackBtn;

/*--------------------SCREEN: ui_ComputerPage------------------------------*/

extern Page_t Page_Calender;

extern lv_obj_t * ui_CalendarPage;
extern lv_obj_t * ui_CalendarShowPage;

void ui_CalendarPage_screen_init(void);
void ui_CalendarPage_screen_deinit(void);


/*--------------------------SCREEN: ui_AlarmPage-------------------------------------*/
extern Page_t Page_Alarm;

#define Alarm_Number 4

typedef struct {
    int alarmState;/*per alarm state*/
    char hour_str[3];
    char min_str[3];
    char day_str[4];
    char time_str[15];
    lv_obj_t* alarmSettingPage;
    lv_obj_t* alarmSettingSwitch;
    lv_obj_t* alarmSettingLabel;
    lv_obj_t* alarmImgContainer;
} Alarm_t;

extern int alarm_currentpointer;

extern Alarm_t alarms[Alarm_Number];

extern int alarmCount;/*Open alarm counts*/
extern bool Add_option;

void ui_AlarmPage_screen_init(void);
void ui_AlarmPage_screen_deinit(void);
void CreateAlarmSettingPage(lv_obj_t* parent,int index);
void ui_event_AlarmSettingSwitch(lv_event_t* e);

extern lv_obj_t* ui_AlarmPage;
extern lv_obj_t* ui_AddImage;
extern lv_obj_t* ui_AlarmSettingPage;
extern lv_obj_t* ui_AlarmSettingSwitch;
extern lv_obj_t* ui_AlarmSettingLabel;
extern lv_obj_t* ui_AlarmImgContainer;


/*--------------------------SCREEN: ui_SettingTimePage-------------------------------------*/
extern Page_t Page_Settime;

void ui_SetTimePage_screen_init(void);
void ui_SetTimePage_screen_deinit(void);

extern lv_obj_t* ui_SetTimePage;
extern lv_obj_t* ui_HourRoller;
extern lv_obj_t* ui_MinuteRoller;
extern lv_obj_t* ui_SetTimeLabel;
extern lv_obj_t* ui_ConfirmImage;
extern lv_obj_t* ui_CancelImg;
extern lv_obj_t* ui_Dropdown;

/*--------------------Picture------------------------------*/
LV_IMG_DECLARE(ui_img_iu_bg_png);    // assets/iu_bg.png
LV_IMG_DECLARE(ui_img_iu_bg3_png);    // assets/iu_bg3.png
LV_IMG_DECLARE(ui_img_setting_png);    // assets/setting.png
LV_IMG_DECLARE(ui_img_drain_png);    // assets/drain.png
LV_IMG_DECLARE(ui_img_clock_png);    // assets/clock.png
LV_IMG_DECLARE(ui_img_card_png);    // assets/card.png
LV_IMG_DECLARE(ui_img_cat_png);    // assets/cat.png
LV_IMG_DECLARE(ui_img_calculator_png);    // assets/Calculator.png
LV_IMG_DECLARE(ui_img_1688708748);    // assets/BLE-C.png
LV_IMG_DECLARE(ui_img_1508907960);    // assets/BLE-O.png
LV_IMG_DECLARE(ui_img_876457220);    // assets/Wifi-C.png
LV_IMG_DECLARE(ui_img_876444160);    // assets/Wifi-O.png
LV_IMG_DECLARE(ui_img_step_png);    // assets/step.png
LV_IMG_DECLARE(ui_img_tempature_png);    // assets/Tempature.png
LV_IMG_DECLARE(ui_img_humidity_png);    // assets/Humidity.png
LV_IMG_DECLARE(ui_img_light_png);    // assets/light.png
LV_IMG_DECLARE(ui_img_bibluetooth_png);    // assets/BiBluetooth.png
LV_IMG_DECLARE(ui_img_wifi_png);    // assets/wifi.png
LV_IMG_DECLARE(ui_img_ggmoreo_png);    // assets/GgMoreO.png
LV_IMG_DECLARE(ui_img_phcalendar_png);    // assets/PhCalendar.png
LV_IMG_DECLARE(ui_img_open_png);    // assets/open.png
LV_IMG_DECLARE(ui_img_nfc_png);    // assets/NFC.png
LV_IMG_DECLARE(ui_img_tokenolt_png);    // assets/TokenOlt.png
LV_IMG_DECLARE(ui_img_stoptime_png);    // assets/Stoptime.png
LV_IMG_DECLARE(ui_img_gomore3_png);    // assets/goMore3.png
LV_IMG_DECLARE(ui_img_calculator1_png);    // assets/calculator1.png
LV_IMG_DECLARE(ui_img_opencal_png);    // assets/opencal.png
LV_IMG_DECLARE(ui_img_play_png);    // assets/Play.png
LV_IMG_DECLARE(ui_img_suspend_png);    // assets/Suspend.png
LV_IMG_DECLARE(ui_img_next_png);    // assets/Next.png
LV_IMG_DECLARE(ui_img_back_png);    // assets/Back.png
LV_IMG_DECLARE(ui_img_iu1_png);    // assets/IU1.png
LV_IMG_DECLARE(ui_img_heart_png);    // assets/heart.png
LV_IMG_DECLARE(ui_img_phsharefill_png);    // assets/PhShareFill.png
LV_IMG_DECLARE(ui_img_writecard_png);    // assets/writecard.png
LV_IMG_DECLARE(ui_img_readcard_png);    // assets/Readcard.png
LV_IMG_DECLARE(ui_img_nfcoff_png);    // assets/Nfcoff.png
LV_IMG_DECLARE(ui_img_iu_bg2_png);    // assets/iu_bg2.png
LV_IMG_DECLARE(ui_img_wrist_png);    // assets/iu_bg2.png
LV_IMG_DECLARE(ui_img_add_png);    // assets/add.png
LV_IMG_DECLARE(ui_img_alarmoff_png);    // assets/AlarmOff.png
LV_IMG_DECLARE(ui_img_alarmon_png);    // assets/AlarmOn.png
LV_IMG_DECLARE(ui_img_confirm_png);    // assets/Confirm.png
LV_IMG_DECLARE(ui_img_alarm_png);    // assets/Alarm.png
LV_IMG_DECLARE(ui_img_delete_png);    // assets/delete.png

/*extra font declations */
LV_FONT_DECLARE(ui_font_Cuyuan24);
LV_FONT_DECLARE(ui_font_Number);



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
