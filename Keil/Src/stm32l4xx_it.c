/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  *           Ready for future peripheral usage (ADC, I2C, UART, GPIO EXTI)
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "stm32l4xx_it.h"

/* Cortex-M4 Processor Interruption and Exception Handlers */

void NMI_Handler(void)
{
    while (1) { }
}

void HardFault_Handler(void)
{
    while (1) { }
}

void MemManage_Handler(void)
{
    while (1) { }
}

void BusFault_Handler(void)
{
    while (1) { }
}

void UsageFault_Handler(void)
{
    while (1) { }
}

void SVC_Handler(void) { }

void DebugMon_Handler(void) { }

void PendSV_Handler(void) { }

void SysTick_Handler(void)
{
    HAL_IncTick();
}

/* ---------------- Peripheral Interrupt Handlers ---------------- */

/* Example: ADC1 global interrupt */
void ADC1_2_IRQHandler(void)
{
    HAL_ADC_IRQHandler(&hadc1);
}

/* Example: I2C1 event interrupt */
void I2C1_EV_IRQHandler(void)
{
    // Add HAL I2C event handler here later if needed
}

/* Example: UART2 global interrupt */
void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}

/* Example: External GPIO pin interrupt */
void EXTI15_10_IRQHandler(void)
{
    // HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13); // Example for user button
}

/* USER CODE BEGIN 1 */
/* Add other peripheral interrupt handlers here as needed */
