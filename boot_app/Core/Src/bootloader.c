

#include "bootloader.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define APP_ADDRESS 0x08004000

void jump_to_app(void)
{
    uint32_t appStack = *(volatile uint32_t*)APP_ADDRESS;
    uint32_t appReset = *(volatile uint32_t*)(APP_ADDRESS + 4);

    // Disable interrupts
    __disable_irq();


    // Set MSP
    __set_MSP(appStack);
    SCB->VTOR = APP_ADDRESS;
    // Jump
    void (*app_entry)(void) = (void*)(appReset | 1);
    app_entry();
}
