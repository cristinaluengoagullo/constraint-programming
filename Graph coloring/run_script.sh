#!/bin/bash

TIME_LIMIT=15 # In secs.
BENCH_DIR=instances
EXE=./coloring

######## DO NOT CHANGE BELOW THIS LINE ########

ulimit -t $TIME_LIMIT

n_solved=0
n_all_pb=0
total_time=0
for ifile in $BENCH_DIR/*.pb; do
    ofile=$ifile.out
    /usr/bin/time -f "%e" $EXE $ifile &> tmp.txt
    if [ $? != 0 ]; then
	echo "Timed out: $ifile"
    else
	echo "OK       : $ifile"
	n_solved=$(( n_solved+1 ))
	time=$(tail -n 1 tmp.txt)
	total_time=$(echo "$total_time + $time" | bc)
    fi
    n_all_pb=$(( n_all_pb+1 ))
done
echo "Time solved problems: $total_time"
echo "Num. solved problems: $n_solved"
echo "Num.  all   problems: $n_all_pb"
perc=$(echo "scale=2; (100*$n_solved)/$n_all_pb" | bc )
echo "Percentage: $perc %"
rm --force tmp.txt
