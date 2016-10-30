#!/bin/sh

target="$1"

sol="./solutions/dcc"
sol_output="11.asm"
spim_output="11.out"

rm -f $sol_output
rm -f $spim_output

$sol < $target > $sol_output 2>&1
spim -file $sol_output > $spim_output 2>&1