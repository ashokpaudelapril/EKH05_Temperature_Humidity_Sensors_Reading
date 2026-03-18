#include "temp_app.h"

#include <stdio.h>

#include "demo_temperature.h"

void temp_app_run_forever(void)
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
