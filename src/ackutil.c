#include<obliv.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"ackutil.h"

uint64_t current_timestamp() {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (uint64_t)tv.tv_sec*(uint64_t)1000000+(uint64_t)tv.tv_usec;
}

uint32_t rand_range(uint32_t min, uint32_t max) {
	return (uint32_t)((double) rand() / ((uint64_t)RAND_MAX+1)) * (max-min+1) + min;
}
