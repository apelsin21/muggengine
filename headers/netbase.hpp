#ifndef NETBASE_HPP
#define NETBASE_HPP

#include <enet/enet.h>

namespace mugg {
    namespace net {
        class NetBase {
            protected:
                ENetAddress address;
                ENetHost* host;
                ENetEvent event;
            
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
        };
    }
}

#endif
