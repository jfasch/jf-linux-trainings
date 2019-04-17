#ifndef JF__TOPICS__MESSAGE_PASSING_COMPONENTS__PROTOCOLS_H
#define JF__TOPICS__MESSAGE_PASSING_COMPONENTS__PROTOCOLS_H

#include <string>
#include <cstdint>

struct message_A
{
    enum class request: uint16_t {
        SAYHELLO, // payload: null terminated string
        SAYHELLO_DELEGATE_TO_B, // payload: null terminated string
    };
    
    request request;
    char payload[126];
};

static const std::string queue_name_A = "/ComponentA";

struct message_B
{
    enum class request: uint16_t {
        SAYHELLO, // payload: null terminated string
    };

    request request;
    char payload[126];
};

static const std::string queue_name_B = "/ComponentB";

#endif
