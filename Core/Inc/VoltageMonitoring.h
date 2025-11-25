#ifndef VOLTAGE_MONITOR_H
#define VOLTAGE_MONITOR_H

#include "stm32l4xx_hal.h"


void voltage_monitor_init(ADC_HandleTypeDef *hadc);


float voltage_monitor_read_rms(void);

#endif // VOLTAGE_MONITOR_H

