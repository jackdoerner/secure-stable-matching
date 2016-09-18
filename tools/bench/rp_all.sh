#!/bin/bash

ITERATIONS="30"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
CLIENT=false

set -e

while getopts ":p:c:i:" opt; do
	case $opt in
		c)
			BENCH_PROG_ARGS+="-c $OPTARG "
			CLIENT=true
			;;
		p)
			BENCH_PROG_ARGS+="-p $OPTARG "
			;;
		i)
			ITERATIONS=$OPTARG
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			exit 1
			;;
		:)
			echo "Option -$OPTARG requires an argument." >&2
			exit 1
			;;
	esac
done
	
eval "$SCRIPT_DIR/rp_proposers.sh $BENCH_PROG_ARGS -i $ITERATIONS"
eval "$SCRIPT_DIR/rp_reviewers.sh $BENCH_PROG_ARGS -i $ITERATIONS"
eval "$SCRIPT_DIR/rp_proposer_pref_bound.sh $BENCH_PROG_ARGS -i $ITERATIONS"
eval "$SCRIPT_DIR/rp_reviewer_pref_bound.sh $BENCH_PROG_ARGS -i $ITERATIONS"
eval "$SCRIPT_DIR/rp_reviewer_pos_bound.sh $BENCH_PROG_ARGS -i $ITERATIONS"