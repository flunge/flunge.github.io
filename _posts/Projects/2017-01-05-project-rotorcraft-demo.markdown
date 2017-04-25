---
layout: post
title:  "NUS Project Rotorcraft Asia Demonstration"
date:   2017-01-05
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [Demo Platform](#platform)
2. [Autonomous Navigation](#uwb)
3. [Actual Performance](#sideshow)

___

<a name = "platform"></a>

### The Formation Platforms

**Introduction**

This project is the application of UAV entertainment, which is specifically LED light show. This is also one of the main applications in the current drone market, since the mini-sized drones are mostly used as an entertaining toy, such as selfie cameras or LED toys instead of indsutrial use. The recent news show several companies like Yihang, Intel or some research agents did UAV light shows with a large swarm of drones up to 500 or even 1000. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/aOd4-T_p5fA" frameborder="0" allowfullscreen></iframe></center>
<center>Intel swarm drones</center>

Before the Intel 500 demos, the NUS UAV team also realized a 16-set quadcopter outdoor light show with aid of differential GPS for very accurate positioning. Below video is the show, where the prime minister Lee Hsien Loong appeared. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/yk8_nqSM1WE" frameborder="0" allowfullscreen></iframe></center>
<center>Lightshow formation by NUS UAV team at Singapore Gardens by the Bay</center>


The project is for the opening ceremony of Rotorcraft Asia 2017, which will be held on April 18. The stage will be in a certain stadium, where no GPS signal is available. For indoor positioning, we use ultra-band width (UWB) system. The platform is also mounted an ultra-bright LED matrix pad for configurable color and brightness light. 

**Flight Controller**

All the flight controller used in my projects is the same (see <a href="https://flunge.github.io/2016/12/01/project-instinct.html#flightController">link</a>);

**Flight Controller Expansion Board**

1. The board integrates necessary peripherals: SD card for data logging, serial to Wi-Fi module for data-link, serial to USB device for debugging, LED controller, power rails and IO ports.
2. The LED controller uses Arduino as platform and Neopixel libraries for light control and pattern design.

<center>
<img src="/public/figures/project/rotorcraft_upper_1.JPG" style="width:40%">
<img src="/public/figures/project/rotorcraft_upper_2.JPG" style="width:40%">
</center>
<center>Front and top view <a href="https://grabcad.com/library/flight-control-extension-board-for-lightshow-1">[3D Model]</a></center>

**Power Expansion Board**

<center>
<img src="/public/figures/project/rotorcraft_lower_1.JPG" style="width:40%">
<img src="/public/figures/project/rotorcraft_lower_2.JPG" style="width:40%">
</center>
<center>Front and top view <a href="https://grabcad.com/library/power-with-communication-board-1">[3D Model]</a></center>

1. This platform adopts dual-board design in order to reduce the foot-print, as a quad-rotor helicopter with dimension limitation confines its space left for avionics;
2. Another reason for dual board design is that the onboard magnetometer is prone to be interfered by large current, if there is only one extension board, where large current drained by ESCs is inevitable. Dual board design separates large current and megnetic components with one mu-metal slice sheet placed in between if necessary;
3. This power extension board includes: dual 5V power output, one 12V power output, one MicroHard pDDl data and video link system, 2 ethernet ports for connecting Up-board as a remote control display port as well as another device (laser scanner / UWB ranging module), power distributions.

**Other Modules**

1. Dampers: dampers are necessary to reject high freqency vibrations. Silicon ball dampers are used and tested.
2. UWB ranging modules: we selected the PulsOn 440 from Time Domain as the ranging modules, whose max communication range is up to 200 m, which is enough for indoor demo use. 
3. Up-board: the upper level CPU used for path planning and trajectory generation. Coordinates calculation for a certain tag given a random setup of anchors is also processed in the CPU. 
4. LED device: we select Neopixel LED matrix for light display for its high lumin parameter and the color and brightness can be configured to desired values. 

<center>
<img src="/public/figures/project/rotorcraft_quad_1.png" style="width:60%">
<img src="/public/figures/project/rotorcraft_quad_2.png" style="width:60%">
</center>
<center>Top and side view</center>

Below is our first manual flight test, where we conducted outside our lab. It can be seen from the video vibration exists at the take-off period. This could be the gain tuning problem. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/dUXnVfIDlSk" frameborder="0" allowfullscreen></iframe></center>
<center>Manual flight test</center>

___

### Autonomous Navigation

This is a milestone for fully autonomous control of the UWB version quad-copter designed for this project. We have mounted several VICON markers on the platform and placed in the VICON environment. In order to test the performance of the implemented control law as well as calibrate the UWB positioning accuracy, we first do the auto hovering in VICON room and further with a simple path. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/xKCNQzzwZnU" frameborder="0" allowfullscreen></iframe></center>
<center>Fully autonomous control with aid of VICON system</center>

**Problems and Solutions**

1. Attitude estimation error: this was caused by the temperature effect on the MPU9250 series motion sensors. The accelerometer readings will be affected by the varying temperature on the start-up phase. This was solved by the adding a temperature curve compensation of the accleration measurement;
2. UWB ranging error: this was mainly caused by setup of the UWB anchors. The positions and distance between each other affect the final ranging accuracy. 
3. UWB estimation error: this was introduced by low update rates of UWB range information as well as the extended Kalman Filter motion model. The motion model was a constant velocity model which did not concern the dynamics of the drones. We added the acceleration information into the motion model and improved the update frequency of the overall range request loops, the accuracy was also improved to 5cm and latency was limited within 200ms. 
4. Magnetometer interference problem: this was caused by the large current interference to the magnetic field around the magnetometer. The final platform uses shielding materials above the power regulation board and eventually mitigated the effect. 

___

### Actual Performance

It was the actual day for the UMSA openning ceremony. We have been testing the whole formation drones system for the last two weeks in Changi Exhibition Center, the Aviation Park beside the sea. The UWB signal is very stable and reliable in the demo hall area with the full dimension around 15m X 15m X 7m. The formation drones was reduced to 6 sets from 10 sets due to the confined area and signal bandwidth capability. The formation shape and path designed for each drone is based on the music rhythm and light will also changes their patterns and color accordingly.  

The patterns include a formal square shape, a figure eight rotation, a random flight, a heart shape, leader and followers shape. With the starry night background and the music, the overall effect is really touching and exciting.  

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/imvOHrcYKy4" frameborder="0" allowfullscreen></iframe></center>
<center>Fully autonomous control with aid of VICON system</center>