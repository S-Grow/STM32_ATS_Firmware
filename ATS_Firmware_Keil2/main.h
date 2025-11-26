#ifndef MAIN_H
#define MAIN_H

#include "stm32l476xx.h"
#include "SysClock.h"

/* -------- GPIO Pin Definitions -------- */
// On-board LED and button
#define LED_PIN      5
#define LED_PORT     GPIOA
#define BUTTON_PIN   13
#define BUTTON_PORT  GPIOC

// Generator pins (example)
#define GEN_CHOKE_PIN  4
#define GEN_START_PIN  3
#define GEN_RUN_PIN    5
#define GEN_PORT       GPIOA

// Any extra LEDs/indicators can go here
// #define INDICATOR_PIN  X
// #define INDICATOR_PORT GPIOB

/* -------- I2C Definitions -------- */
#define I2C_INSTANCE      I2C1
#define I2C_SCL_PIN       8
#define I2C_SDA_PIN       9
#define I2C_GPIO_PORT     GPIOB
#define HT16K33_ADDR      (0x70 << 1)   // 7-bit address shifted for HAL

/* -------- ADC Definitions -------- */
#define ADC_INSTANCE      ADC1
#define ADC_CHANNEL       ADC_CHANNEL_5   // Example
#define ADC_GPIO_PIN      GPIO_PIN_0
#define ADC_GPIO_PORT     GPIOA

/* -------- Delays / Demo Values -------- */
#define LED_BLINK_DELAY   500000  // Simple software delay

#endif /* MAIN_H */
