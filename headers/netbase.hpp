#ifndef NETBASE_HPP
#define NETBASE_HPP

#include <enet/enet.h>

#include "netdefs.hpp"

namespace mugg {
    namespace net {
        class NetManager;

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
            
                mugg::net::NetManager* parent;
            public:
                NetBase(mugg::net::NetManager* parent) {
                    this->parent = parent;
                    this->latestEvent = mugg::net::Event::None;
                }

                virtual int GetMaxConnections() {
                    return this->maxConnections;
                }
                virtual int GetMaxChannels() {
                    return this->maxChannels;
                }
                
                virtual void SetBandwidthLimit(unsigned int inThrottle, unsigned int outThrottle) {
                    enet_host_bandwidth_limit(this->host, inThrottle, outThrottle);
                    this->inLimit = inThrottle;
                    this->outLimit = outThrottle;
                }
                virtual unsigned int GetInLimit() {
                    return this->inLimit;
                }
                virtual unsigned int GetOutLimit() {
                    return this->outLimit;
                }
                
                virtual bool IsInitialized() {
                    return this->initialized;
                }

                virtual std::string AddressToString(ENetAddress address) {
                    unsigned char bytes[4];
                    bytes[0] = address.host & 0xFF;
                    bytes[1] = (address.host >> 8) & 0xFF;
                    bytes[2] = (address.host >> 16) & 0xFF;
                    bytes[3] = (address.host >> 24) & 0xFF;   
                
                    char buffer[100];
                
                    snprintf(buffer, 100, "%d.%d.%d.%d:%d", bytes[0], bytes[1], bytes[2], bytes[3], address.port);
                
                    return std::string(buffer);
                }

                virtual mugg::net::Event ClearLatestEvent() {
                    this->latestEvent = mugg::net::Event::None;
                }
                virtual mugg::net::Event GetLatestEvent() {
                    return this->latestEvent;
                }
                virtual std::string GetLatestEventAddress() {
                    return this->latestEventAddress;
                }
                virtual unsigned char* GetLatestEventData() {
                    return this->latestEventData;
                }

                virtual void Poll() {
                }
        };
    }
}

#endif
