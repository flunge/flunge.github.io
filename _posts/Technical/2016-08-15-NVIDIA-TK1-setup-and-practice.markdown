---
layout: post
title:  "NVIDIA-TK1 Setup"
date:   2016-08-15
categories: Technical
tags: [Hardware Setup, NVIDIA TK1, MNIST]
---

### Summary

Tegra-K1(TK1) is an embedded system provided by NVIDIA, it is designed for applications involving GPU computing, such as deep learning. This article records the procedures for setting up TK1 and a simple implementation example, a handwritten digit recognition system ([LeNet](http://yann.lecun.com/exdb/lenet/)).

___

### Contents

1. TK1 Setup
2. LeNet (MNIST) example

___

### Part 1. TK1 Setup

#### 1.1. Remote access to TK1

Remote access to TK1 is not a compulsory procedure to operate TK1, provide that you have prepared necessary computer accessories, including a display monitor, a keyboard and mouse. However, if you prefer using your computer to operate TK1 remotely, there are many ways to do this. Here is a simple way using *ssh* service.
General speaking, you need to setup a ssh server on TK1 first, and then access to TK1 from your own computer.

1. Open a terminal on TK1 and install ssh server on TK1 


	sudo apt-get install openssh-server


2. Check server setup

    ps -e|grep ssh #If similar message, *"5313 ? 00:00:00 sshd"*, appeared, ssh server is set up successfully.

3. Check IP address of TK1 network

 1. click network->connection information
 2. check IP address at IPv4

Remote access TK1 from your PC, suppose the IP address of TK1 is 172.16.134.90. 

Enter the following command in your PC's terminal.

    ssh ubuntu@172.16.134.90
    
The default password is "ubuntu".


# Install necessary packages in TK1

### Install system packages need for Caffe

```
sudo add-apt-repository universe
sudo apt-get install libprotobuf-dev protobuf-compiler gfortran \
libboost-dev cmake libleveldb-dev libsnappy-dev \
libboost-thread-dev libboost-system-dev \
libatlas-base-dev libhdf5-serial-dev libgflags-dev \
libgoogle-glog-dev liblmdb-dev gcc-4.7 g++-4.7 \
libboost-all-dev
```

_suppose we make a directory in Desktop to store all downloaded package_

    mkdir /home/ubuntu/Desktop/packages_for_caffe
    cd /home/ubuntu/Desktop/packages_for_caffe

### Install CUDA package

To install CUDA, you first need to register to nVidia's [embedded developer program](https://developer.nvidia.com/gameworks-registered-developer-program%20on%20your%20main%20machine) and download [CUDA package](https://developer.nvidia.com/rdp/assets/cuda-l4t-r192) to your local machine. 


Start a new terminal on PC, then copy the package to TK1.

    scp cuda-repo-l4t-r19.2_6.0-42_armhf.deb  ubuntu@172.16.134.90://home/ubuntu/Desktop/packages_for_caffe/

Back to TK1 ssh terminal,

```
sudo dpkg -i cuda-repo-l4t-r19.2_6.0-42_armhf.deb
sudo apt-get update
sudo apt-get install cuda-toolkit-6-5
sudo usermod -a -G video $USER
echo "# Add CUDA bin & library paths:" >> ~/.bashrc
echo "export PATH=/usr/local/cuda/bin:$PATH" >> ~/.bashrc
echo "export LD_LIBRARY_PATH=/usr/local/cuda/lib:$LD_LIBRARY_PATH" >> ~/.bashrc
source ~/.bashrc
```

After installation of CUDA, run `nvcc -V` to check whether everything is installed correctly.
CUDA 6.5 should be installed.

### Install OpenCV for TK1


[OpenCV installation guideline](http://elinux.org/Jetson/Installing_OpenCV)

Check L4T release version,

    head -n 1 /etc/nv_tegra_release

For L4T r21,

```
sudo dpkg -i libopencv4tegra-repo_l4t-r21_2.4.10.1_armhf.deb
sudo apt-get update
sudo apt-get install libopencv4tegra libopencv4tegra-dev
```



For L4T r19,
To install OpenCV for TK1, we need to download 2 packages from the following sites to PC.

* [OpenCV run](https://developer.nvidia.com/rdp/assets/opencv-run-tegra-k1)

* [OpenCV dev](https://developer.nvidia.com/rdp/assets/opencv-dev-tegra-k1)

Similar to CUDA package, we then copy the packages to TK1.

    scp libopencv4tegra* ubuntu@172.16.134.90://home/ubuntu/Desktop/packages_for_caffe/

Install the packages,

```
sudo dpkg -i libopencv4tegra_2.4.8.2_armhf.deb
sudo dpkg -i libopencv4tegra-dev_2.4.8.2_armhf.deb
```

### Install Caffe and Python interface

Install git package and clone Caffe.

```
sudo apt-get install -y git
cd /home/ubuntu/Desktop
git clone https://github.com/BVLC/caffe.git
cd caffe
cp Makefile.config.example Makefile.config
sed -i "s/# CUSTOM_CXX := g++/CUSTOM_CXX := g++-4.7/" Makefile.config
make -j 4 all
```

After installation, runtest to test caffe layers.

    make -j 4 runtest

Run a benchmark test to check again.

    build/tools/caffe time --model=models/bvlc_alexnet/deploy.prototxt --gpu=0

Install Python related package

```
cd caffe/python
sudo apt-get install python-pip
for req in $(cat requirements.txt); do sudo pip install $req; done
cd ../
sudo apt-get install gcc-4.6 g++-4.6 gcc-4.6-multilib g++-4.6-multilib

# Then change CXX in your make file to be
CXX := /usr/bin/g++-4.6

make all
sudo apt-get install python-numpy
make pycaffe
```

### Monitoring GPU utilization

    sudo ./tegrastats

GPU stats are the GR3D ones


# MNIST LeNet example

Basically, follow the tutorial of [MNIST example](http://caffe.berkeleyvision.org/gathered/examples/mnist.html) in Caffe official page.

### Prepare dataset

```
cd $CAFFE_ROOT
./data/mnist/get_mnist.sh
./examples/mnist/create_mnist.sh
```

### Training

```
cd $CAFFE_ROOT
./examples/mnist/train_lenet.sh
```

This command starts to train a LeNet and the trained model is stored as example/mnist/lenet_iter_10000.caffemodel

### Testing

1. Take a photo and store in caffe/data/mnist/sample_digit.png or .jpg
2. Run python end_to_end_digit_recognition.py

#### Real-time picture reading from camera

Installation of OpenCV-Python, mainly refer to the [tutorial](http://www.pyimagesearch.com/2015/06/22/install-opencv-3-0-and-python-2-7-on-ubuntu/)


```
sudo apt-get install libxtst6:i386 libjpeg62:i386
sudo apt-get install build-essential cmake git pkg-config
sudo apt-get install libjpeg8-dev libtiff4-dev libjasper-dev libpng12-dev
sudo apt-get install libgtk2.0-dev
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libatlas-base-dev gfortran
wget https://bootstrap.pypa.io/get-pip.py
sudo python get-pip.py
cd ~
git clone https://github.com/opencv/opencv.git
cd ~/opencv
mkdir build
cd build
cmake -DWITH_CUDA=ON -DCUDA_ARCH_BIN="3.2" -DCUDA_ARCH_PTX="" -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF ..

sudo make -j4 install
sudo ldconfig
echo "# Use OpenCV and other custom-built libraries." >> ~/.bashrc
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/" >> ~/.bashrc
source ~/.bashrc
```    

read video from openCV

```
import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Display the resulting frame
    cv2.imshow('frame',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
```


# Reference

[run caffe on TK1](https://petewarden.com/2014/10/25/how-to-run-the-caffe-deep-learning-vision-library-on-nvidias-jetson-mobile-gpu-board/)

[MNIST LeNet example](http://caffe.berkeleyvision.org/gathered/examples/mnist.html)

[MNIST change](https://github.com/BVLC/caffe/pull/2359/commits/dd3a5f9268ca3bdf19a17760bd6f568e21c1b521)

[OpenCV installation guideline](http://elinux.org/Jetson/Installing_OpenCV)