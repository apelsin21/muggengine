#include "stringpacket.hpp"

mugg::net::StringPacket::StringPacket() {
    this->data = "";
    this->flag = mugg::net::PacketFlag::Reliable;
}
mugg::net::StringPacket::StringPacket(const char* data, mugg::net::PacketFlag flag) {
    this->SetData(data, flag);
}

void mugg::net::StringPacket::SetData(const char* data, mugg::net::PacketFlag flag = mugg::net::PacketFlag::Reliable) {
    this->data = data;
    this->flag = flag;

    this->SetFlag(flag);

    this->size = strlen(data);

    this->packet = enet_packet_create(data, this->size + 1, this->internalFlag);
}
void mugg::net::StringPacket::AppendData(const char* data) {
    std::size_t tempSize = this->size;    
    this->size = tempSize + strlen(data);
    
    enet_packet_resize(this->packet, this->size + 1);
    strcpy((char*)&this->packet->data[tempSize], data);
}
void mugg::net::StringPacket::Truncate(std::size_t size) {
    enet_packet_resize(this->packet, this->size - size);
}
const char* mugg::net::StringPacket::GetData() {
    return this->data;
}
