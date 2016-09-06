The Absentminded Crypto Kit
=====

This project seeks to develop a comprehensive Cryptographic SDK for use in secure multi-party computation. It supports a growing number of useful mathematical cryptographic primitives with efficient implementations based upon recent research, simplifying the development of complex applications in a secure multi-party context. In addition, it includes a number of useful non-cryptographic algorithms, such as Stable Matching and Breadth-first Search. It also includes a comprehensive set of test cases and benchmarks. The ACK library is written in [obliv-c](https://github.com/samee/obliv-c/), a c-derived language for secure multiparty computation. Primary development is undertaken by Jack Doerner. Thanks also to Samee Zahur and Xiao Wang for their contributions.


Features
=====

* Batcher Sorting and Merging - based upon [Sorting Networks and their Applications](http://www.cs.kent.edu/~batcher/sort.pdf)
* Big Integer math
	* Division via Knuth's Algorithm D - based upon The Art of Computer Programming Vol 2, Section 4.3.1
	* Karatsuba-Comba Multiplication
	* Square Root via Newton's Method
* Binary Search
* Graph Algorithms
	* Breadth First Search (Naive Method)
* Oblivious Data Structures
	* Queue - based upon [Circuit Structures for Improving Efficiency of Security and Privacy Tools](http://www.ieee-security.org/TC/SP2013/papers/4977a493.pdf)
* ORAM
	* Circuit ORAM - based upon [Circuit Oram: On Tightness of the Goldreich-Ostrovsky Lower Bound](https://eprint.iacr.org/2014/672.pdf); code contributed by Xiao Wang
	* Linear Scan ORAM
	* Square Root ORAM - based upon [Revisiting Square-Root ORAM: Efficient Random Access in Multi-Party Computation](https://oblivc.org/docs/sqoram.pdf); code contributed by Samee Zahur
* Hash Functions
	* ChaCha20 - based upon [ChaCha, a Variant of Salsa20](https://cr.yp.to/chacha/chacha-20080128.pdf)
	* Salsa20 - based upon [The Salsa20 Family of Stream Ciphers](https://cr.yp.to/snuffle/salsafamily-20071225.pdf)
	* Scrypt - based upon [Stronger Key Derivation via Sequential Memory-hard Functions](https://www.tarsnap.com/scrypt/scrypt.pdf)
	* SHA256 and SHA512
* Stable Matching
	* Gale-Shapley - based upon [Secure Stable Matching at Scale](http://oblivc.org/docs/matching.pdf)
	* Roth-Peranson - based upon [Secure Stable Matching at Scale](http://oblivc.org/docs/matching.pdf)


Installing
=====

1. You must first build [obliv-c](https://github.com/samee/obliv-c/), though it need not be installed in any particular location. In addition to obliv-c, you will need to install the package `openssl-dev` (or your distribution's equivalent). This is necessary only for test cases for SHA256 and SHA512.

2. To compile ACK, set the path to obliv-c's main project directory via `export OBLIVC_PATH=<path to obliv-c>`, then run `make`.


Project Organization
=====

Source for this project is divided into two directories: `src` contains code for the primary library, while `tests` contains code for tests and benchmarks. The library will be compiled to `build/lib/liback.a`, and all testing and benchmarking binaries are found in `build/tests`.