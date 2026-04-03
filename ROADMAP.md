# Board2 (Gateway) Development ROADMAP

## 1. Project Foundation & Environment
- [ ] Set up STM32CubeIDE or your preferred toolchain.
- [ ] Clone/copy the MorseMicro MM_IoT SDK and dashboard project.
- [ ] Verify hardware connections: EKH05 board, HaLow module, host interface (USB/UART/Ethernet).

## 2. Middleware & RTOS Integration
- [ ] Add MorseMicro middleware (morselib, mmipal, mmwlan) to the project.
- [ ] Integrate FreeRTOS and CMSIS-OS2 (add sources, include paths).
- [ ] Integrate lwIP stack for UDP/TCP networking.
- [ ] Update build system (makefile, .mxproject, IDE settings) to include all new sources and headers.

## 3. Board Initialization
- [ ] Refactor main.c to use RTOS startup (mmosal_main, app_init).
- [ ] Initialize all peripherals (SPI, UART, GPIO) in main.c.
- [ ] Add error handling and diagnostics for hardware init.

## 4. HaLow Stack Bring-up
- [ ] Initialize MorseMicro HaLow stack (mmwlan, mmipal).
- [ ] Configure and start HaLow interface (SPI, firmware load, etc.).
- [ ] Set up as HaLow AP or join as STA as required.
- [ ] Obtain IP address via DHCP or static config.

## 5. Application Layer
- [ ] Refactor app layer to use RTOS tasks (UDP receive, data forward).
- [ ] Implement UDP receive task using lwIP sockets.
- [ ] Parse and validate incoming sensor data.
- [ ] Forward data to host (USB, UART, Ethernet, or cloud).
- [ ] Add compile-time switch for UART fallback (for bring-up/debug).

## 6. Diagnostics & Logging
- [ ] Add UART/ITM logging for debugging.
- [ ] Implement error/status reporting (LEDs, serial, etc.).
- [ ] Add runtime diagnostics for HaLow link, IP, and data status.

## 7. Testing & Validation
- [ ] Test UDP reception from SensorNode.
- [ ] Validate data forwarding to host/cloud.
- [ ] Test fallback to UART if HaLow is unavailable.
- [ ] Perform range, throughput, and robustness testing.

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
