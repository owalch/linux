#!/bin/bash
set -e

VAL1=20
VAL2=5

echo "=== Addition"
let SUM=$VAL1+$VAL2
echo "$VAL1 + $VAL2 = $SUM"

echo "=== Subtraction"
((SUB=$VAL1-$VAL2))
echo "$VAL1 - $VAL2 = $SUB"

echo "=== Multiplication"
((MUL=$VAL1*$VAL2))
echo "$VAL1 * $VAL2 = $MUL"

echo "=== Division"
((DIV=$VAL1/$VAL2))
echo "$VAL1 / $VAL2 = $DIV"

echo "=== Modulus"
((MOD=$VAL1 % $VAL2+1))
echo "$VAL1 % $VAL2 = $MOD"

echo "=== Power of "
((POW=$VAL1 ** $VAL2))
echo "$VAL1 ** $VAL2 = $POW"



exit 0
