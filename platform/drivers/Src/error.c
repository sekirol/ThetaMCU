#include "error.h"
#include "stm32wbxx_hal.h"

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}