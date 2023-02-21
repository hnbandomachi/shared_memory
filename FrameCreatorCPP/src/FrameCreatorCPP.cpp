#include "C:\huyle1\projects\IncepIT-TECSWING-Bay-Camera-64bit\OptitrackCameraDLL\OptitrackCameraDLL\FrameCreatorCPP.h"

#define CAMERALIBRARY_IMPORTS 1
#define CORE_IMPORTS 1
#define WIN32_LEAN_AND_MEAN
#define CAMERA_OUT_PUT_WIDTH 960
#define CAMERA_OUT_PUT_HEIGHT 1080
#define CAMERA_LIMIT 6
#define INIT_TIMEOUT 10000
#define FRAME_RATE 120


int main() {
	FrameCreatorCPP* frameCreator = new FrameCreatorCPP("ulvframe", CAMERA_OUT_PUT_WIDTH, CAMERA_OUT_PUT_HEIGHT, "BGR", 125, 2);;
	return 0;
}