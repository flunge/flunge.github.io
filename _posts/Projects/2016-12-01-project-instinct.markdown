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
4. [ORB SLAM](#orbSlam)

___

<a name = "flightController"></a>

**Summary**

This module provides power flight control features for general UAV platform use: multi-rotor platforms, single/coaxial rotor helicopter, unconventional aircrafts as tail-sitters and hybrids. The design extends its capability with all necessary signals connected to a customized connector, making it transportable to any extenion board with same connector type or even multiple identical flight controllers for redundancy purpose.

<div id="row">
<img src="/public/figures/project/instinct_fc_1.JPG">
<img src="/public/figures/project/instinct_fc_2.JPG">
</div>

**Key Features**

General Information:

1. Layers: 8-layer PCB with 1 mm thickness. 
2. Dimension: 36 mm X 22 mm.
3. Main processor: STM32F427AIH6.
4. Necessary peripherals: minimum system, FRAM, I2C buffer, UART buffer, status LED, power regulator.
5. Signals 
