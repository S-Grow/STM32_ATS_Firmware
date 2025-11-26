#include "Display.h"
#include "stm32l4xx_hal.h"

// HT16K33 buffer
static uint8_t buffer[16] = {0};

int init_display(void) {
    // Enable GPIOB clock (already in main, but safe)
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    // HT16K33 commands: oscillator on, display on, max brightness
    uint8_t cmd;
    cmd = 0x21; HAL_I2C_Master_Transmit(&I2C_INSTANCE, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);
    cmd = 0x81; HAL_I2C_Master_Transmit(&I2C_INSTANCE, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);
    cmd = 0xEF; HAL_I2C_Master_Transmit(&I2C_INSTANCE, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);

    // Clear buffer
    for(int i=0;i<16;i++) buffer[i]=0;
    HAL_I2C_Master_Transmit(&I2C_INSTANCE, HT16K33_ADDR, buffer, 16, HAL_MAX_DELAY);

    return 0;
}

int test_display(void) {
    // Turn all segments on
    for(int i=0;i<16;i++) buffer[i]=0xFF;
    return HAL_I2C_Master_Transmit(&I2C_INSTANCE, HT16K33_ADDR, buffer, 16, HAL_MAX_DELAY);
}
