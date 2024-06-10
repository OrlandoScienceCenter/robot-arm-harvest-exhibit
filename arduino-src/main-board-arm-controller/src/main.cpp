#include <Arduino.h>
#include <HardwareSerial.h>
#include "../.pio/libdeps/esp32-s3-devkitm-1/elapsedMillis/elapsedMillis.h"

// DO NOT USE GPIO 46 according to safe ESP32-S3 pins chart
constexpr int PIN_ELBOW_UP =                            48;
constexpr int PIN_ELBOW_DOWN =                          36;

constexpr int PIN_SHOULDER_UP =                         47;
constexpr int PIN_SHOULDER_DOWN =                       21;

constexpr int PIN_SHOULDER_ROTATE_CLOCKWISE =           37;
constexpr int PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE =    38;

constexpr int PIN_WRIST_ROTATE_CLOCKWISE =              16;
constexpr int PIN_WRIST_ROTATE_COUNTERCLOCKWISE =       15;

constexpr int PIN_HAND_CLOSE =                          1;
constexpr int PIN_HAND_OPEN =                           2;

HardwareSerial SerialPort2 (2);

std::string incomingData = "";
std::string lastIncomingData = "";


elapsedMillis sinceJoysticksStateChange;

int incomingDataLength = 0;
bool serialLineStarted = false;

void setup()
{
    Serial.begin(115200);

    pinMode(PIN_ELBOW_UP, OUTPUT);
    pinMode(PIN_ELBOW_DOWN, OUTPUT);

    pinMode(PIN_SHOULDER_UP, OUTPUT);
    pinMode(PIN_SHOULDER_DOWN, OUTPUT);

    pinMode(PIN_SHOULDER_ROTATE_CLOCKWISE, OUTPUT);
    pinMode(PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE, OUTPUT);

    pinMode(PIN_WRIST_ROTATE_CLOCKWISE, OUTPUT);
    pinMode(PIN_WRIST_ROTATE_COUNTERCLOCKWISE, OUTPUT);

    pinMode(PIN_HAND_CLOSE, OUTPUT);
    pinMode(PIN_HAND_OPEN, OUTPUT);

    digitalWrite(PIN_ELBOW_UP, LOW);
    digitalWrite(PIN_ELBOW_DOWN, LOW);

    digitalWrite(PIN_SHOULDER_UP, LOW);
    digitalWrite(PIN_SHOULDER_DOWN, LOW);

    digitalWrite(PIN_SHOULDER_ROTATE_CLOCKWISE, LOW);
    digitalWrite(PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE, LOW);

    digitalWrite(PIN_WRIST_ROTATE_CLOCKWISE, LOW);
    digitalWrite(PIN_WRIST_ROTATE_COUNTERCLOCKWISE, LOW);

    digitalWrite(PIN_HAND_CLOSE, LOW);
    digitalWrite(PIN_HAND_OPEN, LOW);

    SerialPort2.begin(9600, SERIAL_8N1, 5, 4);
}

void moveRobotArm();

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

        if (sinceJoysticksStateChange > 400 &&
            incomingData != lastIncomingData)
        {
            sinceJoysticksStateChange = 0;

            moveRobotArm();

            lastIncomingData = incomingData;

            Serial.println("Moving robot arm since delay was elapsed");
        }

        incomingData = "";
    }
}

void moveElbowUp()
{
    digitalWrite(PIN_ELBOW_DOWN, LOW);
    digitalWrite(PIN_ELBOW_UP, HIGH);
    Serial.println("Moving elbow: UP!");
}

void moveElbowDown()
{
    digitalWrite(PIN_ELBOW_UP, LOW);
    digitalWrite(PIN_ELBOW_DOWN, HIGH);
    Serial.println("Moving elbow: DOWN!");
}

void stopElbow()
{
    digitalWrite(PIN_ELBOW_DOWN, LOW);
    digitalWrite(PIN_ELBOW_UP, LOW);
    Serial.println("Elbow: STOP!");
}

void moveShoulderUp()
{
    digitalWrite(PIN_SHOULDER_DOWN, LOW);
    digitalWrite(PIN_SHOULDER_UP, HIGH);
    Serial.println("Moving shoulder: UP!");
}

void moveShoulderDown()
{
    digitalWrite(PIN_SHOULDER_UP, LOW);
    digitalWrite(PIN_SHOULDER_DOWN, HIGH);
    Serial.println("Moving shoulder: DOWN!");
}

