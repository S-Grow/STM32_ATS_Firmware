#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal.h"

// LD2 LED
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

// ADC pin for voltage monitoring
#define ADC_PIN GPIO_PIN_0
#define ADC_GPIO_Port GPIOA

// I2C for display
#define I2C_DISPLAY hi2c1
extern I2C_HandleTypeDef hi2c1;

// Function prototypes
void Error_Handler(void);
void SystemClock_Config(void);

#endif /* __MAIN_H */
