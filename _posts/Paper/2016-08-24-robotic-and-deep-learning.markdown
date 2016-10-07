---
layout: post
title:  "Robotic and Deep Learning"
date:   2016-08-24
categories: Paper
tags: [Navigation, SLAM,  DeepLearning]
---

### Contents

1. [Deep Neural Network for Real-Time Autonmous Indoor Navigation](#[Deep Neural Network for Real-Time Autonmous Indoor Navigation])
2. [A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots](#A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots)
3. [From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots](#From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots)

___

<a name = "Deep Neural Network for Real-Time Autonmous Indoor Navigation"></a>


| Title  | [Deep Neural Network for Real-Time Autonmous Indoor Navigation]  |
|--------|---|
| Author |  Dong Ki Kim, Tsuhan Chen |
| Year   | 2015  |


**Summary**

This paper proposes an integration of deep learning algorithm and UAV drone. The target is to allow a drone automatically navigating in an indoor environment & searching for a school bag.

It is a classification problem. 6 types of commands (classes) are trained with CaffeNet, including, 

![img_1]

The dataset construction is based on human response imitation. Firstly, human control the drone in the environment using computer command which will be sent to the drone. Second, the commands are recorded as label of images seen by the drone. Third, train a DNN as classification problem.

**Key point**

* Human response imitation
* Easy dataset construction
* Simple classification problem -> easy to train a DNN
* Specific drone required
* Limited command(?)


<br></br>
___
<a name = "A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots"></a>

| Title  | [A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots]  |
|--------|---|
| Author |  Alessandro Giusti, Luca M.Gambardella |
| Year   | 2015  |


**Summary**

This paper integrates deep learning (classification) and UAV drone. The target is to allow UAV to recognize forest trail and make a corresponding move decision, including,

1. forward
2. turn left
3. turn right

![img_2] 

The dataset construction method is innovative. A hiker put 3 cameras (GoPro) on his head and walks straghtly in forest trails. The images taken by 3 cameras corresponds to 3 different classes.

**Key point**

* 3 cameras for dataset construction
* Easy dataset construction
* Simple classification problem -> easy to train a DNN
* Limited command, because only 3 kinds of actions can be recorded

<br></br>
___

<a name = "From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots"></a>

| Title  | [From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots]  |
|--------|---|
| Author |  Mark Pfeiffer, Michael Schaeuble, Juan Nieto, Roland Siegwart and Cesar Cadena |
| Year   | 2016  |

**Summary**

_____________________________

[Deep Neural Network for Real-Time Autonmous Indoor Navigation]: {{site.url}}/public/post_resource/Paper/UAV_and_deep_learning/navigation/2015_DNN_for_real-time_Autonomous_Indoor_Navigation.pdf

[img_1]: {{site.url}}/public/post_resource/Paper/UAV_and_deep_learning/navigation/img_1.png


[A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots]: {{site.url}}/public/post_resource/Paper/UAV_and_deep_learning/navigation/2015_A_Machine_Learning_Approach_to_the_Visual_Perception_of_Forest_Trails_for_Mobile_Robots.pdf

[From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots]: https://arxiv.org/pdf/1609.07910.pdf


[img_2]: {{site.url}}/public/post_resource/Paper/UAV_and_deep_learning/navigation/img_2.png

