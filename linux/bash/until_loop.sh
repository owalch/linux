#/!bin/bash
set -e

COUNTER=0
until [ $COUNTER -gt 5 ]; do
    echo Counter is: $COUNTER
    let COUNTER=COUNTER+1
#     ((COUNTER++))
done

exit 0