void stopShoulderUpDown()
{
    digitalWrite(PIN_SHOULDER_DOWN, LOW);
    digitalWrite(PIN_SHOULDER_UP, LOW);
    Serial.println("Shoulder: STOP!");
}

void openHand()
{
    digitalWrite(PIN_HAND_CLOSE, LOW);
    digitalWrite(PIN_HAND_OPEN, HIGH);
    Serial.println("Moving hand: OPEN!");
}

void closeHand()
{
    digitalWrite(PIN_HAND_OPEN, LOW);
    digitalWrite(PIN_HAND_CLOSE, HIGH);
    Serial.println("Moving hand: CLOSE!");
}

void stopHand()
{
    digitalWrite(PIN_HAND_OPEN, LOW);
    digitalWrite(PIN_HAND_CLOSE, LOW);
    Serial.println("Hand: STOP!");
}

void wristClockwise()
{
    digitalWrite(PIN_WRIST_ROTATE_COUNTERCLOCKWISE, LOW);
    digitalWrite(PIN_WRIST_ROTATE_CLOCKWISE, HIGH);
    Serial.println("Moving hand: OPEN!");
}

void wristCounterclockwise()
{
    digitalWrite(PIN_WRIST_ROTATE_CLOCKWISE, LOW);
    digitalWrite(PIN_WRIST_ROTATE_COUNTERCLOCKWISE, HIGH);
    Serial.println("Moving hand: CLOSE!");
}

void stopWristRotation()
{
    digitalWrite(PIN_WRIST_ROTATE_COUNTERCLOCKWISE, LOW);
    digitalWrite(PIN_WRIST_ROTATE_CLOCKWISE, LOW);
    Serial.println("Hand: STOP!");
}

void shoulderClockwise()
{
    digitalWrite(PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE, LOW);
    digitalWrite(PIN_SHOULDER_ROTATE_CLOCKWISE, HIGH);
    Serial.println("Moving shoulder: CLOCKWISE!");
}

void shoulderCounterclockwise()
{
    digitalWrite(PIN_SHOULDER_ROTATE_CLOCKWISE, LOW);
    digitalWrite(PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE, HIGH);
    Serial.println("Moving shoulder: COUNTERCLOCKWISE!");
}

void shoulderStopRotation()
{
    digitalWrite(PIN_SHOULDER_ROTATE_COUNTERCLOCKWISE, LOW);
    digitalWrite(PIN_SHOULDER_ROTATE_CLOCKWISE, LOW);
    Serial.println("Shoulder: STOP!");
}

void moveRobotArm()
{
    // Left stick
    if (incomingData[0] == '1')
    {
        Serial.println("Left stick move: UP!");
        moveShoulderUp();
    }

    if (incomingData[1] == '1')
    {
        shoulderClockwise();
        Serial.println("Left stick move: RIGHT!");
    }

    if (incomingData[2] == '1')
    {
        Serial.println("Left stick move: DOWN!");
        moveShoulderDown();
    }

    if (incomingData[0] == '0' &&
        incomingData[2] == '0')
    {
        stopShoulderUpDown();
    }

    if (incomingData[3] == '1')
    {
        shoulderCounterclockwise();
        Serial.println("Left stick move: LEFT!");
    }

    if (incomingData[1] == '0' &&
        incomingData[3] == '0')
    {
        shoulderStopRotation();
    }

    if (incomingData[4] == '1')
    {
        Serial.println("Left stick: BUTTON!");
        openHand();
    }

    // Right stick
    if (incomingData[5] == '1')
    {
        Serial.println("Right stick move: UP!");
        moveElbowUp();
    }

    if (incomingData[6] == '1')
    {
        Serial.println("Right stick move: RIGHT!");
        wristClockwise();
    }

    if (incomingData[7] == '1')
    {
        Serial.println("Right stick move: DOWN!");
        moveElbowDown();
    }

    if (incomingData[5] == '0' &&
        incomingData[7] == '0')
    {
        stopElbow();
    }

    if (incomingData[8] == '1')
    {
        Serial.println("Right stick move: LEFT!");
        wristCounterclockwise();
    }

    if (incomingData[6] == '0' &&
        incomingData[8] == '0')
    {
        stopWristRotation();
    }

    if (incomingData[9] == '1')
    {
        Serial.println("Right stick: BUTTON!");
        closeHand();
    }

    if (incomingData[4] == '0' &&
        incomingData[9] == '0')
    {
        stopHand();
    }
}
