#!/bin/bash

args="--add=1 --sub=1 --isub=1 --mul=2 --div=2 --idiv=2 --add-saturate=1 --sub-saturate=1 --isub-saturate=1 --pow=2 --log --abs --min=1 --max=1 --neg --greyscale --kern=kern/gausian_blur.kern3x3 --kern=kern/gausian_blur.kern5x5"

echo ======================================
for arg in $args; do
    sum_s0=0
    for i in {1..10}; do
        sum_s0=$(( $(./aor2p res/gouldian_finch.png $arg $arg $arg $arg $arg -o=benchmark_output.png -s0 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev) + $sum_s0 ))
    done 

    sum_s3=0
    for i in {1..10}; do
        sum_s3=$(( $(./aor2p res/gouldian_finch.png $arg $arg $arg $arg $arg -o=benchmark_output.png -s3 --thread-count=4 | grep 'time taken' | awk '{print $3}' | rev | cut -c 3- | rev) + $sum_s3 ))
    done
    
    s0_avg=$( bc <<< "scale=2; $sum_s0 / 50" )
    s3_avg=$( bc <<< "scale=2; $sum_s3 / 50" )
    relative=$( bc <<< "scale=2; $s0_avg / $s3_avg" )
    echo $arg
    echo --------------------------------------
    printf "s0_avg: %10sns\n" $(( $sum_s0 / 50 ))
    printf "s3_avg: %10sns\n" $(( $sum_s3 / 50 ))
    echo --------------------------------------
    printf "relative: %8sx\n" $relative
    echo ======================================
done

