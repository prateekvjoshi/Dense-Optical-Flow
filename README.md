Dense Optical Flow
==================

Dense optical flow algorithm to track visual features in the input video. At each frame, you will know the direction in which each feature is moving. This is also very useful in estimating the moving regions in the input video stream. There is a file called "CMakeLists.txt". This file will be used to build the project (if you have built OpenCV using cmake). If not, just use the .cpp file in your project and build it. To build using command line, follow the steps below to get it up and running:

	$ cmake .
	$ make
	$ ./main 

When you run the code, a window will pop up showing the features being tracked. If you observe carefully, the features will relocate only for the moving parts in the video.