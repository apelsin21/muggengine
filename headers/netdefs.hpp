#ifndef NETDEFS_HPP
#define NETDEFS_HPP

namespace mugg {
    namespace net {
        enum Event {
            Received,
            Connected,
            Disconnected,
            None
        };
        static const char* EventString[] = {
            "Received",
            "Connected",
            "Disconnected",
            "None",
            NULL
        };

        enum PacketFlag {
            Reliable,
            Unsequenced,
            Sent
        };
        static const char* PacketFlagString[] = {
            "Reliable",
            "Unsequenced",
            "Sent",
            NULL
        };
    }
}

#endif
