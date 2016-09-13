---
layout: post
title:  "ZED Stereo Camera Setup and Practice on Jetson TK1"
date:   2016-08-23
categories: Technical
tags: [Jetson TK1, ZED Camera]
---

### Summary

As the name given, ZED Stereo Camera(ZED) is a stereo camera produced by [Steteolabs](https://www.stereolabs.com/). Basically, ZED is able to capture high-resolution pictures and depth perception. For details, please refer to the official website. In this article, the installation and a simple practice example of ZED is provided. Again, all the produces are based on Ubuntu 14.04.

### Contents

1. [Setup of ZED on TK1](#Setup of ZED camera)
2. [Capture picture and depth map](#Capture picture and depth map)

___
<a name = "Setup of ZED camera"></a>
### Part 1. Setup of ZED camera

The installation of ZED on TK1 is actually quite straightforward. The [official instruction: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/) is well written. Just follow the steps and everything should be done. Here is a quick summary for all steps. There might be one thing that you need to 

*Requirement: (refer to [here](https://huangying-zhan.github.io/2016/08/15/Caffe-installation-and-practice-on-Jetson-TK1.html#title4))*

* CUDA 6.5 R.21
* openCV4tegra 2.4.10

1. Enable USB3.0
	
    ZED Camera requires a USB3.0 port. TK1 has only one USB3.0 port. Make good use of it~

    ```
    sudo vi /boot/extlinux/extlinux.conf
    # Replace ‘usb_port_owner_info=0‘ by ‘usb_port_owner_info=2‘.
    # Save and exit (*:wq*)
    ```

2. Download and install ZED SDK for Jetson

	Visit [ZED download page](https://www.stereolabs.com/developers/#download_anchor) and download ZED SDK for Jetson, which is a *.run* file
    
    ```
    chmod +x ZED_SDK_JTK1_v*.run
	./ZED_SDK_JTK1_v*.run
    # Accept the statement and follow installation instruction.
    ```

	Now, ZED SDK should be installed and there are many interesting demos. The SDK is installed at `/usr/local/zed` by default. However, before running these examples, you might encounter a problem, there is only one USB port on TK1. It is not enought for your keyboard, mouse, and ZED. Unless you have a USB3.0 hub, you need [remote control](https://huangying-zhan.github.io/2016/09/13/Linux-cheat-sheet.html#Remote) TK1 from your computer. 

<br></br>
___

<a name="Capture picture and depth map"></a>
### Part 2. Capture picture and depth map
    

### Reference

* [e-CAM40_CUMI4682_MOD - 4 MP OV4682 RGB IR Camera Module](https://www.e-consystems.com/OV4682-RGB-IR-MIPI-CAMERA-Module.asp)

* [official blog: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/)    