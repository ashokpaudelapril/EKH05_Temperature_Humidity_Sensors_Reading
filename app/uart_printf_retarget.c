#include <stdio.h>

#include "main.h"

extern UART_HandleTypeDef hlpuart1;

int __io_putchar(int ch)
{
    uint8_t c = (uint8_t)ch;
    (void)HAL_UART_Transmit(&hlpuart1, &c, 1, HAL_MAX_DELAY);
    return ch;
}
