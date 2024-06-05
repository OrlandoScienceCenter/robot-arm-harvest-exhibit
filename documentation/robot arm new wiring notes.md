    New wiring

GND from joysticks MCU to NO pins on all joystick switches

RJ-45 to breadboard adapters: all pins match up, e.g. 1 > 1, 2 > 2, 3 > 3 etc when normal CAT6 cable is plugged in

RJ-45 adapters: 
    
    PIN 1 > RS485 A+ 
    PIN 2 > RS485 B-
    PIN 3 > NC
    PIN 4 > Main board and Joysticks board shared ground
    PIN 5 > Main board sending 5v to power joysticks board
    
Joysticks board:
    
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

    UART TX into RS485 board = 12
    
    A+ into ethernet cable = ETH PIN 01
    B- into ethernet cable = ETH PIN 02

    Shared GND on ethernet cable (from ESP32 on other side) = ETH PIN 05    
    5V from ethernet cable (from ESP32 on other side) = ETH PIN 06

