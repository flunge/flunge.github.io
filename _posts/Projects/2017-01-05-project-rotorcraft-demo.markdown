---
layout: post
title:  "NUS Project Rotorcraft Asia Demonstration"
date:   2017-01-05
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [Demo Platform](#platform)
2. [UWB Ranging](#uwb)
3. [Simimar Project](#sideshow)

___

<a name = "platform"></a>

**Summary**

This project is the application of UAV entertainment, which is specifically LED light show. This is also one of the main applications in the current drone market, since the mini-sized drones are mostly used as an entertaining toy, such as selfie cameras or LED toys instead of indsutrial use. The recent news show several companies like Yihang, Intel or some research agents did UAV light shows with a large swarm of drones up to 500 or even 1000. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/aOd4-T_p5fA" frameborder="0" allowfullscreen></iframe></center>
<center>Intel swarm drones</center>

The project is for the opening ceremony of Rotorcraft Asia 2017, which will be held on April 18. The stage will be in a certain stadium, where no GPS signal is available. For indoor positioning, we use ultra-band width (UWB) system. The platform is also mounted an ultra-bright LED matrix pad for configurable color and brightness light. 

Flight controller:

All the flight controller used in my projects is the same (see <a href="https://flunge.github.io/2016/12/01/project-instinct.html#flightController">link</a>);

Flight controller extension board:

<center>
<img src="/public/figures/project/rotorcraft_upper_1.JPG" style="width:40%">
<img src="/public/figures/project/rotorcraft_upper_2.JPG" style="width:40%">
</center>
<center>front and top view <a href="https://grabcad.com/library/flight-control-extension-board-for-lightshow-1">[3D Model]</a></center>

1. The board integrates necessary peripherals: SD card for data logging, serial to Wi-Fi module for data-link, serial to USB device for debugging, LED controller, power rails and IO ports.
2. The LED controller uses Arduino as platform and Neopixel libraries for light control and pattern design.

Power extension:

<center>
<img src="/public/figures/project/rotorcraft_lower_1.JPG" style="width:40%">
<img src="/public/figures/project/rotorcraft_lower_2.JPG" style="width:40%">
</center>
<center>front and top view <a href="https://grabcad.com/library/motherboard-for-project-instinct-1">[3D Model]</a></center>

1. This platform adopts dual-board design in order to reduce the foot-print, as a quad-rotor helicopter with dimension limitation confines its space left for avionics;
2. Another reason for dual board design is that the onboard magnetometer is prone to be interfered by large current, if there is only one extension board, where large current drained by ESCs is inevitable. Dual board design separates large current and megnetic components with one mu-metal slice sheet placed in between if necessary;
3. This power extension board includes: dual 5V power output, one 12V power output, one MicroHard pDDl data and video link system, 2 ethernet ports for connecting Up-board as a remote control display port as well as another device (laser scanner / UWB ranging module), power distributions.

Other Modules:

1. Dampers: dampers are necessary to reject high freqency vibrations. Silicon ball dampers are used and tested.
2. UWB ranging modules: we selected the PulsOn 440 from Time Domain as the ranging modules, whose max communication range is up to 200 m, which is enough for indoor demo use. 
3. Up-board: the upper level CPU used for path planning and trajectory generation. Coordinates calculation for a certain tag given a random setup of anchors is also processed in the CPU. 
4. LED device: we select Neopixel LED matrix for light display for its high lumin parameter and the color and brightness can be configured to desired values. 

<center>
<img src="/public/figures/project/rotorcraft_lower_1.JPG" style="width:40%">
<img src="/public/figures/project/rotorcraft_lower_2.JPG" style="width:40%">
</center>
<center>Top and side view <a href="https://grabcad.com/library/motherboard-for-project-instinct-1">[3D Model]</a></center>

Below is our first manual flight test, where we conducted outside our lab. It can be seen from the video vibration exists at the take-off period. This could be the gain tuning problem. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/dUXnVfIDlSk" frameborder="0" allowfullscreen></iframe></center>
<center>Manual flight test</center>