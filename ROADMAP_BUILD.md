# Board1 (SensorNode) Build System Integration Steps

## 1. Add FreeRTOS and CMSIS-OS2
- Add to `HeaderPath` in .mxproject:
  - `Middlewares\Third_Party\FreeRTOS\Source\include`
  - `Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM33_NTZ\non_secure`
  - `Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2`
  - `Drivers\CMSIS\RTOS2\Include`
- Add to `SourceFiles` in .mxproject:
  - `Middlewares\Third_Party\FreeRTOS\Source\croutine.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\event_groups.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\list.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\queue.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\stream_buffer.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\tasks.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\timers.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM33_NTZ\non_secure\port.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM33_NTZ\non_secure\portasm.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2\cmsis_os2.c`
  - `Middlewares\Third_Party\FreeRTOS\Source\portable\MemMang\heap_4.c`

## 2. Add MorseMicro Middleware and lwIP
- Add to `HeaderPath` in .mxproject:
  - `Middlewares\Third_Party\MorseMicro_MM_IoT_MM_IoT\morselib\MM6108\with_wpa_supplicant\include`
  - `Middlewares\Third_Party\MorseMicro_MM_IoT_MM_IoT\mmLwIP\src\include`
  - `Middlewares\Third_Party\MorseMicro_MM_IoT_MM_IoT\mmLwIP\port`
  - `Middlewares\Third_Party\MorseMicro_MM_IoT_MM_IoT\mmipal\lwip`
- Add to `SourceFiles` in .mxproject (see HaLow_example_spi for full list):
  - All MorseMicro and lwIP .c files used in the example (e.g., mmosal_shim_freertos.c, mmnetif.c, mmipal_lwip.c, etc.)

## 3. Update Build Defines
- Add/verify:
  - `USE_HAL_DRIVER`
  - `STM32U585xx`

## 4. Validate
- Clean and rebuild the project.
- Ensure all new includes and sources are recognized.
- Resolve any missing file or path errors.

---

**Tip:** Use the HaLow_example_spi .mxproject as a reference for all middleware and RTOS integration details.
