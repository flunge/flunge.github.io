---
layout: post
title:  "Detection"
date:   2016-08-24
categories: Paper
tags: [Detection, Deep Learning]
---

### Contents

1. [R-CNN](#R-CNN)
2. [SPP-net](#SPP-net)
3. [Fast R-CNN](#Fast R-CNN)
4. [Faster R-CNN](#Faster R-CNN)

___


| Title  | [Region-based Convolutional Networks for Accurate Object Detection and Segmentation][R-CNN]  |
|--------|---|
| Author |  Ross Girshick, Trevor Darrell |
| Year   | 2015  |
| Link   |https://github.com/rbgirshick/rcnn|


**Summary**

This paper proposes a multi-step object detection pipeline. 

Forward pass:

1. Selective Search to find out rectangle regions where might contain objects, these regions are called proposal.
2. For each proposed region, crop the region from raw image and warp the image to a desirable size (e.g. 227x227 for AlexNet).
3. Feed the warped image into a trained ConvNet(e.g. trained AlexNet) to extract features (4096 vector @ fc7).
4. Use a SVM to classifier features into n classes.
5. Use features to train a bounding box (bbox) regressor. The purpose is to adjust the position and size (dx,dy, dw, dh) of bbox.

Training:

1. Train a ConvNet to classify n classes.
2. Use extracted features to train a SVM to classify n classes. 
3. Use extracted features to train a bbox regressor (output: predicted bbox; label: correct bbox(x,y,w,h)

**Key point**

* Multi-stages pipeline for object detection
* High mAP in PASCAL VOC at that time
* Very slow due to following reasons
    * Proposal stage (time-consuming, ~2k proposals for each image)
    * Feature extraction (each image need forward propagation)
* Multi-stages, each stage is an indivitual process, which is inconvenient
________________________________________


__Title__ 

* [Spatial Pyramid Pooling in Deep Convolutional Networks for Visual Recognition][SPP-net]

__Author__ 

* Kaiming He, Jian Sun

__Year__ 

* 2015

__Summary__

This paper propose a new ConvNet architecture and detection pipeline based on R-CNN. In this ConvNet, it also follows "Proposal->classification->regressor" pipeline. However, for each proposed region, warp/crop doesn't required to change the size of image to a required size (e.g. 227x227 in AlexNet). The main idea includes,

1. Conv layers actually do not request a fixed size input image but a fixed size output vector/feature map for later FC layers.
2. Flexible pyramid pooling at the end of Conv layers (depend on input image size and output vector length) is introduced to produce a fixed vector output.
    * e.g. pooling window's size can be changed according to input imagesize. i.e. larger image -> more Conv output -> larger Conv map -> larger pooling window
3. A SPP layer is introduced to aggregate all feature maps

__Key points__

* Vary image input size
* Conv layers still have fixed filters, but feature maps's size changed accordiningly
* SPP layer to aggregate all feature maps (different pooling operations)

__Pros__: 

* fast due to single conv operation
* Vary input size

__Cons__ 

* can't update conv layer parameters due to pyramid structure
________________________________________

__Title__ 

* [Fast R-CNN]

__Author__ 


* Ross Girshick

__Year__ 

* 2015

__Summary__

A updated version of R-CNN. Most idea is similar to R-CNN, but integrating feature extractor, SVM, bbox regressor together. Also, proposal is done at the end of front Conv layers rather than raw images.
Proposal -> Classification & Regressor

__Key points__

* Integrate bbox regressor with classification -> more end-to-end
* Proposal made in the last Conv layer

__Pros__: 

* Faster and better than R-CNN since features+classifier+regressor are integrated.

__Cons__ 


________________________________________

__Title__ 

* [Faster R-CNN]

__Author__ 


* Shaoqing Ren, Ross Girshick, Jian Sun

__Year__ 

* 2015

__Summary__

A updated version of R-CNN and Fast R-CNN. The whole structure is mainly based on Fast R-CNN, but proposal part is replaced by a ConvNet. Region Proposal Networks is proposed to predict proposal regions. For each sliding window postion, anchors with different scale and aspect ratio are introduced.

Training steps to have share Conv layers:

1. Initialize network with ImageNet pre-trained model
2. Fine-tune whole network for the Region Proposal Network (RPN model)
3. Fine-tune the RPN model in (2) to Fast R-CNN for the detection task
4. Use detector network to initialize PRN but fix the shared conv layers and finetune layers unique to RPN
5. Keey shared conv layers fixed, fine-tune the fc layers of Fast R-CNN

__Key points__

* Without traditional proposal methods (Selective search or EdgeBox)
* Use RPN to make proposal

__Pros__: 

* Very fast since proposal part is replaced by same network

__Cons__ 


________________________________________


[R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2015_Region-based_Convolutional_Networks_for_accurate_object_detection_and_segmentation.pdf

[SPP-net]: {{site.url}}/public/post_resource/Paper/detection/2015_Spatial_Pyramid_Pooling_in_Deep_Convolutional_Networks_for_Visual_Recognition.pdf

[Fast R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2015_Fast_R-CNN.pdf

[Faster R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2016_faster-r-cnn-towards-real-time-object-detection-with-region-proposal-networks.pdf