# SHT4x Driver Folder

This folder contains the Sensirion SHT4x temperature and humidity driver files used by the EKH05 starter project.

## What This Code Does

These sources handle the low-level sensor communication over I2C and expose helper functions that the application layer can call to retrieve readings.

## Key Files

- [sht4x_i2c.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sht4x_i2c.c): sensor-specific command and conversion logic
- [sht4x_i2c.h](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sht4x_i2c.h): public SHT4x interface
- [sensirion_i2c.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sensirion_i2c.c): shared I2C helper functions
- [sensirion_i2c_hal.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sensirion_i2c_hal.c): STM32 HAL adaptation layer
- [sensirion_config.h](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sensirion_config.h): local configuration hooks
- [sensirion_common.c](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/sht4x/sensirion_common.c): shared utility helpers

## When To Start Here

Start in this folder when you want to:

- port the SHT4x driver into another firmware project
- inspect the I2C read/write path
- adjust the sensor HAL integration

## Related Docs

- [../README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/README.md)
- [../app/README.md](/Users/ashokpaudelapril/1.7.4_Wifi_Halow/EKH05_Temperature_Humidity_Sensors_Reading/app/README.md)
