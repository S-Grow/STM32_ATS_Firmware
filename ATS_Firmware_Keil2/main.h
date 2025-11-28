/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c
  *                   This file contains the common defines of the application
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l4xx_hal.h"

// CubeMX-generated peripheral handles
extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;

// LED and button pins from CubeMX
#define LED_PIN         LD2_Pin
#define LED_GPIO_PORT   LD2_GPIO_Port
#define BUTTON_PIN      B1_Pin
#define BUTTON_GPIO_PORT B1_GPIO_Port

// Display I2C address
#define HT16K33_ADDR 0x70 << 1   // 7-bit address shifted left for HAL

// Delay for blinking LED
#define LED_BLINK_DELAY 500000

// Function prototypes
void SystemClock_Config(void);
void Error_Handler(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_ADC1_Init(void);

// Display functions
int init_display(void);
int test_display(void);

#endif /* __MAIN_H */
