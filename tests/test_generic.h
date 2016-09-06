#ifndef TEST_GENERIC_H
#define TEST_GENERIC_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <math.h>

#include "ackutil.h"

#define STATUS_SUCCESS "\e[32m[SUCCESS]\e[0m"
#define STATUS_FAILURE "\e[31m[FAILURE]\e[0m"

#define QUOTE(x) #x
#define TO_STRING(x) QUOTE(x)

#ifndef DEFAULT_REMOTE_HOST
#define DEFAULT_REMOTE_HOST localhost
#endif
static const char default_remote_host[] = TO_STRING(DEFAULT_REMOTE_HOST);

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 54321
#endif
static const char default_port[] = TO_STRING(DEFAULT_PORT);

#undef TO_STRING
#undef QUOTE

#define TEXT_HELP_GENERAL "liback testing and benchmark utility\n\
\n\
Options:\n\
  -h \n\t\tprint this message\n\n\
  -c \x1b[4mADDRESSS\x1b[0m \n\t\trun as client and connect to \x1b[4mADDRESS\x1b[0m\n\n\
  -p \x1b[4mNUMBER\x1b[0m \n\t\tlisten or connect on port \x1b[4mNUMBER\x1b[0m\n\n"

typedef struct args_t {
	int argc;
	char **argv;
} args_t;

void ocTestUtilTcpOrDie(ProtocolDesc* pd, bool isServer, const char* remote_host, const char* port);

char* get_test_name();

char* get_supplementary_options_string();

struct option* get_long_options();

void print_supplmentary_help();

void test_main(void*varg);

#endif