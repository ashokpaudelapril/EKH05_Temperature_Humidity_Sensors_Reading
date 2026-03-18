/*
 * Drop-in snippet for STM32CubeIDE projects.
 * Requires:
 *   - I2C1 initialized (MX_I2C1_Init)
 *   - demo_temperature.c/.h and sht4x sources added to project
 */

#include <stdio.h>
#include "main.h"
#include "demo_temperature.h"

void app_temperature_loop(void)
{
    temperature_init();

    while (1)
    {
        th_value_t th;

        temperature_process();
        th = get_th_values();

        printf("Temp: %.3f C, Humidity: %.3f %%RH\r\n",
               th.temperature_milli_degC / 1000.0f,
               th.humidity_milli_RH / 1000.0f);

        HAL_Delay(1000);
    }
}
