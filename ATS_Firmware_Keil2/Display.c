#include "Display.h"

// HT16K33 buffer
static uint8_t buffer[16] = {0};

int init_display(void) {
    uint8_t cmd;

    // Turn on oscillator
    cmd = 0x21;
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);

    // Display on, blinking off
    cmd = 0x81;
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);

    // Max brightness
    cmd = 0xEF;
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDR, &cmd, 1, HAL_MAX_DELAY);

    // Clear buffer
    for (int i = 0; i < 16; i++) buffer[i] = 0;
    HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDR, buffer, 16, HAL_MAX_DELAY);

    return 0;
}

int test_display(void) {
    // Turn all segments on
    for (int i = 0; i < 16; i++) buffer[i] = 0xFF;
    return HAL_I2C_Master_Transmit(&hi2c1, HT16K33_ADDR, buffer, 16, HAL_MAX_DELAY);
}
