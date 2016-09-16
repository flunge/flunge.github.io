---
layout: post
title:  "UAV Detection"
date:   2016-08-29
categories: Research
tags: [Paper, UAV, Detection, DeepLearning]
---

### Summary

To be edited.

### Contents

1. Setup py-faster-rcnn
2. Training
3. Testing
4. Error and solution

___

### Part 1. Setup py-faster-rcnn

Mainly refer to [py-faster-rcnn].


<br></br>

___

### Part 2. Training

Train original VOC dataset

#### 2.1. Prepare dataset and ConvNet model (initialization)

Download VOC dataset

```
cd $FRCN_ROOT/data
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCtrainval_06-Nov-2007.tar
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCtest_06-Nov-2007.tar
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCdevkit_08-Jun-2007.tar

tar xvf VOCtrainval_06-Nov-2007.tar
tar xvf VOCtest_06-Nov-2007.tar
tar xvf VOCdevkit_08-Jun-2007.tar 
ln -s VOCdevkit VOCdevkit2007 #create a softlink
```

#### 2.2. Training

```
cd $FRCN_ROOT
./experiments
```

<br></br>

___
### Part 3. Testing

#### 3.1. Summary

#### 3.2. ZED practice
[Hello World](https://www.stereolabs.com/blog/index.php/2015/07/15/hello-world/)

Hello world problem: 
init function not found
Since ZED SDK is updated, init() is changed to sl::zed::InitParams structure
Therefore, to initialize ZED, 
    sl::zed::InitParams params;

#### 3.3. Read from ZED
[ZED save depth](https://github.com/stereolabs/zed-save-depth)

Problem and solution

utility.hpp is not found
    include <opencv2/gpu/device/utility.hpp>


#### 3.4. How to use
There are various setups provided by the module.

* --gpu or --cpu (default gpu)
* --net
    * zf (default)
    * vgg16
* --mode
    * 0: Export Mode (only export numerical information of bbox and depth  (default)
    * 1: visualization
* --class
    * [...] (class indexes, default 15)
* --img_source
    * 0: Online Mode (load same image, default)
    * 1: Offline Mode (load a set of images)

<br></br>
___

### Part 4. Error and solution

1. error: command ‘arm-linux-gnueabihf-gcc’ failed with exit status 1
    
	```
    vim nms/gpu_nms.cpp
    # move to line 1617, change the following line to another line
    _nms((&(__Pyx_BufPtrStrided1d(__pyx_t_5numpy_int32_t *
    ->
    _nms((&(__Pyx_BufPtrStrided1d(int*
    ``` 

    Update nms/gpu_nms.pyx in ext_modules in setup.py to nms/gpu_nms.cpp

2. no easydict, cv2

    ```
    sudo pip install easydict
    sudo apt-get install libopencv4tegra-python
    ```

3. roi_pooling_layer.cu:91 check failed: error == cudaSuccess(8 vs 0)

	change this line: `__C.USE_GPU_NMS = True` to `__C.USE_GPU_NMS = False` in py-faster-rcnn/lib/fast_rcnn/config.py

### Reference

[py-faster-rcnn]: https://github.com/rbgirshick/py-faster-rcnn

[Error and Solution]: http://blog.csdn.net/jiajunlee/article/details/50373815