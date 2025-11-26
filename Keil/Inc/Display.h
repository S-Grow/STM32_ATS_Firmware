#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32l4xx_hal.h"

int init_display(void);
int display_voltage(float voltage);
int shutdown_display(void);

#endif /* __DISPLAY_H */
