---
layout: post
title:  "Detection"
date:   2016-08-24
categories: Paper
tags: [Detection, DeepLearning]
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

![rcnn.png]({{site.url}}public/post_resource/Paper/detection/rcnn.png)

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
| Author |  Kaiming He, Xiangyu Zhang, Shaoqing Ren, Jian Sun |
| Year   | 2014  |
| Link   |https://github.com/ShaoqingRen/SPP_net|


**Summary**

This paper propose a new ConvNet architecture and detection pipeline based on R-CNN. In this ConvNet, it also follows "Proposal->Feedforward each proposal region into whole ConvNet for classification->regressor" pipeline. However, for each proposed region, warp/crop doesn't required to change the size of image to a required size (e.g. 227x227 in AlexNet). The main idea includes,

![SPP-net.png]({{site.url}}public/post_resource/Paper/detection/SPP-net.png)


1. Conv layers actually do not request a fixed size input image but a fixed size output vector/feature map for later FC layers.
2. Flexible pyramid pooling (SPP layer) at the end of Conv layers (depend on input image size and output vector length) is introduced to produce fixed vectors and aggregate them together.
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

![fast_rcnn.png]({{site.url}}public/post_resource/Paper/detection/fast_rcnn.png)

1. Proposal (e.g. Selective search)
2. For each image, feed forward and obtain a Conv feature map from the last Conv layer.
3. Project each proposal (Region of Interest, RoI) to the Conv map to get a RoI feature map.
4. For each RoI feature map, use a RoI pooling layer (single SPP layer, SPP layer varies its size according to input size and output a fixed size vector) to get a fixed feature vector.
5. Pass the fixed feature vector through fully-connect layers for classification and bbox regressor.

**Key points**

* Integrate bbox regressor with classification -> more end-to-end
* For each image, a Conv operation is required, then use the last Conv feature map for later operations.
* a SVD algorithm is introduced to reduce redundent connections in fully-connection layer.
* Faster and better than R-CNN since features+classifier+regressor are integrated.
* Porposal is still needed at the beginning.


<br></br>
________________________________________

<a name = "Faster R-CNN"></a>

| Title  | [Faster R-CNN]  |
|--------|---|
| Author |  Shaoqing Ren, Kaiming He, Ross Girshick, Jian Sun |
| Year   | 2015  |
| Link   |https://github.com/ShaoqingRen/faster_rcnn <br> https://github.com/rbgirshick/py-faster-rcnn|

**Summary**

![faster_rcnn_1.png]({{site.url}}public/post_resource/Paper/detection/faster_rcnn_1.png)

An updated version of R-CNN and Fast R-CNN. The whole structure is mainly based on Fast R-CNN, but proposal part is replaced by a ConvNet. Region Proposal Network (RPN) is proposed to predict proposal regions. RPN slides over the last shared Conv feature map to determine whether the region is an object or not. Another highlight of this network is shared Conv layers for RPN and Object recognition. The whole procedure is as following,

Forward pass:

![faster_rcnn_2.png]({{site.url}}public/post_resource/Paper/detection/faster_rcnn_2.png)

1. For each image, feed forward to get a Conv feature map (Conv') from the last Conv layer.
2. RPN to determine object or not

	2.1. On Conv'(256 channels), a 3x3 Conv layer is sliding across the map.
	2.2. At each sliding region, a 256-d feature vector is produced and fully connected to cls layer and reg layer
	2.3. cls layer is a 2-class classification layer (object or not)
	2.4. reg layer is a bbox regressor to adjust the position of bounding box.
	2.5. Anchor is introduced to　give the network translation-invariant. (each anchor represent a combination of different aspect ration and scale)

3. After getting proposals, each proposed region on Conv' is passed into a RoI pooling layer, the purpose is to get a fixed feature vector output to later FC layers.
	3.1. RoI pooling layer is actually a special case of SPP layer (single SPP layer).
	3.2. The layer size is varying according to the size of input feature map.
	3.3. Since the layer size is changing, it always outputs a fixed feature vector.
4. The RoI feature vector is fully connected to a FC layer and do classification.

Training steps to have share Conv layers:

1. Initialize a network with ImageNet pre-trained model
2. Fine-tune whole network for the Region Proposal Network (RPN model)
3. Fine-tune the RPN model in (2) to Fast R-CNN for the detection task
4. Use detector network to initialize PRN but fix the shared conv layers and finetune layers unique to RPN
5. Keep shared conv layers fixed, fine-tune the fc layers of Fast R-CNN

**Key points**

* Without traditional proposal methods (Selective search or EdgeBox)
* Use RPN to make proposal
* Very fast since proposal part is replaced by RPN
* Anchors with translation invariance

________________________________________

Reference

[论文笔记 《Fast R-CNN》](http://zhangliliang.com/2015/05/17/paper-note-fast-rcnn/)


[R-CNN]: {{site.url}}public/post_resource/Paper/detection/2014_Region-based_Convolutional_Networks_for_accurate_object_detection_and_segmentation.pdf

[SPP-net]: {{site.url}}public/post_resource/Paper/detection/2014_Spatial_Pyramid_Pooling_in_Deep_Convolutional_Networks_for_Visual_Recognition.pdf

[Fast R-CNN]: {{site.url}}public/post_resource/Paper/detection/2015_Fast_R-CNN.pdf

[Faster R-CNN]: {{site.url}}public/post_resource/Paper/detection/2016_faster-r-cnn-towards-real-time-object-detection-with-region-proposal-networks.pdf