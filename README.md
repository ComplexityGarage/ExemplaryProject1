**IMPORTANT: while viewing the circuit diagram, please take notice of the fact that the RTC module is missing. It isn't available in Tinkercad components, that's why it couldn't be included in the diagram. RTC pins were connected to the Arduino board in a following way:**
- VCC --> 5V
- GND --> gnd
- CLK --> D10 (digital pin 10)
- DAT --> D9
- RST --> D7

# Light deactivated alarm clock in shape of a garage
# Authors 
- Eryk Bluj
- Mateusz Janus
# Description of the project 
For our final project during Garage of Complexity course we decided to make an alarm clock. In order to switch it off it's necessary to light a photoresistor placed in the chimney. The shape of the alarm clock resembles a garage to match the name of the course - "Garage of Complexity". Our garage alarm clock is shown in the photo below: 

<p align="center">
<img src="https://github.com/ComplexityGarage/ExemplaryProject1/assets/104577187/8bb08fda-fac9-44b5-bbf4-b41ae17ff72a" width="400">

# Science and tech used 
List of items used in making the alarm clock:
1. justPi 2x16 green LCD screen
2. photoresistor 
3. four 10k&Omega; resistors
4. potentiometer
5. DS1302 real time clock module
6. two buttons
7. YD36 analogue speaker
8. Arduino Uno Rev3 board

The case was 3D printed and placed on a styrofoam base. The current time and time of an alarm are displayed on an lcd screen. A photoresistor placed in the chimney serves as a switch. An rtc module keeps track of  time. Two buttons in front of a garage allow a user to change both current and alarm time. There is also an analogue speaker, which plays a simple melody when an alarm goes off. All constituents are connected to an Arduino UNO board through a breadboard.
# State of the art 
We learned many useful things throughout this project and the whole course in general. Wiring and programming an Arduino board isn't a mystery to us anymore. We now know how to include many parts in a circuit and make them work simultaneously. We also gained experience in understanding documentation and wiring related to new components. The whole process of 3D printing became much more intuitive. In addition to that, we learned how to efficiently divide tasks and deal with troubleshooting.
# What next?
Right now we are thinking about what our next project could be and looking forward to the next edition of the course.
# Sources 
- [LCD screen] ( https://docs.arduino.cc/learn/electronics/lcd-displays/ )
- [RTC module library] ( https://www.arduino.cc/reference/en/libraries/ds1302/ )
- [Simple melody example] ( https://docs.arduino.cc/built-in-examples/digital/toneMelody/ )
- [Garage project] (https://www.tinkercad.com/things/0RcNsphQe3S-garage)
