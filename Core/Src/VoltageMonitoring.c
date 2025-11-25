// Voltage Monitoring Demo
// MCU: STM32 Nucleo-L476RG
// Sensor: ZMPT101B
// Author: Spencer Grow

#include "stm32l4xx_hal.h"
#include "Display.h"   // 7-segment display functions

// ADC handle
ADC_HandleTypeDef hadc1;

// Thresholds (not used in demo)
float low_voltage  = 86.0f;
float high_voltage = 128.0f;

// Function prototypes
float Read_Voltage_RMS(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);

// Empty generator stubs for demo
void generator_startup_sequence(void) {}
void generator_stop(void) {}

int main(void)
{
    HAL_Init();                 // Initialize HAL
    SystemClock_Config();       // Configure system clock
    MX_GPIO_Init();             // Initialize GPIO (ADC pin)
    MX_ADC1_Init();             // Initialize ADC
    display_init();             // Initialize 7-segment display

    while (1)
    {
        // Read RMS voltage from ZMPT101B
        float voltage = Read_Voltage_RMS();

        // Update 7-segment display
        display_voltage(voltage);

        // Also print to console via UART if needed
        printf("Voltage RMS: %.1f V\r\n", voltage);

        HAL_Delay(500);  // 0.5s delay between readings
    }
}

// Compute RMS voltage from ADC samples
float Read_Voltage_RMS(void)
{
    const uint16_t samples = 200;
    const float ADC_MID = 2048.0f; // 12-bit ADC midpoint for single-ended input
    uint32_t sum_sq = 0;

    for (uint16_t i = 0; i < samples; i++)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
        uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
        HAL_ADC_Stop(&hadc1);

        float centered = (float)adc_val - ADC_MID;  // Remove DC offset
        sum_sq += centered * centered;
    }

    float adc_rms = sqrtf((float)sum_sq / samples);

    // Convert ADC units to voltage
    float sensor_voltage = (adc_rms / ADC_MID) * 1.65f;  // 3.3V ref
    float voltage_rms = sensor_voltage * 100.0f;         // Calibration factor

    return voltage_rms;
}

// GPIO init for ADC pin only
void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;      // ADC input pin PA5 (IN5)
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// ADC1 init
void MX_ADC1_Init(void)
{
    __HAL_RCC_ADC1_CLK_ENABLE();
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc1.Init.OversamplingMode = DISABLE;
    HAL_ADC_Init(&hadc1);

    sConfig.Channel = ADC_CHANNEL_5;   // PA5
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

// System clock (CubeMX generated)
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 10;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_
