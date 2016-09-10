---
layout: post
title:  "Camera Setup on TK1 (ZED & e-CAM40)"
date:   2016-08-23
categories: Setup
tags: Hardware Setup
---


# e-CAM40

Module: [e-CAM40_CUMI4682_MOD - 4 MP OV4682 RGB IR Camera Module](https://www.e-consystems.com/OV4682-RGB-IR-MIPI-CAMERA-Module.asp)

### Installation of camera

Refer to official guideline, [eCAM documents](https://www.e-consystems.com/OV4682-RGB-IR-MIPI-CAMERA-Module.asp#documents)

### Use of camera

Load camera and turn on camera GUI
```
~/unload_4mp.sh
./init_4mp.sh

# There are 4 possible resolutions.
# 1: 672x380
# 2: 1280x720 
# 3: 1920x1080 
# 4: 2688x1520
# In this applicaiton, we only need 672x380.

./sample_app/Binaries/sample_gl_app 1
```

### Update of camera code

#### Real-time photo saving

open "main.c" in ~/sample_app/Source

From line 91 to line 112, update the code to the following code

```
	int cnt;
	int cap_cnt;
	cnt=0;
	cap_cnt=20;
	while(!(Detect_Key(&global,'q') || global.signalquit ))
	{
		gettimeofday(&t2, &tz);
		deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
		t1 = t2;
		helper_dq_cam_frame(&global.cambuffer,&global.bytes_used);
		OV4682_Demosaic(global.cambuffer,NULL,global.img_w,global.img_h,&global);
		SwapBuffers();
		if(global.capImage && cnt==cap_cnt){
			OV4682_SaveImage(global.imgFormat, &global);
			cnt=0;
		}
		helper_q_cam_frame();
		totaltime += deltatime;
		frames++;
		if (totaltime >  2.0f)
		{
			printf("%4d frames rendered in %1.4f seconds -> FPS=%3.4f\n", frames, totaltime, frames/totaltime);
			totaltime -= 2.0f;
			frames = 0;
		}
		cnt++;
		if (global.capImage==0){
		cnt=0;		
		}
	}
```

cnt and cap_cnt is a parameter pair which is used to count the loops for picture saving.
Once cnt reaches cap_cnt, picture is saved.

After updating the code in ~/sample_app/Source. Use Makefile to rebuild the application

```
cd ~/sample_app/Source
make
```

_All other necessary update can be also done by following the uideline._

# Setup of ZED camera
Mainly refer to [official blog: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/)    

Requirement: 

* CUDA 6.5 R.21
* openCV 2.4.10

# Enable remote GUI

    export DISPLAY:=0
    # run the shell script written in the remote server

    

### Reference

* [e-CAM40_CUMI4682_MOD - 4 MP OV4682 RGB IR Camera Module](https://www.e-consystems.com/OV4682-RGB-IR-MIPI-CAMERA-Module.asp)

* [official blog: TK1 & ZED](https://www.stereolabs.com/blog/index.php/2015/09/24/getting-started-with-jetson-tk1-and-zed/)    