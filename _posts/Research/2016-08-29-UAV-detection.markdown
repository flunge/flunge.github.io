---
layout: post
title:  "UAV & Detection"
date:   2016-08-29
categories: Research
tags: [Paper, UAV, Detection, DeepLearning]
---

### Summary

To be edited.

### Contents

1. [Setup py-faster-rcnn](#Setup py-faster-rcnn)
2. [Training](#Training)
3. [Testing](#Testing)
4. [Error and solution](#Error and solution)

___

<a name = "Setup py-faster-rcnn"></a>

### Part 1. Setup py-faster-rcnn

Mainly refer to [py-faster-rcnn]. The official instruction is well written and easy to follow. 

1. Clone the Faster R-CNN repo
	
    ```
	# Make sure to clone with --recursive
	git clone --recursive https://github.com/rbgirshick/py-faster-rcnn.git
    ```

2. Lets call the directory into `FRCN_ROOT`

3. Build the Cython modules

    ```
    cd $FRCN_ROOT/lib
	make
    ```
    
4. Build Caffe and PyCaffe
	
    For this part, please refer to [Caffe official installation instruction](http://caffe.berkeleyvision.org/installation.html) or my post about [Caffe installation](https://huangying-zhan.github.io/2016/09/09/GPU-and-Caffe-installation-in-Ubuntu.html#Caffe%20installation)
	If you have experience with Caffe, just follow the code at below.
    
    ```
	cd $FRCN_ROOT/caffe-fast-rcnn
    cp Makefile.config.example Makefile.config
    # Modify Makefile.config, uncommment this line
    WITH_PYTHON_LAYER := 1
    # Modifiy Makefile.config according to your need, such as setup related to GPU support, cuDNN, CUDA version, Anaconda, OpenCV, etc.
    
    # After modification on Makefile.config
    make -j4 # 4 is the number of core in your CPU, change it according to your computer CPU  
    # Suppose your have installed prerequites for PyCaffe, otherwise, go back to installation instructions.
    make pycaffe -j4
    ```
    
5. Download pre-computed Faster R-CNN dtectors

	```
    cd $FRCN_ROOT
	./data/scripts/fetch_faster_rcnn_models.sh
    ```

6. Run the demo
	However, in this part you might get into trouble with different errors, such as without some packages. At the end of this post, some encountered errors and solution are provided. For those unexpected error, google and you should be able to find a solution.
    
	```
    ./tools/demo.py
    ```

<br></br>

___

<a name = "Training"></a>

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

<br></br>

#### 2.2. Training

```
cd $FRCN_ROOT
./experiments
```

<br></br>

___

<a name = "Testing"></a>

### Part 3. Testing

#### 3.1. Summary

<br></br>

#### 3.2. ZED practice
[Hello World](https://www.stereolabs.com/blog/index.php/2015/07/15/hello-world/)

Hello world problem: 
init function not found
Since ZED SDK is updated, init() is changed to sl::zed::InitParams structure
Therefore, to initialize ZED, 
    sl::zed::InitParams params;

<br></br>

#### 3.3. Read from ZED
[ZED save depth](https://github.com/stereolabs/zed-save-depth)

Problem and solution

utility.hpp is not found
    include <opencv2/gpu/device/utility.hpp>

<br></br>

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

<a name = "Error and solution"></a>

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
    # Without Anaconda
    sudo pip install easydict
    sudo apt-get install python-opencv
    
    # With Anaconda
    conda install opencv
    conda install -c auto easydict
    ```

3. roi_pooling_layer.cu:91 check failed: error == cudaSuccess(8 vs 0)

	change this line: `__C.USE_GPU_NMS = True` to `__C.USE_GPU_NMS = False` in py-faster-rcnn/lib/fast_rcnn/config.py

4. libcudart.so.8.0: cannot open shared object file: No such file or directory
	
    	sudo ldconfig /usr/local/cuda/lib64


### Reference

[py-faster-rcnn]: https://github.com/rbgirshick/py-faster-rcnn

[Error and Solution]: http://blog.csdn.net/jiajunlee/article/details/50373815