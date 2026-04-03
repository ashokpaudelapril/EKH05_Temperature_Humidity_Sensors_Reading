# EKH05 Temperature Only Starter

This folder contains the minimum SHT4x temperature/humidity sources extracted from `Own Project`.

## Folder Contents

- `app/demo_temperature.c`
- `app/demo_temperature.h`
- `sht4x/*` (Sensirion SHT4x driver and I2C helpers)
- `app/main_temp_snippet.c` (example usage for printing)

Folder notes:

- [app/README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/README.md)
- [sht4x/README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/README.md)

## How To Use In A New STM32CubeIDE Project

1. Create a new STM32U585 project (or duplicate your existing EKH05 project).
2. Enable `I2C1` in the `.ioc` (EKH05 uses PB8/PB9 for SHT4x).
3. Ensure `stdio` output is configured (UART/ITM) so `printf` works.
4. Copy `app/demo_temperature.c` and `app/demo_temperature.h` into your project sources/includes.
5. Copy all files from `sht4x/` into your project.
6. Add include paths for `app` and `sht4x`.
7. Call `temperature_init()` once after HAL peripheral init.
8. Call `temperature_process()` periodically, then print `get_th_values()`.

## If LPUART1 Is Enabled (Recommended)

After code generation, add these files to your project:

- `app/temp_app.c`
- `app/temp_app.h`
- `app/uart_printf_retarget.c`
- `app/demo_temperature.c`
- `app/demo_temperature.h`
- all files from `sht4x/`

Then edit generated `Core/Src/main.c`:

1. Add include:

```c
#include "temp_app.h"
```

2. After `MX_LPUART1_UART_Init();` and `MX_I2C1_Init();`, call:

```c
temp_app_run_forever();
```

This function does:

- sensor init once
- reads every second
- prints `Temp` and `Humidity` via LPUART1

## Notes

- The copied files were adjusted to use `HAL_Delay()` (no `mmosal` dependency).
- Temperature unit is milli-degC. Example: `25340` means `25.340 C`.
- Humidity unit is milli-%RH. Example: `48210` means `48.210 %RH`.
