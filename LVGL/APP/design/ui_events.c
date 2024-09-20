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
	MW_Interface.BLE.Control(0);
	MW_Interface.BLE.ConnectionState = 1;
}

void Bluetoorh_Close(lv_event_t *e)
{
	MW_Interface.BLE.Control(1);
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




