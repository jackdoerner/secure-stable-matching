Secure Stable Matching at Scale
=====

This repository provides code to accompany the paper [Secure Stable Matching at Scale](http://eprint.iacr.org/2016/861.pdf) by Jack Doerner, David Evans, and abhi shelat, which appeared in the 23rd ACM Conference on Computer and Communications Security (CCS) and is included here. This software is, in essence, a version of the [Absentminded Crypto Kit](https://bitbucket.org/jackdoerner/absentminded-crypto-kit) pared down until it contains only what is necessary to reproduce the results presented. As such, it takes the form of a library, along with a small number of testing and benchmarking applications. Bear in mind, further development will take place in the [main ACK repository](https://bitbucket.org/jackdoerner/absentminded-crypto-kit).


Installing
=====

1. You must first build [obliv-c](https://github.com/samee/obliv-c/), though it need not be installed in any particular location. In addition to obliv-c, you will need to install the package `openssl-dev` (or your distribution's equivalent). This is necessary only for test cases for SHA256 and SHA512.

2. To compile ACK, set the path to obliv-c's main project directory via `export OBLIVC_PATH=<path to obliv-c>`, then run `make`.


Project Organization
=====

Source for this project is divided into two directories: `src` contains code for the primary library, while `tests` contains code for tests and benchmarks. The library will be compiled to `build/lib/liback.a`, and all testing and benchmarking binaries are found in `build/tests`. Benchmarking scripts can be found in `tools/bench`, and they will write their output to `results/bench`. Scripts for visualizing benchmark results can be found in `tools/graph`, and they will write their output to `results/graph`. The Secure Stable Matching at Scale paper may be found in the root directory of the project.


Reproducing Results
=====

For the purpose of reproducing the results we report in our paper, we provide a suite of benchmark scripts in the `bench` directory. Each script must be executed on one machine as a server, and on another as a client. Scripts will run as server by default, and will output data and summaries to the `results` directory. Adding the `-c <address>` flag will cause the script to run as a client and connect to the specified server; in client mode the script will print a summary on the terminal, and will not save raw data. The full list of available benchmarks is as follows:

* Secure Gale-Shapley Execution Time vs Pair Count (Figure 8) - `gs_improved.sh` and `gs_textbook.sh`
* Secure Gale-Shapley Gate Count vs Pair Count (Table 1) - `gs_improved.sh` and `gs_textbook.sh`
* Secure Roth-Peranson Parametric Benchmark Results (Figure 9)
	* Proposer Count (Figure 9a) - `rp_proposers.sh`
	* Reviewer Count Figure (9b) - `rp_reviewers.sh`
	* Proposer Preference Bound Figure (9c) - `rp_proposer_pref_bound.sh`
	* Reviewer Preference Bound Figure (9d) - `rp_reviewer_pref_bound.sh`
	* Reviewer Position Bound Figure (9e) - `rp_reviewer_pos_bound.sh`
* Secure Roth-Peranson NRMP Benchmark Results (Table 2) - `rp_nrmp.sh`


Running Tests and Benchmarks Manually
=====

Each of our benchmarking and testing programs have individual options for adjusting the parameters relevant to that particular test or benchmark. These can be found by running the programs with the `-h` flag. In addition, there are a few standard parameters shared by all of the included programs, as well as the benchmarking scripts:

* `-h` prints a list of program-specific flags.
* `-p <number>` determines the port on which the program will listen (for servers) or connect (for clients). The default port is 54321.
* `-c <address>` instructs the program to run as a client, and connect to the server at `<address>`. By default, the program will run as a server.
* `-o <type>` forces the program to use `<type>` ORAMs. Valid types are `sqrt`, `linear`, and `circuit`.
* `-i <number>` (benchmarks only) instructs a benchmark to run for `<number>` iterations, and record results for all of them.


Building on this Work
=====

We encourage others to improve our work and to integrate it with their own applications. As such, we provide it under the 3-clause BSD license. For ease of integration, our code takes the form of a library, to which other software can link directly.