#include "C:\huyle1\projects\IncepIT-TECSWING-Bay-Camera-64bit\OptitrackCameraDLL\OptitrackCameraDLL\FrameCreatorCPP.h"
#include <vector>

#define CAMERA_OUT_PUT_WIDTH	960
#define CAMERA_OUT_PUT_HEIGHT	1080

struct HeapFramePackage
{
	int FrameNum;
	float TimeStamp;
	unsigned char* frontView;
	unsigned char* sideView;
	HeapFramePackage() :FrameNum(0), TimeStamp(0.0){
		frontView = new unsigned char[960 * 1080 * 3]();
		sideView = new unsigned char[960 * 1080 * 3]();
	}
	~HeapFramePackage() {
		delete[] frontView, sideView;
		frontView = nullptr;
		sideView = nullptr;
	}
};

int main() {
	FrameCreatorCPP* frameCreator = new FrameCreatorCPP("cppframe", CAMERA_OUT_PUT_WIDTH, CAMERA_OUT_PUT_HEIGHT, "BGR", 125, 2);
	frameCreator->reset();

	// prepare MAX_ENTITIES frame packages
	HeapFramePackage heap_frame_package[MAX_ENTITIES];
	for (int pckg(0); pckg < MAX_ENTITIES; pckg++) 
	{
		heap_frame_package[pckg].FrameNum = pckg;
		heap_frame_package[pckg].TimeStamp =(float) pckg+0.1;
		for (uint32_t i(0); i < 960 * 1080 * 3; i++) 
		{
			heap_frame_package[pckg].frontView[i] = pckg;
			heap_frame_package[pckg].sideView[i] = pckg;
		}
	}

	std::cout << "\nEnter to push data to shm.\n";
	std::cin.get();
	
	// Push 300 frames to shm
	bool result(false); 
	std::vector<void*> frameTempVector;
	for (int pckg(0); pckg < MAX_ENTITIES; pckg++) {
		frameTempVector = {heap_frame_package[pckg].frontView, heap_frame_package[pckg].sideView};
		result = frameCreator->pushFrame(frameTempVector, heap_frame_package[pckg].FrameNum, heap_frame_package[pckg].TimeStamp);
	}
	std::cout << "\nFinish pushing 300 Frames to shm.\n";
	// Push 301th frames to test isFull()
	result = frameCreator->pushFrame(frameTempVector, heap_frame_package[MAX_ENTITIES-1].FrameNum, heap_frame_package[MAX_ENTITIES-1].TimeStamp);
	
	std::cout << "Enter to flush." << std::endl;
	std::cin.get();
	frameCreator->flush();
	std::cin.get();
	delete frameCreator;
	frameCreator = nullptr;
	return 0;
}