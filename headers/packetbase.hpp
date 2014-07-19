#ifndef PACKETBASE_HPP
#define PACKETBASE_HPP

#include <enet/enet.h>
#include <iostream>

#include "netdefs.hpp"

namespace mugg {
    namespace net {
        class PacketBase {
            protected:
                ENetPacket* packet = nullptr;
                ENetPacketFlag internalFlag;
                mugg::net::PacketFlag flag;
                std::size_t size = 0;
            public:
                void SetFlag(mugg::net::PacketFlag flag) {
                    this->flag = flag;

                    switch(flag) {
                        case mugg::net::PacketFlag::Reliable:
                            this->internalFlag = ENET_PACKET_FLAG_RELIABLE;
                            break;
                        case mugg::net::PacketFlag::Unsequenced:
                            this->internalFlag = ENET_PACKET_FLAG_UNSEQUENCED;
                            break;
                        default:
                            this->internalFlag = ENET_PACKET_FLAG_RELIABLE;
                            break;
                    }
                }
                mugg::net::PacketFlag GetFlag() {
                    return this->flag;
                }

                std::size_t GetSize() {
                    return this->size;
                }

                ENetPacket* GetInternalPacket() {
                    return this->packet;
                }
                void SetInternalPacket(ENetPacket* packet) {
                    this->packet = packet;
                }
        };
    }
}

#endif
