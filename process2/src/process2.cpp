#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include "C:\huyle1\projects\IncepIT-TECSWING-Bay-Camera-64bit\OptitrackCameraDLL\OptitrackCameraDLL\FrameCreatorCPP.h"

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    std::cout << "\nEnter to read shared memory.\n";
    std::cin.get();//Open already created shared memory object.
    //windows_shared_memory shm(open_only, "MySharedMemory", read_only);
    windows_shared_memory shm(open_only, "OMSCFrameSharedMemory", read_only);

    //Map the whole shared memory in this process
    mapped_region region(shm, read_only);
    SharedMemoryData* pshm = static_cast<SharedMemoryData*>(region.get_address());

    // Test deQueue
    bool wrongShm(false);
    if (pshm->front != 0 || pshm->rear != 299) {
        wrongShm = true;
    }
    for (int pckg(0); pckg < MAX_ENTITIES; pckg++) {
        if (pshm->items[pckg].frontView[0] != pckg%256) {
            wrongShm = true;
        }
        if (pshm->items[pckg].sideView[0] != pckg%256) {
            wrongShm = true;
        }
    }
    if (wrongShm) {
        std::cout << "Shared memory is wrong.\n" << std::endl;
    }
    else {
        std::cout << "Shared memory is right.\n" << std::endl;
    }
    std::cin.get();
    return 0;
}
