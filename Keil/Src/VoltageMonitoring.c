// Voltage Monitoring Demo
// MCU: STM32 Nucleo-L476RG
// Sensor: ZMPT101B
// Author: Spencer Grow

#include <stdio.h>
#include <math.h>
#include "stm32l4xx_hal.h"
#include "main.h"
#include "Display.h"   // 7-segment display functions

#include "VoltageMonitoring.h"


// External ADC handle from main.c
extern ADC_HandleTypeDef hadc1;

static const uint16_t NUM_SAMPLES = 200;
static const float ADC_MID = 2048.0f;

// --------------------------------------------------
// Initialize ADC + GPIO for the voltage monitor
// --------------------------------------------------
void voltage_monitor_init(ADC_HandleTypeDef *hadc)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Optionally store the pointer for later RMS reads if needed
}


// --------------------------------------------------
// Read RMS voltage from ZMPT101B
// --------------------------------------------------
float voltage_monitor_read_rms(void)
{
    uint32_t sum_sq = 0;

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

        uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);

        float centered = (float)adc_val - ADC_MID;
        sum_sq += centered * centered;
    }

    float adc_rms = sqrtf((float)sum_sq / NUM_SAMPLES);

    // 3.3V → centered 1.65V peak
    float sensor_voltage = (adc_rms / ADC_MID) * 1.65f;

    // Calibration factor (adjust as needed)
    float voltage_rms = sensor_voltage * 100.0f;

    return voltage_rms;
}
