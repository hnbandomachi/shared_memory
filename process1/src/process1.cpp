#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>


int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    windows_shared_memory shm(create_only, "MySharedMemory", read_write, 1000);
    mapped_region region(shm, read_write);
    int* pshm = static_cast<int*> (region.get_address());
    std::cout << "Region address: " << pshm << std::endl;
    
    int i(0);
    for (int j(0); j < 3; ++j) {
        std::cout << "Data i = "; std::cin >> i;
        std::cin.get(); 
        std::cout << "Setting data 0x"<< i <<  " at address " << pshm + j << std::endl;
        //std::memset((pshm + j), (int)i, sizeof(int));
        memcpy(pshm + j, &i, sizeof(int));
    }
    std::cin.get();
    return 0;
}
