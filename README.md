# STM32 ↔ ESP32 Wireless Communication using NRF24L01

This project demonstrates wireless TX-RX communication between an STM32 Nucleo-F446RE board and an ESP32 using the NRF24L01 2.4GHz transceiver module.

The STM32 acts as the transmitter (TX) and the ESP32 acts as the receiver (RX).

---

# Hardware Used

- STM32 Nucleo-F446RE
- ESP32 Development Board
- NRF24L01+ Transceiver Modules
- Jumper Wires
- 10µF Capacitor (recommended for NRF24 stability)

---

# Project Structure

```text
STM32-ESP32-NRF24L01-SPI-Wireless-Interface/
│
├── STM32_TX/
│   └── STM32CubeIDE project files
│
├── ESP32_RX/
│   └── PlatformIO / Arduino code
│
└── README.md

# NRF24L01 Pin Mapping

| NRF24L01 Pin | STM32 Nucleo-F446RE | Arduino Header | ESP32 |
|---|---|---|---|
| CE | PB0 | A3 | GPIO4 |
| CSN | PA4 | A2 | GPIO5 |
| SCK | PA5 | D13 | GPIO18 |
| MISO | PA6 | D12 | GPIO19 |
| MOSI | PA7 | D11 | GPIO23 |
| VCC | 3.3V | 3V3 | 3.3V |
| GND | GND | GND | GND |

# STM32CubeMX (.ioc) Configuration

## SPI1 Configuration

Configure SPI1 in STM32CubeMX with the following settings:

| Parameter | Value |
|---|---|
| Mode | Full Duplex Master |
| Direction | 2 Lines |
| Data Size | 8 Bits |
| Clock Polarity (CPOL) | LOW |
| Clock Phase (CPHA) | 1 EDGE |
| NSS | Software |
| First Bit | MSB First |
| Baud Rate Prescaler | 64 or 128 |
| CRC Calculation | Disabled |
| TI Mode | Disabled |


## Example Sample Output 
### STM32 
```
TX val = 0
``` 
Denoting the SPI connection is established between the STM32 and NRF module 
### ESP32
```
Received: From STM32
```
