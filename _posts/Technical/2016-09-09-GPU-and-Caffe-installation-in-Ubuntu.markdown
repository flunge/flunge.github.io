---
layout: post
title:  "GPU and Caffe Installation in Ubuntu"
date:   2016-09-09
categories: Technical
tags: [GPU, Caffe]
---

### Summary

[Caffe] is a deep learning framework developed by Berkeley Vision and Learning Center (BVLC). It is specifically designed for deep neural network training and application, especially for convolutional neural networks. However, the training/computation is time-consuming in CPU mode. Therefore, GPU computing is introduced to accelerate the computation. In this post, NVIDIA GTX-1080 is used. GTX-1080 and Caffe installation procedure is recorded. The whole process is operated in Ubuntu 14.04.

___

### Contents

1. [GTX-1080 installation](#GTX-1080 installation)
2. [Caffe installation](#Caffe installation)

___

<a name = "GTX-1080 installation"></a>
### Part 1. GTX-1080 installation

The installation of GTX-1080 mainly refers to [yangcha's tutorial](yangcha.github.io/GTX-1080). 

For different GPU devices, different driver should be installed. In here, the instruction is just for GTX-1080.

```
sudo add-apt-repository ppa:graphics-drivers/ppa
sudo apt-get update
sudo apt-get install nvidia-367
sudo apt-get install mesa-common-dev
sudo apt-get install freeglut3-dev
# Reboot the system to load the driver
sudo reboot
```

<br></br>
___

<a name = "Caffe installation"></a>
### Part 2. Caffe installation

In this part, a simple installation instruction of Caffe is recorded. Basically, the steps are as following. First, install some dependencies for Caffe; Second, download and install Caffe; Third, compile Caffe.

The installation mainly refers to the following websites.

* [Caffe's installation guideline](http://caffe.berkeleyvision.org/installation.html)
* [Caffe's guideline (dependencies installation)](http://caffe.berkeleyvision.org/install_apt.html)

<br></br>

#### 2.1 Install CUDA

If you do not have a NVIDIA GPU supporting CUDA, you actually can ignore this step and move on to next step. Running Caffe without GPU is still possible, but losing the GPU computing feature. Now, for GPU users, visit NVIDIA's [cuda-toolkit](https://developer.nvidia.com/cuda-toolkit) and download CUDA 8.0RC. However, this requrest requires a NVIDIA membership, so join it and download CUDA 8.0RC.

After entering the download page, you will see that there are 3 types of installer. Just pick one and follow the installation instructions.

![CUDA.png]({{site.url}}/public/post_resource/Technical/GPU_and_caffe_installation_in_Ubuntu/CUDA.png)

After installation, you need to set CUDA environment.

```
export PATH=/usr/local/cuda-8.0/bin:$PATH    
export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH  
```

If you later on find that this `export` doesn't work for Caffe, you can directly update Makefile.config in Caffe. We will see.

<br></br>

#### 2.2. Install dependencies

1. Install general dependencies

    ```
    sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
    sudo apt-get install libboost-all-dev
    ```

2. Install ATLAS

        sudo apt-get install libatlas-base-dev

3. Install remaining dependencies

        sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev

	If you are not using Ubuntu 14.04, you may not be able to install these dependencies. Please refer to [here](http://caffe.berkeleyvision.org/install_apt.html).

<br></br>

#### 2.3. (Optional) Anaconda-python
Anaconda is a package which includes a lot of useful python packages/libraries.
It is recommended to install Anaconda but not a compulsory part for Caffe.

Downalod the installer from the Anaconda's [dowloads pag一e](https://www.continuum.io/downloads#linux).

```
cd ~/Downloads

# For different version's installer, 'xxx' is different, just refer to your downloaded installer.
bash Anaconda2-xxx.sh 
```

Follow the installation guideline and accept the statements.
After installation, open a new terminal and check for it by typing `python` in the terminal.
After entering Python, you should see the Python version is something like `Python 2.7.12 |Anaconda 4.1.1 (64-bit)|`

Installation of Anaconda is completed! To know more, please refer to [Anaconda's tutorial](http://conda.pydata.org/docs/) or homepage.

<br></br>

#### 2.4. (Optional) OpenCV

Official requirement: OpenCV >=2.4, including 3.0. Installation of OpenCV is quite ugly, there are already some good instructions. Currently, this part is **to be edited.**

+ [OpenCV installation instruction](http://sysads.co.uk/2014/05/install-opencv-2-4-9-ubuntu-14-04-13-10/)

<br></br>

#### 2.5. Download Caffe

First, `git` is required, can be installed by    

    sudo apt-get install git

Then, clone caffe to a local directory

```
git clone https://github.com/BVLC/caffe.git
cd $CAFFE # $CAFFE is the directory of your downloaded Caffe
cp Makefile.config.example Makefile.config
```

You can modify the configuration before `make` in this `Makefile.config`. Here are some possible modifications.

```
# Anaconda (Uncomment the related part)
# If you are using Anaconda2, remember to udpate ANACONDA_HOME to anaconda2, uncomment this part and comment the original python setup

# PYTHON_INCLUDE := /usr/include/python2.7 \
#                /usr/lib/python2.7/dist-packages/numpy/core/include

ANACONDA_HOME := $(HOME)/anaconda2
PYTHON_INCLUDE := $(ANACONDA_HOME)/include \
                 $(ANACONDA_HOME)/include/python2.7 \
                 $(ANACONDA_HOME)/lib/python2.7/site-packages/numpy/core/include \

# If you don't have a NVIDIA GPU supporting CUDA, you can uncomment a CPU-only switch to build without GPU support.
# CPU-only switch (uncomment to build without GPU support).
CPU_ONLY := 1

# As mentioned before, if your "export" for CUDA path is not working later on. There are two possible solutions.
# (1)
sudo ldconfig /usr/local/cuda/lib64
# (2)
# You can update CUDA directory in this Makefile.config.
# Search for this line,
CUDA_DIR := /usr/local/cuda
# Update it to 
CUDA_DIR := /usr/local/cuda-8.0
```

Then, we can start compiling Caffe.

```
make clean
make all -j8 # where -j8 means use 8 cores of your CPU for compilation which can accelerate the compilation. you should change -j according to the number of your CPU cores. 
make test -j8
make runtest -j8
```
If there is no error up to this stage, Caffe installation is completed.

<br></br>

#### 2.6. (Optional) Install PyCaffe (Python Caffe Interface)

If Python interface is used, follow the guideline to install PyCaffe

```
sudo apt-get install python-dev
cd $CAFFE/python

sudo apt-get install python-pip

for req in $(cat requirements.txt); do sudo pip install $req; done

cd ..
make pycaffe
```

Up to here, the installation is completed!

[Caffe]: http://caffe.berkeleyvision.org/