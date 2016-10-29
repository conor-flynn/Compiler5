#!/bin/sh

target="$1"

./answer.sh $target




solution="./dcc"
actual_destination="a_output_actual.asm"
normal_destination="a_output_normal.asm"

rm -f $normal_destination

$normal_solution < $target > $normal_destination



diff $actual_destination $normal_destination