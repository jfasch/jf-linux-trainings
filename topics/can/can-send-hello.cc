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

    can_frame frame;
    memset(&frame, 0, sizeof(frame));
    frame.can_id = 42;
    frame.can_dlc = 6;
    frame.data[0] = 'h';
    frame.data[1] = 'e';
    frame.data[2] = 'l';
    frame.data[3] = 'l';
    frame.data[4] = 'o';
    frame.data[5] = '\0';

    can.write(&frame, sizeof(frame));

    return 0;
}
