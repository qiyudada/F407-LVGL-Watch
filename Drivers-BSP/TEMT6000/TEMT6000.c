#include "TEMT6000.h"
#include "adc.h"

static ADC_HandleTypeDef *g_HADC_LightSensor = &hadc1;

static uint8_t TEMT6000_Calculate(float sample)
{
    float float_result = sample / 4095.0f;
    uint8_t result = (uint8_t)(float_result * 100); 
    return result;
}

uint8_t TEMT6000_ADC_Start(void)
{
    return HAL_ADC_Start(g_HADC_LightSensor);
}

/*function:TEMT6000_Read
parameter: pData
return: 0 success, 1 fail
*/
uint8_t LightSensor_Read(uint8_t *pData)
{
    float VoltSample = 0.0f;
    if (HAL_OK == HAL_ADC_PollForConversion(g_HADC_LightSensor, 10))
    {
        VoltSample = HAL_ADC_GetValue(g_HADC_LightSensor);
        *pData = TEMT6000_Calculate(VoltSample);
        return 0;
    }
    else
        return 1;
}
