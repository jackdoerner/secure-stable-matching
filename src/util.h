#pragma once

void ocTestUtilTcpOrDie(struct ProtocolDesc* pd,bool isServer,const char* port);
uint64_t current_timestamp();
uint32_t rand_range(uint32_t, uint32_t);

