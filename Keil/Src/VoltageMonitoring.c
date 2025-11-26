#include "voltageMonitoring.h"
#include "main.h"
#include <math.h>

extern ADC_HandleTypeDef hadc1;

#define NUM_SAMPLES 200
#define ADC_MID 2048.0f

float voltage_monitor_read_rms(void)
{
    uint32_t sum_sq = 0;

    for(int i=0;i<NUM_SAMPLES;i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        uint16_t val = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);

        float centered = (float)val - ADC_MID;
        sum_sq += centered*centered;
    }

    float rms = sqrtf((float)sum_sq/NUM_SAMPLES);
    float voltage = (rms/ADC_MID)*1.65f*100.0f; // simple calibration
    return voltage;
}
