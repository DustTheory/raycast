#!/bin/bash
make tests 1> /dev/null &&
for testBinary in ./build_tests/*; do
    printf "\n\nRUNNING TESTS FOR $testBinary \n"
    $testBinary
done