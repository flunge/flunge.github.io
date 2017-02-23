---
layout: post
title:  "NUS Project Remote System"
date:   2016-11-01
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [RF module](#rfmodule)
2. [Radio Receiver](#radioreceiver)
3. [UWB module](#uwb)

___

<a name = "rfmodule"></a>

**Motivation**

Communication techniques is regarded as the core technology in robotic area, especially for UAVs. UAVs often commit missions in some locations that human beings are not accessible, where are always far from the GCS location. This relies on the effectiveness of communication module to transmit the data, even videos to the base station. We have used several communication modules or telemetry, most of which are bulky or not powerful enough. This motivates me to develop my own communication modules for UAV data link.

<center>
<img src="/public/figures/project/remote_1.JPG" style="width:40%">
</center>
<center>Remote control module front view <a href="https://grabcad.com/library/rf-module-1">[3D Model]</a></center> 

**Module Overview**

Hardware specs

1. Processor: STM32F405;
2. RF module: CC2520 and CC2591, where CC2520 is a TI radio transceiver, and CC2591 is the amplifier for longer range concerns.
3. Necessary ports. 

Software Issues

1. Operating System: I am now using ChibiOS as the RTOS for firmware integration.
2. Driver Issue: now the driver of CC2520 via SPI port got some issues and not to be debugged. Maybe is the crystal problem, or maybe other hardware failure. 
3. Sample application: transmitting a simple digit and display at the receiver side.

___

<a name = "radioreceiver"></a>

**Motivation**

For a minimalist design of palm sized quad-rotor UAV, there is no COTS available product, which is small and light enough and compatible with the main brand transmitters like Futaba, Spectrum or JR. This is the motivation to develop such a module that is compatible with one of these transmitter and has a much smaller footprint than the COTS receivers.

<center>
<img src="/public/figures/project/rf_1.JPG" style="width:20%">
<img src="/public/figures/project/rf_1.JPG" style="width:20%">
</center>
<center>front and reverse side view <a href="https://grabcad.com/library/simple-rc-receiver-1">[3D Model]</a></center> 

Hardware Specs 

1. Dimension: 12mm X 14mm;
2. Transceiver: CYRF6936 with a SPI bus connects to the FCU. 
3. RF: ISM band with transmitting power less than 4 dBm.

Software Issues

1. Related work: forked from the TU Delft branch, the Spectrum protocol was hacked and implemented in the processor. 
2. Protocol: DSMx, working better in more radio-crowded environment and performs better to resist noise. 
3. Issues: got bugs in transmission state machine, should be time interval problem, still under debugging.

___

<a name = "uwb"></a>

**Motivation**

Demand for GPS-denied environment navigation of unmanned system has an increasing trend recent years. Several approaches solves the problems:
1. SLAM techniques: the laser or visual SLAM solves the GPS-denied navigation with several different approaches. The laser SLAM is more robust and accurate, while too expensive to be equipped on every drone. The visual SLAM has a low cost, while it consumes much more computational power than the laser SLAM. 
2. UWB positioning techniques: this method is much more easier to realize with several anchors and the UAV is one of the tags. It also supports multi-UAV show without putting in much more effort. 
However, for current COTS products, the UWB module is still expensive, like the Time Domain one. 
This is the motivation for me to find out a low-cost solutin to develop a UWB module.


<center>
<img src="/public/figures/project/uwb_1.JPG" style="width:50%">
</center>
<center>UWB module front view <a href="https://grabcad.com/library/uwb-module-1">[3D Model]</a></center> 

Hardware Specs 

1. Dimension: 40mm X 14mm;
2. Processor: STM32F405; 
3. UWB transceiver: Decawave DWM1000.

Software Issues

1. Operating System: Nuttx; 
2. DWM1000 Driver: the driver is forked from the online documents;
3. Ranging Techniques: current I am trying the one-way ranging method, detailed see <a href="http://mikehamer.info/assets/papers/Ledergerber,%20Hamer,%20DAndrea%20-%20IROS%202015.pdf">[this paper].