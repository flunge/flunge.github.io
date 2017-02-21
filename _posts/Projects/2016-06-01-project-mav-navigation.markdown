---
layout: post
title:  "NUS Project Autonomous Navigation of MAVs"
date:   2016-06-01
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [Flight Controller](#flightController)
2. [Electronic Speed Control](#escs)
3. [Optical Flow Module](#optical)
4. [Gumstix on YOCTO Project](#gumstix)
5. [Platform Overview](#platform)

___

<a name = "flightController"></a>

**Summary**

This flight control module is the most optimized integration compared to the COTS products. The development duration expands for two years, where I improved the controller from the aspects of new functions, smaller footprints, EMC/EMI concerns, current inteference, signal reflection and oscillation. These signal integrity issues affects the performance of the signal as well as the lifttime of the components to a large extent. 

<center>
<img src="/public/figures/project/mav_fc_1.JPG" style="width:30%">
<img src="/public/figures/project/mav_fc_2.JPG" style="width:30%">
</center>
<center>front and reverse side view <a href="https://grabcad.com/library/micro-quad-flight-controller-1">[3D Model]</a></center>

**Key Features**

General Information:

1. Layers: 8-layer PCB with 1 mm thickness. 
2. Dimension: 35 mm X 35 mm.
3. Main processor: STM32F427IIH6.
4. Necessary peripherals: minimum system, FRAM, I2C buffer, UART buffer, status LED, power regulator, power switcher, GPS ublox m8q, SD slot, 

1. Gyroscopes: L3GD20;
2. Acceleromters: MMA8452Q, LSM303D;
3. Motion sensors: MPU6000, MPU6500;
4. Magnetometers: HMC5883L, LSM303D;
5. Barometers: MS5611-01BA.
6. Explanations: all of these sensors share SPI or I2C bus, drivers will be started on system initilized, data will be polled with necessary rates (gyro rates and accelerations will be at 800 or 1000 Hz, magenetometers will be queried with 100 Hz and altitude will be sampled at 50 Hz). Sensors can also be connected on the expandable ports.

Modules running:

1. Sensor module: set all calibration parameters for opened sensors, obtain data from drivers output, combined all sensor data in one publishable topic;
2. Commander module: processing regular events as status display, low voltage alarm, arm-disarm operations, switch control mode and navigation mode, decoding commands from GCS, broadcasting status information;
3. Control modules: inner-loop attitude control module with composite nonlinear feedback method and output position control with robust perfect tracking method;
4. Data logging: configurable data logging with desired rates and topics;
5. Mission control: navigation mission control to specify mission elements, manage state machine and way-points. 

___


<a name = "escs"></a>




