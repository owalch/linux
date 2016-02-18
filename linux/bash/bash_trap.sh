#!/bin/bash
set -e

echo "### bash trap command"
trap bashtrap INT

# clear screen
clear;

# bash trap function is executed when CTRL-C is pressed
bashtrap() {
    echo "CTRL+C Detected"
    echo "-> executing bash trap"
}

# # for loop from 1/10 to 10/10
# for a in `seq 1 10`; do
#     echo "$a/10 to Exit." 
#     sleep 1;
# done

for (( i=0;i<10;i++)); do
    echo "$i/10 to Exit" 
    sleep 1;
done
echo "Exit Bash Trap Example!!!" 

exit 0
