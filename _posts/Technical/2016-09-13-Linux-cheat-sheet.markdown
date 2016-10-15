---
layout: post
title:  "Linux Cheat Sheet"
date:   2016-09-13
categories: Technical
tags: [Linux]
---

### Contents
1. [Remote](#Remote)

___

<a name = "Remote"></a>
### Remote

SSH

1. Open a terminal on TK1 and install ssh server on TK1 

		$ sudo apt-get install openssh-server

2. Check server setup

    	$ ps -e|grep ssh #If similar message, *"5313 ? 00:00:00 sshd"*, appeared, ssh server is set up successfully.

3. Check IP address of TK1 network

		$ ifconfig #If ethernet is used, check *inent addr* on *eth0*

4. Remote access TK1 from your PC, suppose the IP address of TK1 is *123.456.78.90*

		$ ssh ubuntu@123.456.78.90 # The default password is "ubuntu".

Allow display/GUI

	$ export DISPLAY=:0 # if there is more than one display output, change 0 accordingly.

<br></br>
___

### Problem and solution

1. Ethernet wire is connected but can't connect to internet

    Solution:
    Suspend the system and login again