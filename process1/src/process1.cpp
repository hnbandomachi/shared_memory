#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>

#define ACCEPTED_SIZE_BYTE  (uint32_t)(4095*1024*1024)

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    windows_shared_memory shm(create_only, "MySharedMemory", read_write, ACCEPTED_SIZE_BYTE);
    mapped_region region(shm, read_write);
    int* pshm = static_cast<int*> (region.get_address());
    uint32_t sz_shm = region.get_size();
    std::cout << "Region address: " << pshm << std::endl;
    std::cout << "Region size: " << (float)sz_shm/1024/1024 << " MB" << std::endl;
    
    std::clock_t start;
    double duration;

    start = std::clock(); // get current time

    for (uint32_t j(0); j < sz_shm/sizeof(int); ++j) {
        memset(pshm+j, 0xFF, sizeof(int));
    }
    std::cout << "Done setting.\n";

    int* last_pshm = pshm + sz_shm / sizeof(int);
    uint32_t sz_shm_MB = sz_shm / sizeof(int) * 4 / 1024 / 1024;

    std::cout << "sz_shm_MB = " << sz_shm_MB << std::endl;

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC*1000;
    std::cout << "memset() operation took " << duration << "ms" << std::endl;

    std::cin.get();
    return 0;
}
