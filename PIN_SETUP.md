# Board2 Gateway Pin Setup (Simple)

## What this board does
- Receive Wi-Fi HaLow data
- Parse/process payloads
- Print logs on UART

## 1. Enable List (Quick)
- LPUART1
- SPI2
- EXTI for PA1, PB5, PB15

Optional:
- I2C1 fallback sensor
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

### Optional I2C1 fallback
- Enable only if you want local sensor fallback
- PB8: I2C1_SCL
- PB9: I2C1_SDA

## 3. Pin Map (Reference)

### Debug
- PA13 -> SWDIO
- PA14 -> SWCLK

### UART (logs)
- PC1 -> LPUART1_TX
- PC0 -> LPUART1_RX

### HaLow (SPI2)
- PD1 -> SPI2_SCK
- PD3 -> SPI2_MISO
- PD4 -> SPI2_MOSI
- PB4 -> GPIO Output (SPI_CS)
- PA15 -> GPIO Output (BRNG_CS)
- PB5 -> EXTI Rising (BUSY), Pull-down
- PB15 -> EXTI Falling (SPI_IRQ)
- PA1 -> EXTI (BRNG_SPI_IRQ)

### Optional local sensor fallback
- PB8 -> I2C1_SCL
- PB9 -> I2C1_SDA

## 4. Super Simple Order In CubeMX
1. Configure SWD and LPUART1 first
2. Configure SPI2 and CS pins
3. Configure EXTI pins (PA1/PB5/PB15)
4. Optional: add I2C1 fallback sensor
5. Generate code and build

## 5. Enable List (Recheck)
- LPUART1 enabled
- SPI2 enabled
- EXTI enabled for PA1, PB5, PB15

Optional recheck:
- I2C1 enabled (if fallback used)
- SPI2 DMA RX/TX enabled (only if required)

## 6. Done Check
- No red pin conflicts in CubeMX
- UART logs print
- SPI2 init succeeds
- EXTI lines are enabled

## Reference
- HaLow baseline pin style: [HaLow_example_spi/HaLow_example_spi.ioc](../../HaLow_example_spi/HaLow_example_spi.ioc)
