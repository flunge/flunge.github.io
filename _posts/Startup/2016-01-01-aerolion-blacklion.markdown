---
layout: post
title:  "One Year Summary for BlackLion Series Product"
date:   2016-01-01
categories: Startup
tags: [Startup, Hardware]
---

### Contents

1. [Introduction](#introduction)
2. [Technical Stuff](#technical)

___

<a name = "introduction"></a>

**Introduction**

The aerolion technologies is a spin-off company from the Unmanned Systems Research Group of the National University of Singapore. This company specializes in UAV autonomy and navigation in both indoor and outdoor cluttered environment.  

Their main directions include autonomous navigation of unmanned rotorcraft systems, design of unconventional aircrafts, and to provide solutions with intelligent UAVs for a wide range of real-life applications. Their solutions allow intuitive interactions between UAVs and users to precisely navigate and continuously broadcast useful information to the users.

Most of our group members are shareholders in that company and also contribute part of the technologies. I am also a shareholder as well as a member of the board committee. My main responsbility is to develop the hardware system and flight firmware for their main products <a href="http://www.aerolion.com/index.php?fc=module&module=leoblog&id=75&controller=blog&id_lang=1">BL168, <a href="http://www.aerolion.com/index.php?fc=module&module=leoblog&id=71&controller=blog&id_lang=1">BL108, <a href="http://www.aerolion.com/index.php?fc=module&module=leoblog&id=66&controller=blog&id_lang=1">BL068.


___

<a name = "technical"></a>

**Hardware**

Flight controller

The flight controller design shares the same hardware design and firmware branch with the NUS UAV flight control module, while this version is an older version of NUS UAV Instinct system. Main differences are listed below:

1. On-board SD card: the on-board SD card slot is a non-necessary integration in the new versions since a EEPROM or a FRAM device is mounted for parameters management and file storage;
2. Dual-processor design: this flight controller integrate two processors, one is the main processor and the other one is a serial servo output device enabled by a STM32F1xx series MCU. 

<center>
<img src="/public/figures/project/bl168_flc_1.JPG" style="width:30%">
<img src="/public/figures/project/bl168_flc_2.JPG" style="width:30%">
</center>
<center>Front and reverse side view <a href="https://grabcad.com/library/aerolion-technologies-bl-series-flight-control-1">[3D Model]</a></center>

Mother board

This is a well-designed motherboard which provides the following functions:
1. Redundancy: it can be seen from the figure that there are 2 slots for 2 separate flight controllers. One flight controller serves as the master and the other one as the slave module. They share information via serial port by Mavlink protocol, specifically, a heartbeat package, some sensor information and control output. Slave module will take over once the heartbeat package is lost for several times, or the sensor is faulty or control output exceeds a pre-defined ranges. Master is also able to take over from slave module once it was reboot by the slave and get everything correct.
2. Communication: the communication module is MicroHard IpnDDl, for data and video link.
3. Power: there are several power rails designed for this version for backup and redundancy. The analog power and the digital power are separate in case the current for motor and othe analog device pollutes the digital power rail, which is more sensitive to some devices. 

<center>
<img src="/public/figures/project/bl168_mother_1.JPG" style="width:40%">
<img src="/public/figures/project/bl168_mother_2.JPG" style="width:40%">
</center>
<center>Front and reverse side view <a href="https://grabcad.com/library/aerolion-technologies-bl168-extension-board-1">[3D Model]</a></center>

Ground Control Station

Ground control station is an indispensable part for the whole product. For the BL168 design, the GCS has the following functions:
1. Data Hub: the GCS receives data signals from the airborne part and transmit these data to those devices that need them, i.e. the toughpad, or central control hub. 
2. Video info: the GCS receives the real-time video or image from the UAV and display on the monitor. 
3. Commander: to send command signals to the airborne devices. 

In a simple word, the GCS is a communication hub which transmit and receive data packages. Thus, the circuit designed for the GCS is a communication devices with its peripherals and mostly power regulation and distributions. Multiple 5V and 12V ports are for devices like monitor, router, voltage/current display, switches, fans and so on.

<center>
<img src="/public/figures/project/bl168_gcs_1.JPG" style="width:40%">
<img src="/public/figures/project/bl168_gcs_2.JPG" style="width:40%">
</center>
<center>Front and reverse side view <a href="https://grabcad.com/library/aerolion-technologies-bl168-v2-gcs-1">[3D Model]</a></center>