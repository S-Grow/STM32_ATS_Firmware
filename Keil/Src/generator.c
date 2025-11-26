#include "generator.h"
#include "main.h"

GPIO_TypeDef* GEN_PORT = GPIOA;
uint16_t GEN_CHOKE_PIN = GPIO_PIN_4;
uint16_t GEN_START_PIN = GPIO_PIN_3;
uint16_t GEN_RUN_PIN = GPIO_PIN_5;

void generator_startup_sequence(void)
{
    HAL_GPIO_WritePin(GEN_PORT, GEN_CHOKE_PIN, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(GEN_PORT, GEN_CHOKE_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GEN_PORT, GEN_START_PIN, GPIO_PIN_SET);
    HAL_Delay(200);
    HAL_GPIO_WritePin(GEN_PORT, GEN_START_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GEN_PORT, GEN_RUN_PIN, GPIO_PIN_SET);
}

void generator_stop(void)
{
    HAL_GPIO_WritePin(GEN_PORT, GEN_RUN_PIN, GPIO_PIN_RESET);
}
