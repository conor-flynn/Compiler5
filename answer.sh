#!/bin/sh

target="$1"

actual_solution="./solutions/dcc"
actual_destination="a_output_actual.asm"

rm -f $actual_destination

$actual_solution < $target > $actual_destination