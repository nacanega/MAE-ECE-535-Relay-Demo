# MAE-ECE-535-Relay-Demo

Code repository for MAE/ECE 535 Relay Experimental Demonstration

---
## Contents

### MAE-ECE-535_RelayDemoProject.ino

Arduino Sketch containting the code needed to run the demo. Includes the following remote commands:

|Button|Function|
|---|---|
|POWER|Toggle the state of the demo relay|
|FUNC/STOP|Toggle the state of the open automotive relay|
|FAST BACK|Decreases length of "." by 10 ms (min 40 ms, default 60 ms)|
|PAUSE|Taps out the Morse code for "MAE/ECE 535 RELAY DEMO PROJECT"|
|FAST FORWARD|Increases length of "." by 10 ms (max 80 ms, default 60 ms)|
|DOWN|Taps out the Morse code for "SOS"|
|UP|Taps out the Morse code for "HELLO!"|
|0|Taps out the Morse code for "0"|
|1|Taps out the Morse code for "1"|
|2|Taps out the Morse code for "2"|
|3|Taps out the Morse code for "3"|
|4|Taps out the Morse code for "4"|
|5|Taps out the Morse code for "5"|
|6|Taps out the Morse code for "8"|
|7|Taps out the Morse code for "7"|
|8|Taps out the Morse code for "8"|
|9|Taps out the Morse code for "9"|

Requires that the following schematic be wired prior to uploading to your Arduino:

![alt text](https://github.com/nacanega/MAE-ECE-535-Relay-Demo/blob/51914a9584024ef7103f6e732599cca97b6b6cd0/MAE-ECE-535_Relay_Demo_Project_Schematics_black.png "Circuit/Wiring Diagram of Relay Demonstrator")

#### Notes
  * The fast forward and fast back functions can be used to adjust to your relay so that the Morse code is decipherable
  * A Keyestudio Mega 2560 R3 Plus might be required since it has more connections and can support higher output current (1.5A)

### magforce.m
MATLAB script which:
1) Visualizes the magnetic force (obtained from FEMM) as a function of gap distance
2) Uses the magnetic force data to fit a 4th order polynomial relating magnetic force to gap distance
3) Uses the curve fit and derived equation of motion to simulate the behavior of our relay
    - Utilizes Euler's method for numerical integration
    - Simulates when the coil is energized
    - Then simulates when the coil is de-energized
4) Plots the resulting armature arm angle, angular velocity, angular acceleration, and gap distance (from washer on bottom of armature to electromagnet) as functions of time 
---
## Abstract
Electromechanical relays are devices which are used to control large currents with small currents. This project focuses on the creation of a simple Single-Pole Double-Throw (SPDT) relay. Designing an electromechanical relay involves balancing the torques on an armature and then creating an electromagnet such that the force on the armature is enough to quickly move contacts to act as a switch. Balancing the forces includes determining the spring force and location, center of mass and mass, and magnetic force and location. The magnetic force can be approximated using the 2D FEA software FEMM. The dynamics can then be simulated via numerical integration using various gap distances to interpolate magnetic forces at different gaps. This data can then be used to design and/or predict the responses of a working relay.

---
## Video Demonstration
[![YouTube Video Demonstration](http://img.youtube.com/vi/MjULgcrd9X8/0.jpg)](http://www.youtube.com/watch?v=MjULgcrd9X8)
