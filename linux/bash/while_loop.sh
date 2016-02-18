#!/bin/bash
set -e

COUNTER=8
while [ $COUNTER -gt 0 ]; do
    echo Counter is: $COUNTER
#     let COUNTER=COUNTER-1
    ((COUNTER--))   # second way to decrement
done

exit 0
