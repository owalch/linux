#!/bin/bash
set -e

echo "### Arrays"
# Array with 4 elements
ARRAY=( 'Hot Dog' 'MC Donalds' Fridge Pepper )
# Get number of elements
ELEMENTS=${#ARRAY[@]}

# print each element in array 
for (( i=0;i<$ELEMENTS;i++)); do
    echo ${ARRAY[${i}]}
done

exit 0
