#!/bin/bash
set -e

VAR=Hello

# function to print world
function hello {
    local VAR=World
    echo $VAR
}
echo $VAR
hello
echo

echo "=== Pass argument to function"
function call_date {
    if [ "$1" = "short" ] ; then
        echo `date +%d"."%m"."%y`
    fi
    if [ "$1" = "middle" ] ; then
        echo `date +%a" "%d". "%b" "%G`
    fi
    if [ "$1" = "long" ] ; then
        echo `date +%A" "%d". "%B" "%G`
    fi
}


# call the function
call_date "short"
call_date "middle"
call_date "long"

exit 0
