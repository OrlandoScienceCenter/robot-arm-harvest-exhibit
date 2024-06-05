#include <Arduino.h>
#include <SoftwareSerial.h>

constexpr int PIN_LEFTSTICK_DIRECTION_UP =     2;
constexpr int PIN_LEFTSTICK_DIRECTION_RIGHT =  3;
constexpr int PIN_LEFTSTICK_DIRECTION_DOWN =   4;
constexpr int PIN_LEFTSTICK_DIRECTION_LEFT =   5;
constexpr int PIN_LEFTSTICK_DIRECTION_BUTTON = 6;

constexpr int PIN_RIGHTSTICK_DIRECTION_UP =     7;
constexpr int PIN_RIGHTSTICK_DIRECTION_RIGHT =  8;
constexpr int PIN_RIGHTSTICK_DIRECTION_DOWN =   9;
constexpr int PIN_RIGHTSTICK_DIRECTION_LEFT =   10;
constexpr int PIN_RIGHTSTICK_DIRECTION_BUTTON = 11;

SoftwareSerial mainBoardSerial(13, 12); // RX, TX

void setup()
{
    Serial.begin(115200);

    mainBoardSerial.begin(9600);

    pinMode(PIN_LEFTSTICK_DIRECTION_UP, INPUT_PULLUP);
    pinMode(PIN_LEFTSTICK_DIRECTION_RIGHT, INPUT_PULLUP);
    pinMode(PIN_LEFTSTICK_DIRECTION_DOWN, INPUT_PULLUP);
    pinMode(PIN_LEFTSTICK_DIRECTION_LEFT, INPUT_PULLUP);
    pinMode(PIN_LEFTSTICK_DIRECTION_BUTTON, INPUT_PULLUP);

    pinMode(PIN_RIGHTSTICK_DIRECTION_UP, INPUT_PULLUP);
    pinMode(PIN_RIGHTSTICK_DIRECTION_RIGHT, INPUT_PULLUP);
    pinMode(PIN_RIGHTSTICK_DIRECTION_DOWN, INPUT_PULLUP);
    pinMode(PIN_RIGHTSTICK_DIRECTION_LEFT, INPUT_PULLUP);
    pinMode(PIN_RIGHTSTICK_DIRECTION_BUTTON, INPUT_PULLUP);
}

void loop()
{
    const bool leftStickDirectionUp = !digitalRead(PIN_LEFTSTICK_DIRECTION_UP);
    const bool leftStickDirectionRight = !digitalRead(PIN_LEFTSTICK_DIRECTION_RIGHT);
    const bool leftStickDirectionDown = !digitalRead(PIN_LEFTSTICK_DIRECTION_DOWN);
    const bool leftStickDirectionLeft = !digitalRead(PIN_LEFTSTICK_DIRECTION_LEFT);
    const bool leftStickDirectionButton = !digitalRead(PIN_LEFTSTICK_DIRECTION_BUTTON);

    const bool rightStickDirectionUp = !digitalRead(PIN_RIGHTSTICK_DIRECTION_UP);
    const bool rightStickDirectionRight = !digitalRead(PIN_RIGHTSTICK_DIRECTION_RIGHT);
    const bool rightStickDirectionDown = !digitalRead(PIN_RIGHTSTICK_DIRECTION_DOWN);
    const bool rightStickDirectionLeft = !digitalRead(PIN_RIGHTSTICK_DIRECTION_LEFT);
    const bool rightStickDirectionButton = !digitalRead(PIN_RIGHTSTICK_DIRECTION_BUTTON);

    // Left stick
    mainBoardSerial.print(leftStickDirectionUp);
    mainBoardSerial.print(leftStickDirectionRight);
    mainBoardSerial.print(leftStickDirectionDown);
    mainBoardSerial.print(leftStickDirectionLeft);
    mainBoardSerial.print(leftStickDirectionButton);

    // Right stick
    mainBoardSerial.print(rightStickDirectionUp);
    mainBoardSerial.print(rightStickDirectionRight);
    mainBoardSerial.print(rightStickDirectionDown);
    mainBoardSerial.print(rightStickDirectionLeft);
    mainBoardSerial.print(rightStickDirectionButton);

    mainBoardSerial.println();

    // Left stick
    // Serial.print(leftStickDirectionUp);
    // Serial.print(leftStickDirectionRight);
    // Serial.print(leftStickDirectionDown);
    // Serial.print(leftStickDirectionLeft);
    // Serial.print(leftStickDirectionButton);
    //
    // // Right stick
    // Serial.print(rightStickDirectionUp);
    // Serial.print(rightStickDirectionRight);
    // Serial.print(rightStickDirectionDown);
    // Serial.print(rightStickDirectionLeft);
    // Serial.print(rightStickDirectionButton);
    //
    // Serial.println();
}
