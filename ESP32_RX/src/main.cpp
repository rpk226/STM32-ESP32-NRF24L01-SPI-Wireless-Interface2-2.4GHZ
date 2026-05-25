#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

RF24 radio(4, 5);  // CE, CSN

//const byte address[6] = "00001";
//byte address[5] = {0x45, 0x55, 0x67, 0x10, 0x21};

byte address[6] = "RxAAA";
void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println("Starting RX...");

    if (!radio.begin()) {
        Serial.println("❌ Radio not responding!");
        while (1);
    }

    // MUST match transmitter
radio.begin();

radio.setChannel(100);

radio.setDataRate(RF24_1MBPS);

radio.setPALevel(RF24_PA_LOW);

radio.disableCRC();

//radio.setCRCLength(RF24_CRC_8);

radio.setPayloadSize(32);

radio.setAutoAck(false);

radio.openReadingPipe(0, address);

radio.startListening();

Serial.println("Listening on channel 100...");
Serial.println(radio.isChipConnected());
}

void loop()
{
    if (radio.available())
    {
        uint8_t buffer[32] = {0};

        radio.read(buffer, 32);

        Serial.print("Received: ");

        /*for(int i=0;i<32;i++)
        {
            Serial.print((char)buffer[i]);
        }
        */
        Serial.println((char*)buffer);
    }

    else
    {
        Serial.println("No packet");

        delay(1000);
    }
}