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
                unsigned int inLimit, outLimit;
                bool initialized;
            public:
                int GetMaxConnections() {
                    return this->maxConnections;
                }
                int GetMaxChannels() {
                    return this->maxChannels;
                }
                unsigned int GetInLimit() {
                    return this->inLimit;
                }
                unsigned int GetOutLimit() {
                    return this->outLimit;
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
