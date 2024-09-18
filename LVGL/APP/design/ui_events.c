#include "ui.h"
void Update_Home_Time(lv_event_t *e)
{
	// Your code here
}

void Update_Home_Date(lv_event_t *e)
{
	// Your code here
}

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
	// Your code here
}

void Bluetoorh_Close(lv_event_t *e)
{
	// Your code here
}

void Wifi_Open(lv_event_t *e)
{
	// Your code here
}

void Wifi_Close(lv_event_t *e)
{
	// Your code here
}

void Update_Navi_Date(lv_event_t *e)
{
	// Your code here
}

void Update_Step(lv_event_t *e)
{
	// Your code here
}

void Update_Tempature(lv_event_t *e)
{
	char Temp_buf[6];
	lv_arc_set_value(ui_TempatureArc, MW_Interface.DTH11.temperature);
	sprintf(Temp_buf, "%d", MW_Interface.DTH11.temperature);
	lv_label_set_text_fmt(ui_TempArcLabel, Temp_buf);
}

void Update_Humidity(lv_event_t *e)
{
	char Humid_buf[6];
	lv_arc_set_value(ui_HumidityArc, MW_Interface.DTH11.humidity);
	sprintf(Humid_buf, "%d", MW_Interface.DTH11.humidity);
	lv_label_set_text_fmt(ui_HumidArcLabel, Humid_buf);
}

void Update_Humidity_Arc(lv_event_t *e)
{
	// Your code here
}

void Update_Tempature_Arc(lv_event_t *e)
{
	// Your code here
}

void Update_Step_Arc(lv_event_t *e)
{
	// Your code here
}

void Update_Light_Intensity(lv_event_t *e)
{
	// Your code here
}
