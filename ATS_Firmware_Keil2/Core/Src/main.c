#include "main.h"
#include "Display.h"

#define LED_BLINK_DELAY 500000

int main(void)
{
    // Initialize HAL Library
    HAL_Init();

    // Configure the system clock
    SystemClock_Config();

    // Initialize all configured peripherals (GPIO, I2C, ADC, etc.)
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_ADC1_Init();

    // Initialize the display
    init_display();

    // LED state
    uint8_t flash = 0;

    while(1)
    {
        // Check if button is pressed
        if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
        {
            flash = !flash;

            // Toggle display
            if(flash)
            {
                test_display();   // All segments ON
            }
            else
            {
                init_display();   // Clear display
            }

            // Wait until button released (simple debounce)
            while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET);
        }

        // Blink LED if flash is on
        if(flash)
        {
            HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        }

        // Simple software delay
        for(volatile uint32_t i = 0; i < LED_BLINK_DELAY; i++);
    }
}
