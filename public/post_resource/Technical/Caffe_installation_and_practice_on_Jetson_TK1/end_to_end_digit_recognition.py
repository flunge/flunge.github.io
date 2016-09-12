# manual input image requirement: white blackgroud, black digit
# system input image requirement: black background, white digit

# loading settup
caffe_root = "/home/ubuntu/Desktop/caffe/"
model_weights = caffe_root + "examples/mnist/lenet_iter_10000.caffemodel"
model_def = caffe_root + "examples/mnist/lenet.prototxt"
image_path = caffe_root + "data/mnist/sample_digit.png"


# set up Python environment: numpy for numerical routines, and matplotlib for plotting
import numpy as np
import scipy
import os.path
import time
# import matplotlib.pyplot as plt
from PIL import Image
import sys
sys.path.insert(0, caffe_root + 'python')
import caffe
# caffe.set_mode_cpu()
caffe.set_device(0)
caffe.set_mode_gpu()

# setup a network according to model setup
net = caffe.Net(model_def,      # defines the structure of the model
                model_weights,  # contains the trained weights
                caffe.TEST)     # use test mode (e.g., don't perform dropout)



exist_img_time=0
while True:
	try:
		new_img_time=time.ctime(os.path.getmtime(image_path))
		if new_img_time!=exist_img_time:
			
			# read image and convert to grayscale
			image=Image.open(image_path,'r')
			image=image.convert('L') #makes it greyscale
			image=np.asarray(image.getdata(),dtype=np.float64).reshape((image.size[1],image.size[0]))

			# convert image to suitable size
			image=scipy.misc.imresize(image,[28,28])
			# since system require black backgroud and white digit
			inputs=255-image

			# reshape input to suitable shape
			inputs=inputs.reshape([1,28,28])

			# change input data to test image
			net.blobs['data'].data[...]=inputs

			# forward processing of network
			start=time.time()
			net.forward()
			end=time.time()
			output_prob = net.blobs['ip2'].data[0]  # the output probability vector for the first image in the batch

			print 'predicted class is:', output_prob.argmax()

			
			duration=end-start
			print duration, 's'
			exist_img_time=new_img_time
	except IndexError:
		pass
	except IOError:
		pass
	except SyntaxError:
		pass