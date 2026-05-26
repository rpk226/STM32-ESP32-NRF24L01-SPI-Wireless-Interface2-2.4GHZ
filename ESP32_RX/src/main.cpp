#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

// RX module
RF24 radioRX(4, 5);

// TX module (interferer)
RF24 radioTX(16, 17);

uint32_t last = 0;
bool first_packet = true;

unsigned long lastReceiveTime = 0;
const unsigned long timeout = 5000;  // 1 second timeout

/*

byte address[6] = "RxAAA";

void setup() {
    Serial.begin(115200);
    delay(2000);

// Configure CSN pins
    pinMode(5, OUTPUT);
    pinMode(17, OUTPUT);

    digitalWrite(5, HIGH);
    digitalWrite(17, HIGH);

    Serial.println("Starting RX + TX...");

    // 🔵 INIT RX
    digitalWrite(5, LOW);
    digitalWrite(17, HIGH);

    if (!radioRX.begin()) {
        Serial.println("❌ RX radio failed!");
        while (1);
    }


    Serial.println("✅ RX initialized");
    radioRX.begin();

    radioRX.setChannel(100);

    radioRX.setDataRate(RF24_1MBPS);

    radioRX.setPALevel(RF24_PA_LOW);

    radioRX.disableCRC();

    //radio.setCRCLength(RF24_CRC_8);

    radioRX.setPayloadSize(32);

    radioRX.setAutoAck(false);

    radioRX.openReadingPipe(0, address);

    radioRX.startListening();

    Serial.println("Listening on channel 100...");
    Serial.println(radioRX.isChipConnected());


    // 🔴 INIT TX
    digitalWrite(5, HIGH);
    digitalWrite(17, LOW);

    if (!radioTX.begin()) {
        Serial.println("❌ TX radio failed!");
        while (1);
    }

    Serial.println("✅ TX initialized");

    // Release both
    digitalWrite(5, HIGH);
    digitalWrite(17, HIGH);

    radioTX.setChannel(100);              // SAME CHANNEL → strong interference
    radioTX.setDataRate(RF24_1MBPS);
    radioTX.setPALevel(RF24_PA_MAX);

    radioTX.stopListening();

    Serial.println("Interference TX started");
}

void loop()
{
    //  RECEIVE DATA
    if (radioRX.available())
    {
        uint8_t buffer[32] = {0};

        radioRX.read(buffer, 32);

        Serial.print("RX: ");
        for (int i = 0; i < 8; i++) {
            Serial.print(buffer[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

    // GENERATE INTERFERENCE
    uint8_t noise[32];

    for (int i = 0; i < 32; i++) {
        noise[i] = random(0, 255);
    }

    radioTX.write(&noise, sizeof(noise));

    delayMicroseconds(500);
}

*/




byte address[6] = "RxAAA";
void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println("Starting RX...");

    if (!radioRX.begin()) {
        Serial.println("❌ Radio not responding!");
        while (1);
    }

    // MUST match transmitter
radioRX.begin();

radioRX.setChannel(100);

radioRX.setDataRate(RF24_1MBPS);

radioRX.setPALevel(RF24_PA_LOW);

radioRX.disableCRC();

//radio.setCRCLength(RF24_CRC_8);

radioRX.setPayloadSize(32);

radioRX.setAutoAck(false);

radioRX.openReadingPipe(0, address);

radioRX.startListening();

Serial.println("Listening on channel 100...");
Serial.println(radioRX.isChipConnected());
}


void loop()
{
    if (radioRX.available())
    {
        uint8_t buffer[32] = {0};

        radioRX.read(buffer, 32);

        // Convert string → number
        uint32_t current = atoi((char*)buffer);

        Serial.print("RX: ");
        Serial.println(current);

        // Packet loss detection
        if (!first_packet)
        {
            if (current != last + 1)
            {
                Serial.print("❌ Packet lost! Expected: ");
                Serial.print(last + 1);
                Serial.print(" Got: ");
                Serial.println(current);
            }
        }
        else
        {
            first_packet = false;
        }

        last = current;
    }

    // 🔴 NO PACKET RECEIVED (timeout detection)
    if (millis() - lastReceiveTime > timeout)
    {
        Serial.println("⚠️ No packets received!");

        // Reset timer to avoid continuous spam
        lastReceiveTime = millis();
    }
}
