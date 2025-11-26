#include "display.h"

// External I2C handle
extern I2C_HandleTypeDef hi2c1;

#define DISPLAY_ADDR (0x70 << 1)

static const uint8_t digits[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
#define SEG_E 0x79
#define SEG_r 0x50

static uint8_t buffer[16];

int init_display(void)
{
    HAL_Delay(50);
    uint8_t cmd = 0x21;
    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, &cmd, 1, HAL_MAX_DELAY);
    cmd = 0x81;
    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, &cmd, 1, HAL_MAX_DELAY);
    cmd = 0xEF;
    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, &cmd, 1, HAL_MAX_DELAY);

    for(int i=0;i<16;i++) buffer[i]=0;
    HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, buffer, 16, HAL_MAX_DELAY);

    return 0;
}

int display_voltage(float voltage)
{
    for(int i=0;i<16;i++) buffer[i]=0;

    if(voltage>150.0f)
    {
        buffer[0]=SEG_E; buffer[2]=SEG_r; buffer[4]=SEG_r;
        return HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, buffer, 16, HAL_MAX_DELAY);
    }

    int val = (int)voltage;
    int d1 = val/100; int d2=(val/10)%10; int d3=val%10;
    if(val<100)d1=-1; if(val<10)d2=-1;

    if(d1>=0) buffer[0]=digits[d1];
    if(d2>=0) buffer[2]=digits[d2];
    buffer[4]=digits[d3];

    return HAL_I2C_Master_Transmit(&hi2c1, DISPLAY_ADDR, buffer, 16, HAL_MAX_DELAY);
}
