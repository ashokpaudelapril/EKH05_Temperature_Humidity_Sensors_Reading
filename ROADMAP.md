# Board1 (SensorNode) Development ROADMAP

## 1. Project Foundation & Environment
- [ ] Set up STM32CubeIDE or your preferred toolchain.
- [ ] Clone/copy the MorseMicro MM_IoT SDK and dashboard project.
- [ ] Verify hardware connections: EKH05 board, sensors, HaLow module.
- [ ] Confirm UART, SPI, I2C, and GPIO pin mappings.

## 2. Middleware & RTOS Integration
- [ ] Add MorseMicro middleware (morselib, mmipal, mmwlan) to the project.
- [ ] Integrate FreeRTOS and CMSIS-OS2 (add sources, include paths).
- [ ] Integrate lwIP stack for UDP/TCP networking.
- [ ] Update build system (makefile, .mxproject, IDE settings) to include all new sources and headers.

## 3. Board Initialization
- [ ] Refactor main.c to use RTOS startup (mmosal_main, app_init).
- [ ] Initialize all peripherals (I2C, SPI, UART, GPIO) in main.c.
- [ ] Add error handling and diagnostics for hardware init.

## 4. HaLow Stack Bring-up
- [ ] Initialize MorseMicro HaLow stack (mmwlan, mmipal).
- [ ] Configure and start HaLow interface (SPI, firmware load, etc.).
- [ ] Join/scan for HaLow network (SSID, security, etc.).
- [ ] Obtain IP address via DHCP or static config.

## 5. Application Layer
- [ ] Refactor app layer to use RTOS tasks (sensor read, data send).
- [ ] Implement sensor polling (e.g., SHT4x temperature/humidity).
- [ ] Format sensor data for transmission (JSON, binary, etc.).
- [ ] Implement UDP send task using lwIP sockets.
- [ ] Add compile-time switch for UART fallback (for bring-up/debug).

## 6. Diagnostics & Logging
- [ ] Add UART/ITM logging for debugging.
- [ ] Implement error/status reporting (LEDs, serial, etc.).
- [ ] Add runtime diagnostics for HaLow link, IP, and sensor status.

## 7. Testing & Validation
- [ ] Test sensor readout and data formatting.
- [ ] Test UDP transmission over HaLow to Gateway.
- [ ] Validate fallback to UART if HaLow is unavailable.
- [ ] Perform power, range, and robustness testing.

## 8. Documentation & Handover
- [ ] Document all hardware connections and configuration.
- [ ] Maintain a README and ROADMAP in the project root.
- [ ] Comment all major code sections and functions.
- [ ] Prepare test reports and known issues list.

---

# General Best Practices

- Use version control (git) for all code and documentation.
- Keep all third-party middleware in versioned subfolders.
- Use compile-time switches for transport selection (HaLow vs UART).
- Regularly update the ROADMAP and README as the project evolves.
- Maintain a changelog and issue tracker.
