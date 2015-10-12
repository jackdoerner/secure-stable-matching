#pragma once

#define STATUS_SUCCESS "\e[32m[SUCCESS]\e[0m"
#define STATUS_FAILURE "\e[31m[FAILURE]\e[0m"

char* testName();

void testMain(void*varg);