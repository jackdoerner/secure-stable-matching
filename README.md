Secure Stable Matching at Scale
=====

This repository provides code to accompany the paper [Secure Stable Matching at Scale](http://oblivc.org/docs/matching.pdf) by Jack Doerner, David Evans, and abhi shelat, which appeared in the 23rd ACM Conference on Computer and Communications Security (CCS). It is, in essence, a version of the [Absentminded Crypto Kit](https://bitbucket.org/jackdoerner/absentminded-crypto-kit) pared down until it contains only what is necessary to reproduce the results presented. As such, it takes the form of a library, along with a small number of testing and benchmarking applications. Bear in mind, further development will take place in the [main ACK repository](https://bitbucket.org/jackdoerner/absentminded-crypto-kit).


Installing
=====

1. You must first build [obliv-c](https://github.com/samee/obliv-c/), though it need not be installed in any particular location. In addition to obliv-c, you will need to install the package `openssl-dev` (or your distribution's equivalent). This is necessary only for test cases for SHA256 and SHA512.

2. To compile ACK, set the path to obliv-c's main project directory via `export OBLIVC_PATH=<path to obliv-c>`, then run `make`.


Project Organization
=====

Source for this project is divided into two directories: `src` contains code for the primary library, while `tests` contains code for tests and benchmarks. The library will be compiled to `build/lib/liback.a`, and all testing and benchmarking binaries are found in `build/tests`. Benchmarking scripts can be found in `bench`.


Reproducing Results
=====


Building on this Work
=====