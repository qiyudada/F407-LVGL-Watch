#include "ui.h"

void Drain_Open(lv_event_t *e)
{
	// Your code here
}

void Drain_Close(lv_event_t *e)
{
	// Your code here
}

void NFC_Open(lv_event_t *e)
{
	if(Page_Get_NowPage()->page_obj==&ui_NFCCardPage)
	{
		lv_label_set_text(ui_CardCommandLabel, "Waiting for Command...");
	}
	MW_Interface.NFC.ConnectionState = 0;
}

void NFC_Close(lv_event_t *e)
{
	if(Page_Get_NowPage()->page_obj==&ui_NFCCardPage)
	{
		lv_label_set_text(ui_CardCommandLabel, "Please Open NFC...");
	}
	MW_Interface.NFC.ConnectionState = 1;
}

void Bluetooth_Open(lv_event_t *e)
{
	MW_Interface.BLE.ConnectionState = 1;
}

void Bluetoorh_Close(lv_event_t *e)
{
	MW_Interface.BLE.ConnectionState = 0;
}

void Wifi_Open(lv_event_t *e)
{
	// Your code here
}

void Wifi_Close(lv_event_t *e)
{
	// Your code here
}

void WristWake_Open(lv_event_t *e)
{
	MW_Interface.IMU.WristEnable();
}

void WristWake_Close(lv_event_t *e)
{
	MW_Interface.IMU.WristDisable();
}
