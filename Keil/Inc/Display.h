// display.h - Header for HT16K33 4-digit 7-segment display
#ifndef DISPLAY_H
#define DISPLAY_H

int init_display(void);
int display_voltage(float voltage);
int shutdown_display(void);
void test_display(void);

#endif
