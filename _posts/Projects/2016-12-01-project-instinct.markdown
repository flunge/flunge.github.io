---
layout: post
title:  "NUS Project INSTINCT"
date:   2016-12-01
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [Flight Controller](#flightController)
2. [Mother Board](#motherboard)
3. [Platform Instinct](#platformInstinct)
4. [Software Modules](#software)

___

<a name = "flightController"></a>

**Summary**

This module provides power flight control features for general UAV platform use: multi-rotor platforms, single/coaxial rotor helicopter, unconventional aircrafts as tail-sitters and hybrids. The design extends its capability with all necessary signals connected to a customized connector, making it transportable to any extenion board with same connector type or even multiple identical flight controllers for redundancy purpose.

<center>
<img src="/public/figures/project/instinct_fc_1.JPG" style="width:40%">
<img src="/public/figures/project/instinct_fc_2.JPG" style="width:40%">
</center>
<center>front and reverse side view <a href="https://grabcad.com/library/adaptive-flight-controller-1">[3D Model]</a></center>

**Key Features**

General Information:

1. Layers: 8-layer PCB with 1 mm thickness. 
2. Dimension: 36 mm X 22 mm.
3. Main processor: STM32F427AIH6.
4. Necessary peripherals: minimum system, FRAM, I2C buffer, UART buffer, status LED, power regulator.
5. Signals extended: 16X PWMs, 4X GPIOs, 6X power, I2C, CAN bus, 6 Serial ports, USB ports, SWD ports.

Sensors included:

1. Gyroscopes: L3GD20;
2. Acceleromters: MMA8452Q, LSM303D;
3. Motion sensors: MPU6000, MPU6500, MPU9250;
4. Magnetometers: HMC5883L, MPU9250, LSM303D;
5. Barometers: MS5611-01BA, LPS22HB.
6. Explanations: all of these sensors share SPI or I2C bus, drivers will be started on system initilized, data will be polled with necessary rates (gyro rates and accelerations will be at 800 or 1000 Hz, magenetometers will be queried with 100 Hz and altitude will be sampled at 50 Hz). Sensors can also be connected on the expandable ports.

Modules running:

1. Sensor module: set all calibration parameters for opened sensors, obtain data from drivers output, combined all sensor data in one publishable topic;
2. Commander module: processing regular events as status display, low voltage alarm, arm-disarm operations, switch control mode and navigation mode, decoding commands from GCS, broadcasting status information;
3. Control modules: inner-loop attitude control module with composite nonlinear feedback method and output position control with robust perfect tracking method;
4. Data logging: configurable data logging with desired rates and topics;
5. Mission control: navigation mission control to specify mission elements, manage state machine and way-points. 
6. Base project: current firmware project is forked from the Pixhawk repo 3 years ago.


<a name = "motherboard"></a>

**Summary**

This motherboard extends the capabilities of the flight controller described in the above part. Besides providing power and extension signals to the flight controller, this motherboard got its own standalone functions. The current design works for quad-rotor, hexa-rotor and Y-3 configurations, with the pre-defined functions and shapes. 

<center>
<img src="/public/figures/project/instinct_mth_1.JPG" style="width:40%">
<img src="/public/figures/project/instinct_mth_2.JPG" style="width:40%">
</center>
<center>front and reverse side view <a href="https://grabcad.com/library/motherboard-for-project-instinct-1">[3D Model]</a></center>

General Information:

1. Layers: 6-layer PCB with 1 mm thickness. 
2. Dimension: 95 mm X 95 mm.
3. Power rails: input 2-cell to 4-cell battery, output 12V/1A, dual 5V/4.5A and 3.3V/1A power.

Functions extended:

1. GPS: integrated u-blox GPS m8 series receiver and antenna, with backup power supply.
2. Serial to Wi-Fi device: ESP8266 based tiny serial to Wi-Fi module for data downloading and command uploading. 
3. S-bus receiver: compatible with Futaba S-bus receiver module. 
4. ESCs: 6X 3-phase brushless DC motor ESCs, which supports PWM command mode and I2C command mode. The ESC is also able to report its status including voltage, current, temperature, and rpm. 
5. Other necessary parts: level shifter, protocol shifters, voltage and current sensing, board to wire connectors, etc.

Modules running:

1. Mavlink: communication module running on a specified UART prots and transmitted to GCS via serial to Wi-Fi device;
2. Servo output: PWMs/I2C bus connected to ESCs to transmit commands from controller for servo output;
3. PPM/S-bus: receiver input from RC transmitters, a UART device is allocated to S-bus input to decode the data, while PPM is a general timer function; 
4. Further peripherals: I2C bus will attached more devices (external magnetometers, range sensors, other MCUs), UART will be connected to upper-level CPU as Intel processor for more high level algorithm.