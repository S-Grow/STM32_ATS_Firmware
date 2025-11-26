#include "main.h"
#include "Display.h"

int main(void) {
    System_Clock_Init();

    // Enable GPIO clocks
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

    // Configure LED
    GPIOA->MODER &= ~(3UL<<(LED_PIN*2));
    GPIOA->MODER |= 1UL<<(LED_PIN*2);

    // Configure button
    GPIOC->MODER &= ~(3UL<<BUTTON_PIN*2);
    GPIOC->PUPDR |= 1UL<<(BUTTON_PIN*2);

    // Initialize I2C display
    init_display();

    int flash = 0;

    while(1) {
        if((GPIOC->IDR & (1UL<<BUTTON_PIN)) == 0) {
            flash = !flash;

            // Toggle display all segments
            if(flash) test_display();
            else init_display(); // clear display

            while((GPIOC->IDR & (1UL<<BUTTON_PIN)) == 0); // debounce
        }
        if(flash) GPIOA->ODR ^= (1UL<<LED_PIN); // blink LED

        for(volatile int i=0;i<LED_BLINK_DELAY;i++);
    }
}
