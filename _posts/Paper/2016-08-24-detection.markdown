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

<a name = "R-CNN"></a>
| Title  | [Region-based Convolutional Networks for Accurate Object Detection and Segmentation][R-CNN]  |
|--------|---|
| Author |  Ross Girshick, Trevor Darrell |
| Year   | 2014  |
| Link   |https://github.com/rbgirshick/rcnn|


**Summary**

This paper proposes a multi-step object detection pipeline.

![rcnn.png](/home/jzhan/github/huangying-zhan.github.io/public/post_resource/Paper/detection/rcnn.png)

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
* State-of-art mAP in PASCAL VOC (53.7 on PASCAL VOC 2010)
* Very slow due to following reasons
    * Proposal stage (time-consuming, ~2k proposals for each image)
    * Feature extraction (each image need forward propagation)
* Multi-stages, each stage is an indivitual process, which is inconvenient

<br></br>

___

<a name = "SPP-net"></a>
| Title  | [Spatial Pyramid Pooling in Deep Convolutional Networks for Visual Recognition][SPP-net]  |
|--------|---|
| Author |  Kaiming He, Jian Sun |
| Year   | 2014  |
| Link   |https://github.com/ShaoqingRen/SPP_net|


**Summary**

This paper propose a new ConvNet architecture and detection pipeline based on R-CNN. In this ConvNet, it also follows "Proposal->Feedforward each proposal region into whole ConvNet for classification->regressor" pipeline. However, for each proposed region, warp/crop doesn't required to change the size of image to a required size (e.g. 227x227 in AlexNet). The main idea includes,

![SPP-net.png](/home/jzhan/github/huangying-zhan.github.io/public/post_resource/Paper/detection/SPP-net.png)

1. Conv layers actually do not request a fixed size input image but a fixed size output vector/feature map for later FC layers.
2. Flexible pyramid pooling　(SPP layer) at the end of Conv layers (depend on input image size and output vector length) is introduced to produce fixed vectors and aggregate them together.
    * e.g. pooling window's size can be changed according to input imagesize. i.e. larger image -> more Conv output -> larger Conv map -> larger pooling window



**Key points**

* Variable image input size
* Conv layers still have fixed filters, but feature maps's size change accordiningly.
* SPP layer to aggregate all feature maps (different pooling operations)
* can't update conv layer parameters due to pyramid structure

<br></br>

___
<a name = "Fast R-CNN"></a>
| Title  | [Fast R-CNN]  |
|--------|---|
| Author |  Ross Girshick |
| Year   | 2015  |
| Link   |https://github.com/rbgirshick/fast-rcnn|

**Summary**

An updated version of R-CNN. The main idea is a combination of R-CNN and SPP layer from SPP-net. Moreover, this paper also integrates feature extractor, SVM, bbox regressor together. The whole forward pipeline is as following,

![fast_rcnn.png](/home/jzhan/github/huangying-zhan.github.io/public/post_resource/Paper/detection/fast_rcnn.png)

1. Proposal (e.g. Selective search)
2. For each image, feed forward and obtain a Conv feature map from the last Conv layer.
3. Project each proposal (Region of Interest, RoI) to the Conv map to get a RoI feature map.
4. For each RoI feature map, use a RoI pooling layer (single SPP layer, SPP layer varies its size according to input size and output a fixed size vector) to get a fixed feature vector.
5. Pass the fixed feature vector through fully-connect layers for classification and bbox regressor.

**Key points**

* Integrate bbox regressor with classification -> more end-to-end
* For each image, a Conv operation is required, then use the last Conv feature map for later operations.
* Faster and better than R-CNN since features+classifier+regressor are integrated.
* Porposal is still needed at the beginning.


________________________________________

<a name = "Faster R-CNN"></a>
| Title  | [Faster R-CNN]  |
|--------|---|
| Author |  Ross Girshick |
| Year   | 2015  |
| Link   |https://github.com/ShaoqingRen/faster_rcnn; 
https://github.com/rbgirshick/py-faster-rcnn|

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

Reference

[zhangliliang's　论文笔记 《Fast R-CNN》](http://zhangliliang.com/2015/05/17/paper-note-fast-rcnn/)


[R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2014_Region-based_Convolutional_Networks_for_accurate_object_detection_and_segmentation.pdf

[SPP-net]: {{site.url}}/public/post_resource/Paper/detection/2014_Spatial_Pyramid_Pooling_in_Deep_Convolutional_Networks_for_Visual_Recognition.pdf

[Fast R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2015_Fast_R-CNN.pdf

[Faster R-CNN]: {{site.url}}/public/post_resource/Paper/detection/2016_faster-r-cnn-towards-real-time-object-detection-with-region-proposal-networks.pdf