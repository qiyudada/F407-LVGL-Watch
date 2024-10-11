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
	// Your code here
}

void NFC_Close(lv_event_t *e)
{
	// Your code here
}

void Bluetooth_Open(lv_event_t *e)
{
	MW_Interface.BLE.ConnectionState = 1;
}

void Bluetoorh_Close(lv_event_t *e)
{
	MW_Interface.BLE.ConnectionState = 0;
}

void WristWake_Open(lv_event_t* e)
{
    MW_Interface.IMU.WristEnable();
}

void WristWake_Close(lv_event_t* e)
{
    MW_Interface.IMU.WristDisable();
}


void Wifi_Open(lv_event_t *e)
{
	// Your code here
}

void Wifi_Close(lv_event_t *e)
{
	// Your code here
}




