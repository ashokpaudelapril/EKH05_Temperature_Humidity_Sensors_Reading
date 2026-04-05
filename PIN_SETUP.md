# Board1 Sensor Node Pin Setup (Simple)

## What this board does
- Read SHT4x sensor
- Send data over Wi-Fi HaLow
- Print logs on UART

## 1. Enable List (Quick)
- LPUART1
- I2C1
- SPI2
- EXTI for PA1, PB5, PB15

Optional:
- SPI2 DMA RX/TX (enable only if Morse stack asks for it)

## 2. Set Up Each Enabled Item

### LPUART1
- Mode: Asynchronous
- Direction: TX/RX
- Baud rate: 115200
- Word length: 8 Bits
- Parity: None
- Stop bits: 1
- Hardware flow control: None

### I2C1
- Mode: I2C
- Addressing: 7-bit
- Keep default timing first, tune later only if needed

### SPI2
- Mode: Full-Duplex Master
- NSS: Software (CS handled by GPIO)
- Data size: 8-bit
- Keep default SPI timing first, tune later only if needed

### EXTI
- PB5: EXTI, Rising edge, Pull-down
- PB15: EXTI, Falling edge
- PA1: EXTI enabled

### NVIC
- SPI2 global interrupt: Enabled
- EXTI interrupts for PA1/PB5/PB15: Enabled
- SysTick: Enabled

## 3. Pin Map (Reference)

### Debug
- PA13 -> SWDIO
- PA14 -> SWCLK

### UART (logs)
- PC1 -> LPUART1_TX
- PC0 -> LPUART1_RX

### Sensor (I2C1)
- PB8 -> I2C1_SCL
- PB9 -> I2C1_SDA

### HaLow (SPI2)
- PD1 -> SPI2_SCK
- PD3 -> SPI2_MISO
- PD4 -> SPI2_MOSI
- PB4 -> GPIO Output (SPI_CS)
- PA15 -> GPIO Output (BRNG_CS)
- PB5 -> EXTI Rising (BUSY), Pull-down
- PB15 -> EXTI Falling (SPI_IRQ)
- PA1 -> EXTI (BRNG_SPI_IRQ)

## 4. Super Simple Order In CubeMX
1. Configure SWD and LPUART1 first
2. Configure I2C1 (PB8/PB9)
3. Configure SPI2 and CS pins
4. Configure EXTI pins (PA1/PB5/PB15)
5. Generate code and build

## 5. Enable List (Recheck)
- LPUART1 enabled
- I2C1 enabled
- SPI2 enabled
- EXTI enabled for PA1, PB5, PB15

Optional recheck:
- SPI2 DMA RX/TX enabled (only if required)

## 6. Done Check
- No red pin conflicts in CubeMX
- UART logs print
- Sensor read works
- SPI2 init succeeds

## Reference
- HaLow baseline pin style: [HaLow_example_spi/HaLow_example_spi.ioc](../../HaLow_example_spi/HaLow_example_spi.ioc)
