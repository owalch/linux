#!/bin/bash
set -e

echo "=== Different for loops"
# for loop from 1/10 to 10/10
for a in `seq 1 5`; do
    echo "$a/5" 
    sleep 1;
done

echo
# the same with other syntax
for (( i=0;i<5;i++)); do
    echo "$i/5" 
    sleep 1;
done
echo

echo "=== Loop ls"
for f in $( ls ../ ); do
    echo $f
done 

exit 0
