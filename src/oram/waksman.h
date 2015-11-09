#pragma once
#include<stdbool.h>
#include<stddef.h>

size_t waksmanSwapCount(size_t n);
size_t waksmanNetwork(unsigned a[],unsigned b[],size_t n);
size_t waksmanSwitches(const unsigned arr[],unsigned n,bool output[]);

size_t waksmanStrataCount(size_t n);
void waksmanStratify(unsigned a[],unsigned b[],bool switches[],
                     size_t n,size_t strata_sizes[]);
