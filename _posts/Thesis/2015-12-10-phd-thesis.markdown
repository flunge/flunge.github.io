---
layout: post
title:  "Ph.D. Thesis"
date:   2015-12-10
categories: Thesis
tags: [Thesis]
---

| Title  | <a href="https://drive.google.com/open?id=0B6qEpC0tNfZXTXZwWG5CSElhVEk">Navigation and Autonomous Control of MAVs in GPS-deined Environments</a> |
|--------|---|
| Author | LI Kun |
| Supervisors | Prof. Ben M. Chen & Prof. Tong H. Lee |
| Year   | 2015  |

<br>

**Summary**

This thesis presents an autonomous navigation and control solution of a fully customized micro aerial vehicle (MAV) in global positioning system (GPS)-denied environments. To achieve the best integration and efficiency, key modules of the MAV system have been investigated and optimized iteratively, including mechanical frame, propulsion system, electrical motor speed controller, flight controller, communication module, customized sensors, and so on. Starting from the basic working principles, these modules are developed to be fully functional with light weight, high efficiency and high reliability properties. In addition, an optical-flow module and a video streaming module are also incorporated into the whole system for navigation in GPS-denied environments. Furthermore, a palm-size quad-rotor nano aerial vehicle (NAV) with gross take-off weight around 40 g is developed for navigation in more confined environments following the design methodologies of MAV with reduced systems. Subsequently, with a working platform, a nonlinear model is derived for autonomous control to achieve robust attitude loop and position loop performance from corresponding sensing feedbacks. To achieve robust motion estimation, optical flow algorithms have been developed using both pixel intensity and image feature methods. Pinhole camera is modeled with which the translational velocities in 3D real world can be calculated from the 2D image flow information. Moreover, research on monocular vision-based monocular simultaneous localization and mapping (SLAM) is carried out with software development based on open-source embedded Linux and Gstreamer. SLAM algorithm has been actualized running on ROS in GCS. A vision-based target tracking algorithm has been developed for the MAV and tested in an application of rooftop landing. Vision-aided target searching and detection are also included for object recognition.

**Contents**

1. Introductions <br>
1.1 An Introduction to State-of-art UAV Platforms
1.2 An Introduction to UAV Sensing Technologies 
1.3 An Introduction to UAV Navigation Techniques
1.4 Contribution of the Thesis
2. MAV Platform and Hardware System
2.1 Task Description
2.2 Mechanical Design
2.3 BLDC Motors Control Scheme
2.4 Propulsion System Design
2.5 Avionic System Design
2.6 Wireless Communication Module
2.7 Optical-flow Module Hardware Design
2.8 Monocular Vision Module
2.9 NAV Platform Design
3. Dynamic Modeling and Control
3.1 Mathematical Nonlinear Model
3.2 Inner-loop Attitude Control
3.3 Outer-loop Position Control
4. Vision-aidedLocomotionEstimation
4.1 Motion Estimation Using Optical Flow 
4.2 Experimental Results 
4.3 NAV Autonomous Control 
5. Mono-CameraSimultaneousLocalizationandMapping
5.1 Video Streaming Firmware
5.2 Feature Extraction for SLAM
5.3 Monocular SLAM
5.4 Results
6. Vision-aided Outdoor Navigation of MAV and DigitRecognition 
6.1 System Overview
6.2 Rooftop Landing Vision Algorithm
6.3 Digit Detection Algorithm
6.4 Flight Test Results
7. Conclusion and Future Works

**Defense Slides**

Below is the oral defense slides on Oct 5th, 2015.

<center><iframe src="https://docs.google.com/presentation/d/1ZsnGcj0aYxw_Q_3VVekEhx3H7HrBXD5JBA3nuaIUe9g/embed?start=false&loop=false&delayms=3000" frameborder="0" width="960" height="749" allowfullscreen="true" mozallowfullscreen="true" webkitallowfullscreen="true"></iframe></center>