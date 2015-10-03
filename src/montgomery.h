#pragma once
#define BYTES 4

void montgomeryMain(void*varg);

typedef struct {
  char x[BYTES];
  char n[BYTES];
  char m[BYTES];
  char result[BYTES];
} protocolIO;