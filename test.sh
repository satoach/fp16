#!/bin/bash

function expect () {
    result=`./target $1`
    echo -n "$result vs $2: "
    if [ $result == $2 ]; then
        echo "OK"
    else
        echo "NG"
        exit 1
    fi
}

expect 1 0x3c00
expect 0.2 0x3266
expect -0.7 0xb999
expect 0.0 0x0000
expect -0.0 0x8000
expect 1.0009765625 0x3c01
expect 1.001953125 0x3c02
expect 1.9990234375 0x3fff
expect 2 0x4000
expect -2 0xc000
expect 65472 0x7bfe
expect 65504 0x7bff
expect -65504 0xfbff
# expect infinity(+) 0x7c00
# expect infinity(-) 0xfc00
expect 0.33325 0x3554
