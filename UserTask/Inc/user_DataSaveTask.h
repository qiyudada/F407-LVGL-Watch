#ifndef __USER_DATASAVETASK_H__
#define __USER_DATASAVETASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "sys.h"


uint8_t SettingGet(uint8_t *buf, uint8_t addr, uint8_t lenth);

uint8_t SettingSave(uint8_t *buf, uint8_t addr, uint8_t lenth);

void DataSaveTask(void *argument);

	
#ifdef __cplusplus
}
#endif

#endif

