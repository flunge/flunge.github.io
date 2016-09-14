---
layout: post
title:  "GTX1080 setup & Caffe Installation on Ubuntu14.04"
date:   2016-09-09
categories: Technical
tags: [GPU, Caffe]
---

GTX 1080 installation
Mainly refer to [yangcha's tutorial](yangcha.github.io/GTX-1080)

Caffe installation
Mainly refer to 

* [Caffe's installation guideline](http://caffe.berkeleyvision.org/installation.html)
* [Caffe's guideline (dependency installation)](http://caffe.berkeleyvision.org/install_apt.html)
* [coldmooon's Caffe installation](http://coldmooon.github.io/2015/08/03/caffe_install/)

## Part 1: Install dependencies
#### Install general dependencies
```
sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler

sudo apt-get install libboost-all-dev
```

#### Install ATLAS
    sudo apt-get install libatlas-base-dev


#### Install remaining dependencies
    sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev

problem and solution
Can't run sample (g++ is not found)
sudo apt-get install build-essential

#### (Optional) Anaconda-python
Anaconda is a package which includes a lot of useful python packages/libraries.
It is recommended to install Anaconda but not a compulsory part for Caffe.

Downalod the installer from the Anaconda's [dowloads page](https://www.continuum.io/downloads#linux)

```
cd ~/Downloads

# For different version's installer, 'xxx' is different, just refer to your downloaded installer.
bash Anaconda2-xxx.sh 
```

Follow the installation guideline and accept the statements.
After installation, open a new terminal and check for it by typing `python` in the terminal.
After entering Python, we should see the Python version is something like `Python 2.7.12 |Anaconda 4.1.1 (64-bit)|`

Installation of Anaconda is completed! To know more, please refer to Anaconda's tutorial or homepage.

#### (Optional) OpenCV
Official requirement: OpenCV >=2.4, including 3.0

In this tutorial, OpenCV 2.4 is installed.

1. Download OpenCV from [OpenCV homepage](http://opencv.org/downloads.html)

## Part 2: Compilation
#### Download and install caffe
First, `git` is required, can be installed by    

    sudo apt-get install git

Then, clone caffe to a local directory
```
git clone https://github.com/BVLC/caffe.git
cd $Caffe_dir # $Caffe_dir is the directory of your downloaded Caffe
cp Makefile.config.example Makefile.config
```

You can modify the configuration before `make` in this `Makefile.config`. Here are some possible modifications.
```
# Anaconda (Uncomment the related part)
# If you are using Anaconda2, remember to udpate ANACONDA_HOME to anaconda2
ANACONDA_HOME := $(HOME)/anaconda2
PYTHON_INCLUDE := $(ANACONDA_HOME)/include \
                 $(ANACONDA_HOME)/include/python2.7 \
                 $(ANACONDA_HOME)/lib/python2.7/site-packages/numpy/core/include \

```
(if you have installed Anaconda, remember to uncomment the parts related to anaconda)

Then, we can start compile Caffe
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-8.0/lib64
make clean
make all -j8 # where -j8 means use 8 cores of your CPU for compilation which can accelerate the compilation. you should change -j according to the number of your CPU cores. 
make test -j8
make runtest -j8
```
If there is no error up to this stage, Caffe installation is completed.

#### (Optional) Install PyCaffe (Python Caffe)
If Python interface is used, follow the guideline to install PyCaffe
```
sudo apt-get install python-dev
cd $Caffe_dir/python

sudo apt-get install python-pip
for req in $(cat requirements.txt); do sudo pip install $req; done
cd ..
make pycaffe
```
   