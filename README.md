# robot-arm-harvest-exhibit
Redoing the agricultural robotics robotic arm exhibit

# Troubleshooting

## Joysticks

### Joystick input not registering

The arduino on the joysticks side (In the joystick housing) will light the LED labelled "L" when there is any joystick activity on either joystick.
 
This means if it is always on, a switch has likely failed closed and will need to be replaced.
 
If the LED lights on all but one or two axis when you move the joystick (LED should light for up/down/left/right/button) then those switches have likely failed in a way where they never make contact, and will need to be replaced.
 
If it never lights, no matter what you do on a joystick, then that joystick's connection to GND has likely failed. (GND should be connected to all 5 switch NO pins on each of the 5 switches for a particular joystick.)
 
If it never lights, no matter what you do on BOTH joysticks, then the shared cable to GND has likely lost connection to the arduino board.
 
### Joystick arduino has no LEDs lit
 
The joystick arduino board gets power from the main microcontroller over the CAT6 cable. If absolutely no LEDs are lit on the joystick arduino board, then the CAT6 chain likely has a problem somewhere. Check all cables to ensure they are connected, and try replacing the main CAT6 cable that runs between the joysticks case and the main exhibit case.


