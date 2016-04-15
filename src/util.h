#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <obliv_common.h>

void ocTestUtilTcpOrDie(struct ProtocolDesc* pd,bool isServer,const char* port);
uint64_t current_timestamp();
uint32_t rand_range(uint32_t, uint32_t);

#endif

