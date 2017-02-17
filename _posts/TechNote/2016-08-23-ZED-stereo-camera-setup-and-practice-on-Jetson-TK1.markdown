---
layout: post
title:  "ZED Stereo Camera Setup and Practice on Jetson TK1"
date:   2016-08-23
categories: TechNote
tags: [JetsonTK1, ZEDCamera]
---

### Summary

As the name given, ZED Stereo Camera(ZED) is a stereo camera produced by [Steteolabs](https://www.stereolabs.com/). Basically, ZED is able to capture high-resolution pictures and depth perception. For details, please refer to the official website. In this article, the installation and a simple practice example of ZED is provided. Again, all the produces are based on Ubuntu 14.04.

### Contents

1. [Setup of ZED on TK1](#Setup of ZED camera)
2. [Capture picture and depth map](#Capture picture and depth map)
3. [Detection with Depth](#Detection with Depth)

___
<a name = "Setup of ZED camera"></a>
### Part 1. Setup of ZED camera

The installation of ZED on TK1 is actually quite straightforward. The [official instruction: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/) is well written. Just follow the steps and everything should be done. Here is a quick summary for all steps. 

*Requirement: (refer to [here](https://huangying-zhan.github.io/2016/08/16/Caffe-installation-and-practice-on-Jetson-TK1.html#Caffe%20installation%20on%20TK1))*

* CUDA 6.5 R.21
* openCV4tegra 2.4.10

Now, let's start!

1. Enable USB3.0
	
    ZED Camera requires a USB3.0 port. TK1 has only one USB3.0 port. Make good use of it~

    ```
    $ sudo vi /boot/extlinux/extlinux.conf
    # Replace ‘usb_port_owner_info=0‘ by ‘usb_port_owner_info=2‘.
    # Save and exit (*:wq*)
    ```

2. Download and install ZED SDK for Jetson

	Visit [ZED download page](https://www.stereolabs.com/developers/#download_anchor) and download ZED SDK for Jetson, which is a *.run* file
    
    ```
    $ chmod +x ZED_SDK_JTK1_v*.run
	$ ./ZED_SDK_JTK1_v*.run
    # Accept the statement and follow installation instruction.
    ```

	Now, ZED SDK should be installed and there are many interesting demos. The SDK is installed at `/usr/local/zed` by default. However, before running these examples, you might encounter a problem, there is only one USB port on TK1. It is not enough for your keyboard, mouse, and ZED. Unless you have a USB3.0 hub, you need to [remote control](https://huangying-zhan.github.io/2016/09/13/Linux-cheat-sheet.html#Remote) TK1 from your computer. 

<br></br>
___

<a name="Capture picture and depth map"></a>
### Part 2. Capture picture and depth map

#### 2.1. Summary
To study ZED, we can learn from it's [blog examples](https://www.stereolabs.com/blog/) or study the [Github examples](https://github.com/stereolabs). Basically, the examples are the same. Blog examples provide more detailed explanations but some parts of the code are quite outdated. The reason is that ZED released Ver.1.0 and made some changes. The blog examples were written before Ver.1.0. Nevertheless, Github examples provide update codes. In summary, study both at the same time should be more efficient. 

<br></br>

#### 2.2. Hello World
Before jumping to the later content, a simple ["Hello-world" example](https://www.stereolabs.com/blog/index.php/2015/07/15/hello-world/) is suggested to be implemented by yourself first. Follow the instruction and build a Hello-World program. However, as mentioned before, the blog examples are quite outdated. Please use this [main-hello-world.cpp](https://www.dropbox.com/s/i9zhg15stjfgp5u/main-hello-world.cpp?dl=0) and [CMakeLists.txt](https://www.dropbox.com/s/uoe0iwjp582klq0/CMakeLists.txt?dl=0) to build the program. Remember to rename *main-hello-world.cpp* as *main.cpp*.

<br></br>

#### 2.3. Capture pictures and depth maps
Suppose you have built your `Hello World`. In this part, we will see a simple modification based on a ZED's [OpenCV example](https://github.com/stereolabs/zed-opencv). The ultimate goal is to capture RGB pictures, their corresponding dispartiy image and depth map from time to time. First, let's have a taste on the original example.

```
$ cp /usr/local/zed/sample/cpu/with\ OpenCV ~/Desktop/zed_capture #copy and rename the example to desktop
$ cd $zed_capture # For simplicity, $zed_capture represents the full directory of /zed_capture
$ mkdir build
$ cd build
$ cmake ..
$ make # If you can see "Linking CXX executable "ZED with OpenCV" ", the program is built sucessfully
$ ./ZED\ with\ OpenCV
```

Play around with the program first. Then, download and rename [main-capture.cpp](https://www.dropbox.com/s/g2g7m0flsubfe5v/main_capture.cpp?dl=0) as *main.cpp*.
Now, replace the original *main.cpp* by this new *main.cpp* and build the program again.

```
$ cd $zed_capture/build
$ make
$ ./ZED\ with\ OpenCV
```

This program allows you to save images, disparity images and depth maps from time to time. However, there are some settings you can modify in the *main.cpp*. Please refer to *main setup parameters* at the beginning of the code. After modification, you have to build the program again.


<br></br>
___

<a name="Detection with Depth"></a>

### Part 3. Detection with Depth

In this part, we are going to use both RGB images and depth maps in a detection algorithm. The detection algorithm is [Faster R-CNN](https://github.com/rbgirshick/py-faster-rcnn). Download and install py-faster-rcnn first by following the official guideline or Part 1 in [my post](https://huangying-zhan.github.io/2016/09/22/detection-faster-rcnn.html). 

General speaking, the goal of this part is to find out the distance from the camera of detected objects. We also need this [detection_depth_multiple.py](https://www.dropbox.com/s/o3hboq7svgm1reh/detection_depth_multiple.py?dl=0). Save the script in `py-faster-rcnn/tools/`. This scipt is designed for VOC dataset only. However, making simple modifications can make this script works for other detection task under py-faster-rcnn framework.

Suppose you save RBG images at `$rgb_img_dir` and depth maps at `$depth_map_dir`. 

1. Update directories in line 210, 211 in `detection_depth_multiple.py`.

2. Usage

	```python
    ./detection_depth_multiple.py [options]
    options:
    --gpu [GPU_ID]: use gpu mode and select the GPU id.
    --cpu : use cpu mode
    --net [zf / vgg]: select the network and corresponding model, e.g. zf, vgg
    --image_source [0 / 1]: there are two kinds of input source mode. Mode 0 means online loading, which loads same rgb image and depth map from the directories. Mode 1 is offline loading mode. It loads a set of images.
    --mode [0 / 1]: There are two modes. Mode 0 only exports numerical information, including bounding boxes coordinates and depth; Mode 1 visualizes the result.
    --class [CLASS_ID, ..., CLASS_ID]: select the class indexs that you are going to detect. In VOC dataset, there are 20 classes.
    
    # Example: gpu mode, zf net, offline loading, output visualization, 15th class is interested
    ./detection_depth_multiple.py --gpu 0 --net zf --image_source 1 --mode 1 --class [15]
    ```




### Reference


[official blog: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/)    