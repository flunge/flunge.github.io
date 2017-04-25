---
layout: post
title:  "NUS Project INSTINCT"
date:   2016-12-01
categories: Project
tags: [Project, Hardware]
---

### Contents

1. [Project Mainline](#mainline)
2. [Platform Development](#motherboard)
3. [Software Modules](#software)
4. [FPGA Stereo Vision](#fpga)
5. [Sub-project1: SAFMC-2017](#safmc)
6. [Sub-project2: IMAV-2017](#imav)

___

<a name = "mainline"></a>

### Project Mainline

**Introduction**

This project aims to deelop a comprehensive and implementable UAV GPS-less navigation system capable of navigating through indoor and under-foliage. The system must be light-weight to be carried on-board, real-time processing and robust in handling realistic scenarios. Multiple agent cooperation for missions will also be studied through this project.

**Scope of Work**

**Summary**

___

<a name = "platform"></a>

### Platform Development

**Flight Control Module**

This module provides power flight control features for general UAV platform use: multi-rotor platforms, single/coaxial rotor helicopter, unconventional aircrafts as tail-sitters and hybrids. The design extends its capability with all necessary signals connected to a customized connector, making it transportable to any extenion board with same connector type or even multiple identical flight controllers for redundancy purpose.

<center>
<img src="/public/figures/project/instinct_fc_1.JPG" style="width:30%">
<img src="/public/figures/project/instinct_fc_2.JPG" style="width:30%">
</center>
<center>Front and reverse side view <a href="https://grabcad.com/library/adaptive-flight-controller-1">[3D Model]</a></center>

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

**Motherboard**

This motherboard extends the capabilities of the flight controller described in the above part. Besides providing power and extension signals to the flight controller, this motherboard got its own standalone functions. The current design works for quad-rotor, hexa-rotor and Y-3 configurations, with the pre-defined functions and shapes. 

<center>
<img src="/public/figures/project/instinct_mth_1.JPG" style="width:40%">
<img src="/public/figures/project/instinct_mth_2.JPG" style="width:40%">
</center>
<center>Front and reverse side view <a href="https://grabcad.com/library/motherboard-for-project-instinct-1">[3D Model]</a></center>

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

**Platform Overview**

Below figures shows the overall assembly effect of the platform INSTINCT. With the flight controller and mother board, the hexa-copter is able to perform GPS guided navigation. Design has been verified with real flight test data besides the lab. 

<center>
<img src="/public/figures/project/instinct_hex_1.png" style="width:60%">
<img src="/public/figures/project/instinct_hex_2.png" style="width:60%">
</center>
<center>Top and side view</center>

Parameter table:

1. Measured: several parameters are measured, as mass, dimension and beam length;
2. Estimated: moment of inertia can be calculated with a simple experimental setup, i.e. 3-wire setup. Alternatively, they can be obtained with an estimated value from SolidWorks, given that density and mass of all components are correctly defined. 
3. Calculated: motor & propeller parameters are calculated with experiments, i.e. a tachometer and a pwm recorder to calculate motor steady state parameters, a load cell and a tachometer to calculate propeller thrust and torque parameters.

Controller stuff:

1. Modeling: nonlinearity involved by the kinematic part is handled once the current attitude and reference attitude is known, by the thrust-vector orientation method. Output of this part will be the pure 6-DOF dynamics, which can be handled with a standard method, feedback linearation with the estimated gyro rates.
2. Control: inner-loop attitude is controlled with a 200 Hz controller, which is realized with composite nonlinear feedback method. This method is suitable for fast dynamic plant for its high gain at large error and low gain at small error, that is to say, fast convergence rate at initial state and small overshoot when output is approaching reference. For outer loop, the robust perfect tracking method is used with an augmented plant definition. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/bFXiUpcPxbg" frameborder="0" allowfullscreen></iframe></center>
<center>Explosion view of assembly process</center>

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/uURoJApO9Ro" frameborder="0" allowfullscreen></iframe></center>
<center>Manual flight test</center>

___

<a name = "software"></a>

### Software Modules

**ROS Hierachy**

Software is the core of the whole project, as the brain to a human. According to the platform, an Intel Up-board is the main CPU for higher level intelligence. The output of sensors laser scanner and front-facing RGBD-camera Intel Realsense, are all directed into Intel Up-board for further processing. Below video is the handheld platform with a Realsense camera. ORB-SLAM is running onboard on ROS kinetic version. For laser scanner, Google SLAM or hector SLAM is used for this project. The future work will be fusion of multiple software node pose estimation results, along with the inertia measurements.

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/srzCYUnKaMo" frameborder="0" allowfullscreen></iframe></center>
<center>Hand held platform SLAM result with <a href="http://webdiis.unizar.es/~raulmur/orbslam/">[ORB-SLAM]</a></center>

Modules list:

1. Flight controller firmware are processed on the MCU STM32F427, which necessary topics published to serial port and further to USB port of the upper level CPU.
2. In the upper level CPU Up-board, the whole system is running on ROS in Ubuntu system. ROS nodes are inter-connected to share information.
3. Application layer handles the user defined missions and state change conditions. The API layer defines necessary and basic functions such as takeoff and landing, fly to waypoint or fly a certain distance. SLAM and path planning layer includes the SLAM and planning nodes subscribing raw sensor information (laser scans and raw images) and publishing reference position points. Obstacle avoidance is also handled in this node where a local/global map is maintained for planning and loop closure purpose.
4. MAVROS is the interface between ROS and MAV platform using protocol Mavlink. 

<center>
<img src="/public/figures/project/uavsystem_1.jpg" style="width:70%">
</center>

___
 
<a name = "fpga"></a>

### FPGA Stereo Vision

Field programmable gate array extends the ability of image processing by parallel processing and line synchronization. We use Xlinix Zync7020 supporting for dual-cemera drivers with high resolution and image pre-processing. Depth map estimation based on epi-polar geometry and ORB feature extraction are developed on this module. Further development of communication between FPGA module and Intel Upboard is still under progress. This module will replace the Intel Realsense as the forward facing vision system. The large view angle and high frame rate will enable fast processing, i.e. fast flight capability in dynamic environment.

___


<a name = "safmc"></a>

### Sub-project1: SAFMC-2017

**Introduction**

The platform InstinCT is specially designed for GPS-denied environment navigation, catering for applications in unknown and realisitic scenarios. With different configuration of Lidar and visual sensors, we first demonstrated our capability in 2017 Singapore Amazing Flying Machine Competition category D2, the fully autonomous category, with the hexacopter drone performing autonomous navigation with a 30-meter Hokuyo laser range finder. This video shows the preparation of the competition, where all the efforts done are based on our group member's research work, on mission management, lidar SLAM, path planning and trajectory generation, state fusion, communication, flight control, and hardware integration. Thanks to the integration of Google cartographer, a lidar based SLAM, providing high frequency updating rate, loop closure detection and low computational consumption. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/TZbpOoGi-JE" frameborder="0" allowfullscreen></iframe></center>
<center>Autonomous flight performance</center>

**Real Competition Scenario**

The actual challenge includes several scoring points: 
1. autonomous take-off;
2. entering building through window;
3. flying through corridors;
4. chemical sampling at an unknown location through visual detection;
5. identify casualty's name tag through on-board camera;
6. enter and identifying personnel in dark room;
7. passing through array of poles and a fan to emulate windy condition;
8. visual guided precise landing. 
The NUS UAV team completes all of the missions and awarded the championship. 

<center><iframe width="560" height="315" src="https://www.youtube.com/embed/l_Ys-ouD7VM" frameborder="0" allowfullscreen></iframe></center>
<center>Autonomous flight performance</center>