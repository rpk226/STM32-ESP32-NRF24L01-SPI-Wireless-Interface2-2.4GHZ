# STM32 ↔ ESP32 Wireless Communication using NRF24L01

This project demonstrates wireless TX-RX communication between an STM32 Nucleo-F446RE board and an ESP32 using the NRF24L01 2.4GHz transceiver module.

- STM32 Nucleo-F446RE acts as the **Transmitter (TX)**
- ESP32 acts as the **Receiver (RX)**

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
│   └── PlatformIO / Arduino source files
│
└── README.md
```

---

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

---

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

---

## GPIO Configuration

| STM32 Pin | Configuration | Purpose |
|---|---|---|
| PB0 | GPIO_Output | NRF24 CE |
| PA4 | GPIO_Output | NRF24 CSN |
| PA5 | SPI1_SCK | NRF24 SCK |
| PA6 | SPI1_MISO | NRF24 MISO |
| PA7 | SPI1_MOSI | NRF24 MOSI |

---

# NRF24 Configuration

| Parameter | Value |
|---|---|
| Channel | 100 |
| Data Rate | 1 Mbps |
| Payload Size | 32 Bytes |
| Address Width | 5 Bytes |
| CRC | Enabled |
| Auto ACK | Disabled |

---

## Example Output

### STM32 TX
TX status: 0 

### ESP32 RX
```
RX: 0
RX: 1
```
### Packet Loss & Link Monitoring
```
RX: 10
RX: 11
❌ Packet lost! Expected: 12 Got: 13
⚠️ No packets received!
``` 

Indicates successful transmission and reception of packets, along with real-time detection of packet

# Notes

- CE must be pulsed HIGH briefly during transmission.
- Use a 10µF capacitor across NRF24 VCC and GND for stable operation.
- Both TX and RX must use:
  - same channel
  - same address
  - same data rate
  - same CRC settings

---


# References

This project uses the following NRF24L01 STM32 HAL library as a reference:

- [HardwareLevel STM32 HAL NRF24 Library](https://github.com/HardwareLevel/stm32_hal_nrf24_library/tree/main)

The library provides:
- NRF24L01 SPI communication using STM32 HAL
- TX/RX packet handling
- CRC configuration
- Dynamic payload support
- Auto acknowledgment support
- Pipe and channel configuration
