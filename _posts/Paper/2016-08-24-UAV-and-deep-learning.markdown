---
layout: post
title:  "UAV and Deep Learning"
date:   2016-08-24
categories: Paper
tags: [Paper, Navigation, Deep Learning]
---

### Contents

1. Navigation


### Navigation

___
 
Title

* [Deep Neural Network for Real-Time Autonmous Indoor Navigation]

Author

* Dong Ki Kim, Tsuhan Chen

Year

* 2015



| head |a |
|a|d|
|b|c|


__Summary__

This paper propose an integration of deep learning algorithm and UAV drone. The target is to allow a drone automatically navigating in an indoor environment & searching for a school bag.

It is a classification problem. 6 types of commands (classes) are trained with CaffeNet, including, 

![img_1]

The dataset construction is based on human response imitation. Firstly, human control the drone in the environment using computer command which will be sent to the drone. Second, the commands are recorded as label of image seen by the drone. Third, train a DNN as classification problem.

__Key points__

* human response imitation

__Pros__: 

* Easy dataset construction
* Simple classification problem -> easy to train a DNN

__Cons__ 

* Specific drone required
* Limited command(?)

________________________________________


__Title__ 

* [A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots]

__Author__ 

* Alessandro Giusti, Luca M.Gambardella

__Year__ 

* 2015

__Summary__

This paper integrates deep learning (classification) and UAV drone. The target is to allow UAV to recognize forest trail and make a corresponding move decision, including,

1. forward
2. turn left
3. turn right

![img_2] 

The dataset construction method is innovative. A hiker put 3 cameras (GoPro) on his head and walks straghtly in forest trails. The images taken by 3 cameras corresponds to 3 different classes.

__Key points__

* 3 cameras for dataset construction

__Pros__: 

* Easy dataset construction
* Simple classification problem -> easy to train a DNN

__Cons__ 

* Limited command, because only 3 kinds of actions can be recorded

_____________________________

[Deep Neural Network for Real-Time Autonmous Indoor Navigation]: {{site.url}}/public/post/UAV_paper/navigation/2015_DNN_for_real-time_Autonomous_Indoor_Navigation.pdf

[img_1]: {{site.url}}/public/post/UAV_paper/navigation/img_1.png

[A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots]: {{site.url}}/public/post/UAV_paper/navigation/2015_A_Machine_Learning_Approach_to_the_Visual_Perception_of_Forest_Trails_for_Mobile_Robots.pdf

[img_2]: {{site.url}}/public/post/UAV_paper/navigation/img_2.png