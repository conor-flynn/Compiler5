#!/bin/sh

target="$1"

sol 		="./dcc"
sol_output 	="22.asm"
spim_output ="22.out"

rm -f $sol_output
rm -f $spim_output

$sol < $target > $sol_output 
spim -file $sol_output > $spim_output 2>&1