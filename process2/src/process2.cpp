#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    std::cout << "\nEnter to read shared memory.\n";
    std::cin.get();//Open already created shared memory object.
    windows_shared_memory shm(open_only, "MySharedMemory", read_only);

    //Map the whole shared memory in this process
    mapped_region region(shm, read_only);

    //Check that memory was initialized to 1
    int* pshm = static_cast<int*>(region.get_address());
    std::cout << "Getting data of address " << pshm << std::endl;

    for (int i(0); i < 3; i++) {
        std::cout << "Read data: " << (int)*(pshm + i);
        std::cin.get();
    }

    std::cout << "Finish reading shared memory\n";
    std::cin.get();
    return 0;
}
