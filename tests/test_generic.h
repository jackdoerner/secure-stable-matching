#ifndef TEST_GENERIC_H
#define TEST_GENERIC_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

#define STATUS_SUCCESS "\e[32m[SUCCESS]\e[0m"
#define STATUS_FAILURE "\e[31m[FAILURE]\e[0m"

char* testName();

void testMain(void*varg);

#endif