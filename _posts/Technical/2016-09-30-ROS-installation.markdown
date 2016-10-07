---
layout: post
title:  "ROS Installation & Cheatsheet"
date:   2016-09-30
categories: Technical
tags: [ROS]
---

### Summary



___

### Contents

1. [ROS installation](#ROS installation)
2. [Cheatsheet](#Cheatsheet)
2. [Error and solution](#Error and solution)

___

<a name = "ROS installation"></a>

### Part 1. ROS installation


### Part 2. Cheatsheet

General

```
rospack find [package] # return package directory
roscd [path] # change directory to a package or a stack
rosls [path] # list files in the package

mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace


catkin_create_pkg [package_name] [depend1] [depende2] # create a catkin worksapce
catkin_make # build the packages

roscore # start core service
rosnode list # list running nodes
rosnode info [node] # return node information
rosrun [package] [node_name] #run a node

ros rqt_graph rqt_graph

rostopic list -v # show topics and their information
rostopic type [topic] # get the message type of the topic
rostopic pub [topic] [msg_type] [args] # publishes data to a topic
rostopic hz [topic] # show the publish rate

rosmsg show <msg> #get the information of the message
```


<a name = "Error and solution"></a>

### Part 3. Error and solution

No module named catkin_pkg

	pip install catkin_pkg

No module named rosdep2.rospack

	pip install rosdep

No module named em
	
    pip install empy