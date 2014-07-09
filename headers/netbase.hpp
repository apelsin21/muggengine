#ifndef NETBASE_HPP
#define NETBASE_HPP

#include <enet/enet.h>

#include "netdefs.hpp"

namespace mugg {
    namespace net {
        class NetBase {
            protected:
                ENetAddress address;
                ENetHost* host;
                ENetEvent event;
            
                mugg::net::Event latestEvent;

                int maxConnections, maxChannels;
                int incThrottle, outThrottle;
                bool initialized;
            public:
                int GetMaxConnections() {
                    return this->maxConnections;
                }
                int GetMaxChannels() {
                    return this->maxChannels;
                }
                int GetIncThrottle() {
                    return this->incThrottle;
                }
                int GetOutThrottle() {
                    return this->outThrottle;
                }
                bool IsInitialized() {
                    return this->initialized;
                }

                mugg::net::Event GetLatestEvent() {
                    return this->latestEvent;
                }
        };
    }
}

#endif
