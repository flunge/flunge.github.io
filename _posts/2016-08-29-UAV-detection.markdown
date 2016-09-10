---
layout: post
title:  "UAV Detection (Faster R-CNN)"
date:   2016-08-29
categories: UAV_Tasks
tags: Paper UAV Detection Deep_Learning Faster_R-CNN
---


________________________________________
## Setup

Mainly refer to [py-faster-rcnn].

[Error and solution]

### error: command ‘arm-linux-gnueabihf-gcc’ failed with exit status 1

Solution:

    vim nms/gpu_nms.cpp


```
#move to line 1617, change the following line to another line
_nms((&(__Pyx_BufPtrStrided1d(__pyx_t_5numpy_int32_t *, 
->
_nms((&(__Pyx_BufPtrStrided1d(int*
``` 

Update nms/gpu_nms.pyx in ext_modules in setup.py to nms/gpu_nms.cpp

no easydict, cv2
sudo pip install easydict
sudo apt-get install libopencv4tegra-python

roi_pooling_layer.cu:91 check failed: error == cudaSuccess(8 vs 0)
change this line: __C.USE_GPU_NMS = Ture to __C.USE_GPU_NMS = False in py-faster-rcnn/lib/fast_rcnn/config.py

________________________________________

## Train original VOC dataset

### Prepare dataset and ConvNet model (initialization)

Download VOC dataset
```
cd $FRCN_ROOT/data
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCtrainval_06-Nov-2007.tar
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCtest_06-Nov-2007.tar
wget http://host.robots.ox.ac.uk/pascal/VOC/voc2007/VOCdevkit_08-Jun-2007.tar

tar xvf VOCtrainval_06-Nov-2007.tar
tar xvf VOCtest_06-Nov-2007.tar
tar xvf VOCdevkit_08-Jun-2007.tar

# create a softlink
ln -s VOCdevkit VOCdevkit2007
```

### Training
```
cd $FRCN_ROOT
./experiments
```

___________________________________________
## Testing

### Main idea

### ZED practice
[Hello World](https://www.stereolabs.com/blog/index.php/2015/07/15/hello-world/)
#### Hello world
init function not found
Since ZED SDK is updated, init() is changed to sl::zed::InitParams structure
Therefore, to initialize ZED, 
    sl::zed::InitParams params;


### Read from ZED
[ZED save depth](https://github.com/stereolabs/zed-save-depth)

Problem and solution

utility.hpp is not found
    include <opencv2/gpu/device/utility.hpp>


## How to use
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
* --imge_source
    * 0: Online Mode (load same image, default)
    * 1: Offline Mode (load a set of images)

[py-faster-rcnn]: https://github.com/rbgirshick/py-faster-rcnn

[Error and Solution]: http://blog.csdn.net/jiajunlee/article/details/50373815