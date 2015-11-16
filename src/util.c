#include<obliv.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"util.h"

#ifndef REMOTE_HOST
#define REMOTE_HOST localhost
#endif

#define QUOTE(x) #x
#define TO_STRING(x) QUOTE(x)
static const char remote_host[] = TO_STRING(REMOTE_HOST);
#undef TO_STRING
#undef QUOTE

uint64_t current_timestamp() {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
	//struct timespec t;
	//clock_gettime(CLOCK_REALTIME,&t);
	//return t.tv_sec+1e-9*t.tv_nsec;
}

uint32_t rand_range(uint32_t min, uint32_t max) {
	return (uint32_t)((double) rand() / ((uint64_t)RAND_MAX+1)) * (max-min+1) + min;
}

void ocTestUtilTcpOrDie(ProtocolDesc* pd,bool isServer,const char* port)
{
	if(isServer)
	{ if(protocolAcceptTcp2P(pd,port)!=0)
		{ fprintf(stderr,"TCP accept failed\n");
			exit(1);
		}
	}
	else 
		if(protocolConnectTcp2P(pd,remote_host,port)!=0) 
		{ fprintf(stderr,"TCP connect failed\n");
			exit(1);
		}
}
