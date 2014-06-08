
all:
	g++ -std=c++11 -O3 -o v4l2stereo main.cpp libcam.cpp stereovision.cpp -I/usr/include/opencv -I/usr/local/include/cvblobs -L/usr/lib `pkg-config opencv --cflags --libs` -L/usr/local/lib -msse3 -Wall -pedantic -fopenmp -lcvblobs

debug:
	g++ -std=c++11 -g -o v4l2stereo *.cpp calibration/*.cpp elas/*.cpp -I/usr/include/opencv -L/usr/lib `pkg-config opencv --cflags --libs` -msse3 -Wall -pedantic -fopenmp

clean:
	rm -f v4l2stereo
