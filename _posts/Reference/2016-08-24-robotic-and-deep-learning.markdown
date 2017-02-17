---
layout: post
title:  "Robotic and Deep Learning"
date:   2016-08-24
categories: Reference
tags: [Odometry,  DeepLearning]
---

### Contents

1. [Deep Neural Network for Real-Time Autonmous Indoor Navigation](#[Deep Neural Network for Real-Time Autonmous Indoor Navigation])
2. [A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots](#A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots)
3. [From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots](#From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots)
4. [Deep Learning for Laser based Odometry Estimation](#Deep Learning for Laser based Odometry Estimation)
5. [Learning visual odometry with a convolutional network](#Learning visual odometry with a convolutional network)

___

<a name = "Deep Neural Network for Real-Time Autonmous Indoor Navigation"></a>


| Title  | [Deep Neural Network for Real-Time Autonmous Indoor Navigation]  |
|--------|---|
| Author |  Dong Ki Kim, Tsuhan Chen |
| Year   | 2015  |


**Summary**

This paper proposes an integration of deep learning algorithm and UAV drone. The target is to allow a drone automatically navigating in an indoor environment & searching for a school bag.

It is a classification problem. 6 types of commands (classes) are trained with CaffeNet, including, 

![img_1](https://cloud.githubusercontent.com/assets/13748721/19177572/f8356968-8c7c-11e6-80d8-976eb3bc446f.png)

The dataset construction is based on human response imitation. Firstly, human control the drone in the environment using computer command which will be sent to the drone. Second, the commands are recorded as label of images seen by the drone. Third, train a DNN as classification problem.

**Key point**

```
* Human response imitation
+ Easy dataset construction
+ Simple classification problem -> easy to train a DNN
- Specific drone required
- Limited command(?)
```

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

![img_2](https://cloud.githubusercontent.com/assets/13748721/19177573/f8397d28-8c7c-11e6-9bbb-8615c6ebe2f4.png)

The dataset construction method is innovative. A hiker put 3 cameras (GoPro) on his head and walks straghtly in forest trails. The images taken by 3 cameras corresponds to 3 different classes.

**Key point**

```
* 3 cameras for dataset construction
+ Easy dataset construction
+ Simple classification problem -> easy to train a DNN
- Limited command, because only 3 kinds of actions can be recorded
```

<br></br>
___

<a name = "From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots"></a>

| Title  | [From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots]  |
|--------|---|
| Author |  Mark Pfeiffer, Michael Schaeuble, Juan Nieto, Roland Siegwart and Cesar Cadena |
| Year   | 2016  |

**Summary**

This paper proposes a framework to train a ConvNet for motion planning. The goal is to provide robot a good motion response when faced obstacles and move toward a target point at the same time (i.e. while moving toward target point, there might be obstacles on the way, the robot need to make response). For training, the input to the ConvNet is a laser range findings (1080-dimension vector indicating distances), target point coordinates (polar coordinates) in a robot-centric coordinate system, and velocity (rotation and translation). For deployment part, the input is the laser range findings and target point coordinates. This is treated as a regression problem.

![image](https://cloud.githubusercontent.com/assets/13748721/19219144/2fa088e8-8e3e-11e6-85b7-2db222ee33f1.png)

For dataset construction, the data is generated from a simulartor and an expert motion planner. Simulator provides environment for laser scanning findings, target coordinates while motion planner provides the corresponding velocity response.

For experiment, there are 6000 trajectories in the training map and 4000 trajectories in the evaluation map, with 2.1M and 2.2M input/output tuples (Why evaluation map has more tuples than training? Because travel longer distance in evaluation maps?). For each trajectory, there are 8 target points. Robot need to travel along all 8 points. However, external SLAM should be employed such that the robot knows where it is and the target point coordinates.

For result evaluation, there are different measurements used to evaluate the performance.

![image](https://cloud.githubusercontent.com/assets/13748721/19219190/3ca9bbb2-8e3f-11e6-9512-143003d23ad3.png)

trans.error: Translation error
rot. error : Rotation error

![image](https://cloud.githubusercontent.com/assets/13748721/19219192/437ea88a-8e3f-11e6-8dac-09a7708934f5.png)

CNN: trained ConvNet for the task
ROS: Global motion planner (with global map)
Etrans / Erot: Energy spent for translation and rotation
dist: travelled distance
dgoal: final distance to goal
time: travel time

Black bar means CNN better than ROS while green bar is opposite.

**Key points**

```
* Apply CNN on Laser findings as vector
* Data-driven end-to-endmotion planning for a bototic platform
* Without pre-training since dataset is large enough
+ Constant calculation time; traditional method depends
+ Transfer the simulation result back to real world is possible 
- External global map needed / robot with SLAM, such that target point coordinates can be known
```

<br></br>
___

<a name = "Deep Learning for Laser based Odometry Estimation"></a>

| Title  | [Deep Learning for Laser based Odometry Estimation]  |
|--------|---|
| Author |  Austin Nicolai, Ryan Skeele, Christopher Eriksen, Geoffrey A. Hollinger |
| Year   | 2016  |

**Summary**

![image](https://cloud.githubusercontent.com/assets/13748721/19220298/f874df44-8e5c-11e6-9535-90f99efca80d.png)

This paper proposes applying deep learning for laser based odometry estimation. The laser is a 3D laser which builds a point cloud based surrounding environments (distance). The collected 3D point cloud is projected to 2D space as a depth map (depth image). Then, CNN is deployed to estimate the odometry between two depth maps, i.e. rotation and translation matrix between the pair. 

![image](https://cloud.githubusercontent.com/assets/13748721/19220300/038b0e4e-8e5d-11e6-89e7-689a106a7d05.png)

For dataset construction, the team collects data from real world with the aid of a Wheel based odometry for providing odometry ground truth. However, they only collected 3300 depth scans. After that, the team augments the dataset via 2 methods. Finally constructed 16000 image pairs.

* Additional pair: ...[t-1],[t],[t+1]...; not only pair [t] & [t+1] but also [t-1] & [t+1]
* Reversed order : [t],[t+1] →  [t+1],[t]

For experiment part, they carry out a lot of experiments concerning pre-training, convolution/pooling layer structure, fully connected layer structure, regularization and optimization. Here is the simplified conclusion. 

* With pre-training is better. The pre-trained model is done by unsupervised learning (auto-encoder)
* Referring to VGG, multiple small Conv filters and reducing FC layers work better.
* Dropout should be added to reduce overfitting
* Optimization methods doesn't matter.

**Key points**

```
* Applying CNN on 3D Laser odometry
* Similar to VGG structure
+ Good data augmentation methods provided
- Insufficient dataset, might be a reason for bad result
- Same initialization for Conv layers but different feature learnt after training
	- Resulted in unshared Conv layers, which may be incorrect
	- Increased memory for more Conv layer
```

<br></br>
___

<a name = "Learning visual odometry with a convolutional network"></a>

| Title  | [Learning visual odometry with a convolutional network]  |
|--------|---|
| Author |  Kishore Konda, Roland Memisevic |
| Year   | 2015  |

**Summary**

This paper presents an approach for visual odometry estimation based on deep ConvNet. The feedforward operation is showed below. The network is also initialized by unservised learning with an auto-encoder. The team reports that training CNN without using features from unsupervised pre-training resulted innoisy filters and overfitting on the training data. 

![image](https://cloud.githubusercontent.com/assets/13748721/19255807/0ffa3820-8f94-11e6-8538-e6f21f59b1b5.png)

Moreover, they are using discretised velocities and direction changes rather than real valued prediction. Due to lackof large amounts of data, the linear regression was unable to larn a good prediction model. Using the predicted velocity and direction, the team is also able to predict a path.

![image](https://cloud.githubusercontent.com/assets/13748721/19255916/f4409ef2-8f94-11e6-895b-d35a070b267d.png)


**Keypoint**

```
* Visual odometry based on ConvNet
* Trained based on KITTY dataset
```


[Deep Neural Network for Real-Time Autonmous Indoor Navigation]: https://arxiv.org/abs/1511.04668


[A Machine Learning Approach to the Visual Perception of Forest Trails for Mobile Robots]: http://rpg.ifi.uzh.ch/docs/RAL16_Giusti.pdf

[From Perception to Decision: A Data-driven Approach to End-to-end Motion Planning for Autonomous Ground Robots]: https://arxiv.org/pdf/1609.07910.pdf

[Deep Learning for Laser based Odometry Estimation]: http://juxi.net/workshop/deep-learning-rss-2016/papers/Nicolai%20-%20Deep%20Learning%20Lidar%20Odometry.pdf

[Learning visual odometry with a convolutional network]: http://www.iro.umontreal.ca/~memisevr/pubs/VISAPP2015.pdf