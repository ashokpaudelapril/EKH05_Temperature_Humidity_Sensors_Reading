# App Folder

This folder contains the small application layer used by the EKH05 temperature and humidity starter project.

## What This Code Does

The files here sit above the raw SHT4x driver and provide the polling, formatting, and simple example runtime used by the starter project.

## Key Files

- [demo_temperature.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/demo_temperature.c): sensor-facing application helpers
- [demo_temperature.h](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/demo_temperature.h): public interface for the temperature helper
- [temp_app.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/temp_app.c): simple forever-loop application wrapper
- [temp_app.h](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/temp_app.h): public interface for the app wrapper
- [uart_printf_retarget.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/uart_printf_retarget.c): `printf` retarget support for UART output
- [main_temp_snippet.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/main_temp_snippet.c): example integration snippet for generated `main.c`

## When To Start Here

Start in this folder when you want to:

- understand the minimal polling flow
- reuse the ready-made demo loop in another CubeIDE project
- connect UART logging to a simple sensor readout

## Related Docs

- [../README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/README.md)
- [../sht4x/README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/README.md)
