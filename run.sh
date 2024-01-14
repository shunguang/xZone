#!/bin/bash

# run cp ../../run.sh run.sh
# to copy this file to the linux build directory (build/bin/)

for transport in 1 2 3
do
    export XZONE_TRANSPORT=$transport
    ./test.out config.xml & 
    testPid=$!
    ./imagePub.out config.xml pcktsz 15000 &
    imagePubId=$!

    # Check if the process is still running
    while kill -0 $imagePubId 2> /dev/null; do
        sleep 1
    done

    echo "killing test.out (PID $testPid)"
    kill -9 $testPid

    wait
done