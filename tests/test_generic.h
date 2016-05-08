#ifndef TEST_GENERIC_H
#define TEST_GENERIC_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "ackutil.h"

#define STATUS_SUCCESS "\e[32m[SUCCESS]\e[0m"
#define STATUS_FAILURE "\e[31m[FAILURE]\e[0m"

#ifndef REMOTE_HOST
#define REMOTE_HOST localhost
#endif

#define QUOTE(x) #x
#define TO_STRING(x) QUOTE(x)
static const char remote_host[] = TO_STRING(REMOTE_HOST);
#undef TO_STRING
#undef QUOTE

void ocTestUtilTcpOrDie(ProtocolDesc* pd,bool isServer,const char* port);

char* testName();

void testMain(void*varg);

#endif