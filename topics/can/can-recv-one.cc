#include <jf/can.h>

#include <iostream>
#include <cstdlib>
#include <cstring>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << argv[0] << " <ifacename>" << std::endl;
        exit(1);
    }

    jf::CAN_Raw can(argv[1]);

    struct can_frame frame;
    can.read(&frame, sizeof(frame));

    std::cout << frame.can_id << ':';
    std::cout.write((const char*)frame.data, frame.can_dlc);
    std::cout << std::endl;

    return 0;
}
