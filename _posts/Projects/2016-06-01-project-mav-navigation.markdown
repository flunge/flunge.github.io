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

This module provides power flight control features for general UAV platform use: multi-rotor platforms, single/coaxial rotor helicopter, unconventional aircrafts as tail-sitters and hybrids. The design extends its capability with all necessary signals connected to a customized connector, making it transportable to any extenion board with same connector type or even multiple identical flight controllers for redundancy purpose.