The Absentminded Crypto Kit
=====

The ACK library is written in [obliv-c](https://github.com/samee/obliv-c/), a c-derived language for secure multiparty computation.

Thanks to Samee Zahur and Xiao Wang for their contributions.


Features
=====

* Batcher Sorting and Merging
* Big Integer math
	* Division via Knuth's Algorithm D
	* Karatsuba-Comba Multiplication
	* Square Root via Newton's Method
* Binary Search
* Graph Algorithms
	* Breadth First Search (Naive Method)
* Oblivious Data Structures
	* Queue
* ORAM
	* Circuit ORAM
	* Linear Scan ORAM
	* Square Root ORAM
* Hash Functions
	* ChaCha20
	* Salsa20
	* Scrypt
	* SHA256 and SHA512
* Stable Matching
	* Gale-Shapley
	* Roth-Peranson


Installing
=====

1. You must first build [obliv-c](https://github.com/samee/obliv-c/), though it need not be installed in any particular location. In addition to obliv-c, you will need to install the package `openssl-dev` (or your distribution's equivalent). This is necessary only for test cases for SHA256 and SHA512.

2. To compile ACK, set the path to obliv-c's main project directory via `export OBLIVC_PATH=<path to obliv-c>`, then run `make`.


Project Organization
=====

Source for this project is divided into two directories: `src` contains code for the primary library, while `tests` contains code for tests and benchmarks. The library will be compiled to `build/lib/liback.a`, and all testing and benchmarking binaries are found in `build/tests`.