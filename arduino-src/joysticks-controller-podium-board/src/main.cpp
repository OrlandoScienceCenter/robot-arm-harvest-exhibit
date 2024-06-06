#include <Arduino.h>
#include <SoftwareSerial.h>

constexpr int PIN_LEFTSTICK_DIRECTION_UP =     2;   // ORANGE on CAT6
constexpr int PIN_LEFTSTICK_DIRECTION_RIGHT =  3;   // GRREN on CAT6
constexpr int PIN_LEFTSTICK_DIRECTION_DOWN =   4;   // BLUE on CAT6
constexpr int PIN_LEFTSTICK_DIRECTION_LEFT =   5;   // BROWN on CAT6
constexpr int PIN_LEFTSTICK_DIRECTION_BUTTON = 6;   // WHITE/GREEN striped on CAT6

constexpr int PIN_RIGHTSTICK_DIRECTION_UP =     7;  // ORANGE on CAT6
constexpr int PIN_RIGHTSTICK_DIRECTION_RIGHT =  8;  // GRREN on CAT6
constexpr int PIN_RIGHTSTICK_DIRECTION_DOWN =   9;  // BLUE on CAT6
constexpr int PIN_RIGHTSTICK_DIRECTION_LEFT =   10; // BROWN on CAT6
constexpr int PIN_RIGHTSTICK_DIRECTION_BUTTON = 11; // WHITE/GREEN striped on CAT6

SoftwareSerial mainBoardSerial(A0, 12); // RX, TX

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

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void turnOnLedIfAnyJoystickActivity(bool leftStickDirectionUp, bool leftStickDirectionRight, bool leftStickDirectionDown, bool leftStickDirectionLeft, bool leftStickButton, bool rightStickDirectionUp, bool rightStickDirectionRight, bool rightStickDirectionDown, bool rightStickDirectionLeft, bool rightStickButton);

void loop()
{
    const bool leftStickDirectionUp = !digitalRead(PIN_LEFTSTICK_DIRECTION_UP);
    const bool leftStickDirectionRight = !digitalRead(PIN_LEFTSTICK_DIRECTION_RIGHT);
    const bool leftStickDirectionDown = !digitalRead(PIN_LEFTSTICK_DIRECTION_DOWN);
    const bool leftStickDirectionLeft = !digitalRead(PIN_LEFTSTICK_DIRECTION_LEFT);
    const bool leftStickButton = !digitalRead(PIN_LEFTSTICK_DIRECTION_BUTTON);

    const bool rightStickDirectionUp = !digitalRead(PIN_RIGHTSTICK_DIRECTION_UP);
    const bool rightStickDirectionRight = !digitalRead(PIN_RIGHTSTICK_DIRECTION_RIGHT);
    const bool rightStickDirectionDown = !digitalRead(PIN_RIGHTSTICK_DIRECTION_DOWN);
    const bool rightStickDirectionLeft = !digitalRead(PIN_RIGHTSTICK_DIRECTION_LEFT);
    const bool rightStickButton = !digitalRead(PIN_RIGHTSTICK_DIRECTION_BUTTON);

    turnOnLedIfAnyJoystickActivity(leftStickDirectionUp,
        leftStickDirectionRight,
        leftStickDirectionDown,
        leftStickDirectionLeft,
        leftStickButton,
        rightStickDirectionUp,
        rightStickDirectionRight,
        rightStickDirectionDown,
        rightStickDirectionLeft,
        rightStickButton);

    // Left stick
    mainBoardSerial.print(leftStickDirectionUp);
    mainBoardSerial.print(leftStickDirectionRight);
    mainBoardSerial.print(leftStickDirectionDown);
    mainBoardSerial.print(leftStickDirectionLeft);
    mainBoardSerial.print(leftStickButton);

    // Right stick
    mainBoardSerial.print(rightStickDirectionUp);
    mainBoardSerial.print(rightStickDirectionRight);
    mainBoardSerial.print(rightStickDirectionDown);
    mainBoardSerial.print(rightStickDirectionLeft);
    mainBoardSerial.print(rightStickButton);

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

void turnOnLedIfAnyJoystickActivity(bool leftStickDirectionUp, bool leftStickDirectionRight, bool leftStickDirectionDown, bool leftStickDirectionLeft, bool leftStickButton,
                                   bool rightStickDirectionUp, bool rightStickDirectionRight, bool rightStickDirectionDown, bool rightStickDirectionLeft, bool rightStickButton)
{

    if (leftStickDirectionUp || leftStickDirectionRight || leftStickDirectionDown || leftStickDirectionLeft || leftStickButton ||
        rightStickDirectionUp || rightStickDirectionRight || rightStickDirectionDown || rightStickDirectionLeft || rightStickButton)
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
