#ifndef NETBASE_HPP
#define NETBASE_HPP

#include <enet/enet.h>

#include "netdefs.hpp"

namespace mugg {
    namespace net {
        class NetBase {
            protected:
                ENetAddress address;
                ENetHost* host = nullptr;
                ENetEvent event;
            
                mugg::net::Event latestEvent;
                std::string latestEventAddress;
                unsigned char* latestEventData;

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
                
                void SetBandwidthLimit(unsigned int inThrottle, unsigned int outThrottle) {
                    enet_host_bandwidth_limit(this->host, inThrottle, outThrottle);
                    this->inLimit = inThrottle;
                    this->outLimit = outThrottle;
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

                std::string AddressToString(ENetAddress address) {
                    unsigned char bytes[4];
                    bytes[0] = address.host & 0xFF;
                    bytes[1] = (address.host >> 8) & 0xFF;
                    bytes[2] = (address.host >> 16) & 0xFF;
                    bytes[3] = (address.host >> 24) & 0xFF;   
                
                    char buffer[100];
                
                    snprintf(buffer, 100, "%d.%d.%d.%d:%d", bytes[0], bytes[1], bytes[2], bytes[3], address.port);
                
                    return std::string(buffer);
                }

                mugg::net::Event GetLatestEvent() {
                    return this->latestEvent;
                }
                std::string GetLatestEventAddress() {
                    return this->latestEventAddress;
                }
                unsigned char* GetLatestEventData() {
                    return this->latestEventData;
                }
        };
    }
}

#endif
