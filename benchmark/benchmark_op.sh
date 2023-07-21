#!/bin/bash

echo ======================================
sum_s3=0
for i in {1..100}; do
    sum_s3=$(( $(./aor2p res/gouldian_finch.png $@ $@ $@ $@ $@ -o=benchmark_output.png -s3 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev) + $sum_s3 ))
done

echo $arg
echo --------------------------------------
printf "s3_avg: %10sns\n" $(( $sum_s3 / 500 ))
echo ======================================

