#include <Arduino.h>
#include <HardwareSerial.h>

constexpr int PIN_ELBOW_UP =   17;
constexpr int PIN_ELBOW_DOWN = 16;

HardwareSerial SerialPort2 (2);

std::string incomingData = "";
int incomingDataLength = 0;
bool serialLineStarted = false;

void setup()
{
    Serial.begin(115200);

    pinMode(PIN_ELBOW_UP, OUTPUT);
    pinMode(PIN_ELBOW_DOWN, OUTPUT);

    digitalWrite(PIN_ELBOW_UP, LOW);
    digitalWrite(PIN_ELBOW_DOWN, LOW);

    SerialPort2.begin(9600, SERIAL_8N1, 5, 4);
}

void moveElbowUp();
void moveElbowDown();
void stopElbow();

void loop()
{
    if (SerialPort2.available())
    {
        const char incomingChar = static_cast<char>(SerialPort2.read());

        if (incomingChar == '\n') serialLineStarted = true;

        if (serialLineStarted &&
            incomingChar != '\n')
        {
            incomingData += incomingChar;
            incomingDataLength++;
        }
    }

    if (incomingDataLength > 9)
    {
        serialLineStarted = false;
        incomingDataLength = 0;

        Serial.print("incoming line was: ");
        Serial.println(incomingData.c_str());

        // Left stick
        if (incomingData[0] == '1')
        {
            Serial.println("Left stick move: UP!");
        }

        if (incomingData[1] == '1')
        {
            Serial.println("Left stick move: RIGHT!");
        }

        if (incomingData[2] == '1')
        {
            Serial.println("Left stick move: DOWN!");
        }

        if (incomingData[3] == '1')
        {
            Serial.println("Left stick move: LEFT!");
        }

        if (incomingData[4] == '1')
        {
            Serial.println("Left stick: BUTTON!");
        }

        // Right stick
        if (incomingData[5] == '1')
        {
            Serial.println("Right stick move: UP!");
        }

        if (incomingData[6] == '1')
        {
            Serial.println("Right stick move: RIGHT!");
        }

        if (incomingData[7] == '1')
        {
            Serial.println("Right stick move: DOWN!");
        }

        if (incomingData[8] == '1')
        {
            Serial.println("Right stick move: LEFT!");
        }

        if (incomingData[9] == '1')
        {
            Serial.println("Right stick: BUTTON!");
        }

        if (incomingData[0] == '0' &&
            incomingData[1] == '0' &&
            incomingData[2] == '0' &&
            incomingData[3] == '0' &&
            incomingData[4] == '0' &&
            incomingData[5] == '0' &&
            incomingData[6] == '0' &&
            incomingData[7] == '0' &&
            incomingData[8] == '0' &&
            incomingData[9] == '0')
        {
            Serial.println("Elbow STOP!");
            stopElbow();
        }

        incomingData = "";
    }
}

void moveElbowUp()
{
    digitalWrite(PIN_ELBOW_UP, HIGH);
}

void moveElbowDown()
{
    digitalWrite(PIN_ELBOW_DOWN, HIGH);
}

void stopElbow()
{
    digitalWrite(PIN_ELBOW_DOWN, LOW);
    digitalWrite(PIN_ELBOW_UP, LOW);
}