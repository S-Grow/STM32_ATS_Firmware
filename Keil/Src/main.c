#include "main.h"
#include "display.h"
#include "voltageMonitoring.h"
#include "generator.h"

I2C_HandleTypeDef hi2c1;
ADC_HandleTypeDef hadc1;

void SystemClock_Config(void)
{
    // Minimal clock config for demo
    RCC_OscInitTypeDef osc={0};
    RCC_ClkInitTypeDef clk={0};
    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&osc);

    clk.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_ADC_CLK_ENABLE();

    // LD2
    GPIO_InitTypeDef gpio={0};
    gpio.Pin = LD2_Pin; gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL; gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LD2_GPIO_Port,&gpio);

    // ADC input
    gpio.Pin = ADC_PIN; gpio.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(ADC_GPIO_Port,&gpio);

    // I2C1 init
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x00303D5B; // ~100kHz
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);

    // ADC init
    hadc1.Instance = ADC1;
    HAL_ADC_Init(&hadc1);

    init_display();

    while(1)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(500);

        float v = voltage_monitor_read_rms();
        display_voltage(v);
    }
}
