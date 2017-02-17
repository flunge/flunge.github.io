---
layout: post
title:  "Caffe Installation and Practice on Jetson TK1"
date:   2016-08-16
categories: TechNote
tags: [Caffe, JetsonTK1]
---

### Summary

Jetson Tegra-K1([TK1]) is an embedded system provided by NVIDIA. It is designed for applications involving GPU computing, such as deep learning. While [Caffe] is a deep learning framework developed by Berkeley Vision and Learning Center (BVLC). This article records the procedures for installation of Caffe on TK1 and a simple implementation example, a real-time handwritten digit recognition system ([LeNet]). All the procedures are based on Ubuntu 14.04.

<center>![tk1](https://cloud.githubusercontent.com/assets/13748721/19178013/67c98378-8c81-11e6-90d5-236392c34759.png)</center>
<center><u>Jetson TK1</u></center>

___

### Contents

1. [Caffe installation on TK1](#Caffe installation on TK1)
2. [Real-time handwritten digit recognition on TK1](#Real-time handwritten digit recognition on TK1)

___
<a name="Caffe installation on TK1"></a>
### Part 1. Caffe installation on TK1

#### 1.1. Remote access TK1

Remote accessing TK1 is not a compulsory procedure to operate TK1, provide that you have prepared necessary computer accessories, including a display monitor, a keyboard and mouse. However, if you prefer using your computer to operate TK1 remotely, there are many ways to do this. Here is a simple way using *ssh* service.

General speaking, you need to setup a ssh server on TK1 first, and then access TK1 from your own computer. Now, suppose your TK1 is connected to internet via ethernet, follow the [instruction](https://huangying-zhan.github.io/2016/09/13/Linux-cheat-sheet.html#Remote) to remote access TK1 from your computer

<br></br>

#### 1.2. Install prerequisites for Caffe

Now, we need to install some prerequisites for Caffe, including,

+ General dependencies
+ CUDA for ARM package
+ OpenCV for Tegra

1. Install  general dependencies for Caffe

    ```
    $ sudo add-apt-repository universe
    $ sudo apt-get install libprotobuf-dev protobuf-compiler gfortran \
    $ libboost-dev cmake libleveldb-dev libsnappy-dev \
    $ libboost-thread-dev libboost-system-dev \
    $ libatlas-base-dev libhdf5-serial-dev libgflags-dev \
    $ libgoogle-glog-dev liblmdb-dev gcc-4.7 g++-4.7 \
    $ libboost-all-dev
    ```

2. Install CUDA package

	Visit [NVIDIA's developer page for Tegra] and download *CUDA 6.5 Toolkit for L4T Rel 21.x*. Let's make directory on Desktop to store all downloaded package. The installation is based on the official [CUDA for Jetson installation instruction]. If there is any unexpected problem, please refer to the official instruction.

    ```
    $ mkdir /home/ubuntu/Desktop/packages_for_caffe
    $ cd /home/ubuntu/Desktop/packages_for_caffe

    $ sudo dpkg -i cuda-repo-l4t-r21.2-6-5-prod_6.5-34_armhf.deb
    $ sudo apt-get update
    $ sudo apt-get install cuda-toolkit-6-5
    $ sudo usermod -a -G video $USER
    
    $ echo "# Add CUDA bin & library paths:" >> ~/.bashrc
    $ echo "export PATH=/usr/local/cuda/bin:$PATH" >> ~/.bashrc
    $ echo "export LD_LIBRARY_PATH=/usr/local/cuda/lib:$LD_LIBRARY_PATH" >> ~/.bashrc
    $ source ~/.bashrc
    ```

	After installation of CUDA, run `nvcc -V` to check whether everything is installed correctly. 
    CUDA 6.5 should be installed.

3. Install OpenCV for TK1

	Now, we can install OpenCV for Jetson. The installation is also based on the official [OpenCV for Jeton installation guideline]. Again, refer to the page if there is any problem. Before installation, visit [NVIDIA's developer page for Tegra] again and download *OpenCV4Tegra for L4T 21.x*.

    ```
    $ cd /home/ubuntu/Desktop/packages_for_caffe

    $ sudo dpkg -i libopencv4tegra-repo_l4t-r21_2.4.10.1_armhf.deb
    $ sudo apt-get update
    $ sudo apt-get install libopencv4tegra libopencv4tegra-dev
    ```

<br></br>

#### 1.3. Install Caffe and PyCaffe

In this part, we are finally going to download and install Caffe! First, make sure you have installed git `sudo apt-get install git`. PyCaffe is the Python interface for Caffe. For Caffe installation, there might be some unexpected errors. Please try to google the error. There must be other people encounted same error as you. Specifically, you can refer to the [Caffe Google group](https://groups.google.com/forum/#!forum/caffe-users) or [Caffe Github](https://github.com/BVLC/caffe/issues) and look for a solution to your problem.

1. Clone and Complie Caffe

    ```
    # Suppose you are going to install Caffe on Desktop
    $ cd /home/ubuntu/Desktop
    $ git clone https://github.com/BVLC/caffe.git
    $ cd $CAFFE # From now on, for simplicity, $CAFFE refers to Caffe's directory
    $ cp Makefile.config.example Makefile.config
    $ sudo apt-get install gcc-4.6 g++-4.6 gcc-4.6-multilib g++-4.6-multilib
    $ sed -i "s/# CUSTOM_CXX := g++/CUSTOM_CXX := g++-4.6/" Makefile.config

    $ make all -j4
    $ make test -j4
	# After installation, runtest to test Caffe layers.
    $ make runtest -j4
    # Run a benchmark test to check again.
    $ build/tools/caffe time --model=models/bvlc_alexnet/deploy.prototxt --gpu=0
    ```

2. Install Python related package

    ```
    $ cd $CAFFE/python
    $ sudo apt-get install python-pip
    $ for req in $(cat requirements.txt); do sudo pip install $req; done
    $ cd ../
    $ make all
    $ sudo apt-get install python-numpy
    $ make pycaffe
    ```

Up to this stage, if you didn't encounter any error. Caffe is installed on TK1! 

<br></br>
___

<a name = "Real-time handwritten digit recognition on TK1"></a>
### Part 2. Real-time handwritten digit recognition

In this part, we will see how to train a classical convolutional neural network ([LeNet]) on TK1 and implement a handwritten digit recognition system in real-time. Actually, TK1 is not designed for deep neural network training due to its hardware limits. It is more likely an embedded device for implementation of trained neural network models. Therefore, **DON'T TRAIN** other deep neural networks on TK1. However, our ultimate goal is to build a real-time recognition system using TK1. We certainly need a trained model.

For the preparation of dataset and network training, basically, follow the tutorial of [MNIST example](http://caffe.berkeleyvision.org/gathered/examples/mnist.html) in Caffe official page.

#### 2.1.  Train LeNet

1. Prepare dataset

    ```
    $ cd $CAFFE
    $ ./data/mnist/get_mnist.sh
    $ ./examples/mnist/create_mnist.sh
    ```

2. Train LeNet
	This step takes about 15 minutes. Go and make a cup of coffee first~
    
    ```
    $ cd $CAFFE_ROOT
    $ ./examples/mnist/train_lenet.sh # The trained model is stored in $CAFFE/example/mnist/ and named *lenet_iter_10000.caffemodel*
    ```
    
	Now, LeNet model is ready for use!

<br></br>

#### 2.2. Real-time recognition

A simple [end-to-end-digit recognition][end_to_end_digit_recognition] written by Python is provided for testing LeNet. However, make sure that you are using a white paper and the digit written on the paper is large enough. If the digit is too small / lines are too thin, the system might not be able to recognize the digit correctly. Before the details of real-time implementation, we try to recognize a digit in a single picture first.

1. Take a photo and store as $CAFFE/data/mnist/sample_digit.png
2. Run `python end_to_end_digit_recognition.py`

To make this as a real-time implementation, there are many ways, such as reading captured image from camera or reading a locally saved  picutre from time to time. The later one is implemented since it suits to different cameras. Basically, the idea is,

1. Use a camera to capture and save pictures from time to time
2. The saved picture must be stored in same directory and same name, i.e. *sample_digit.png*
3. `end_to_end_digit_recognition.py` reads the picture from time to time.

Here is a simple demo video.

<iframe width="427" height="240" src="https://www.youtube.com/embed/5_aONXUhKbE" frameborder="0" allowfullscreen></iframe>

<br></br>


### Reference


[Run caffe on TK1](https://petewarden.com/2014/10/25/how-to-run-the-caffe-deep-learning-vision-library-on-nvidias-jetson-mobile-gpu-board/)

[CUDA for Jetson installation instruction]: http://elinux.org/Jetson/Installing_CUDA

[OpenCV for Jeton installation guideline]: http://elinux.org/Jetson/Installing_OpenCV

[NVIDIA's developer page for Tegra]: https://developer.nvidia.com/linux-tegra-rel-21

[MNIST LeNet example]: http://caffe.berkeleyvision.org/gathered/examples/mnist.html

[LeNet]: http://yann.lecun.com/exdb/lenet/

[end_to_end_digit_recognition]: https://www.dropbox.com/s/dbbaeoddwfg4cfg/end_to_end_digit_recognition.py?dl=0

[TK1]: http://www.nvidia.com/object/tegra-k1-processor.html

[Caffe]: http://caffe.berkeleyvision.org/