#!/bin/bash
set -e

echo "### If, than, else expressions"
EXP_1="fool"
EXP_2="foo"

if [ "$EXP_1" = "foo" ] ; then
    echo "if 1 = true"
else if [ "$EXP_2" = "foo" ] ; then
    echo "if 2 = true"
else
    echo "both ifs failed"
    fi
fi
echo

DIRECTORY="../bash"
# check if directory exists
if [ -d $DIRECTORY ] ; then
    echo "Directory \"$DIRECTORY\" exists"
else
    echo "Directory \"$DIRECTORY\" does not exist"
fi
echo

echo "=== Nested if"
# Declare variable choice and assign value 4
choice=4
echo "1. Fish"
echo "2. Chicken"
echo "3. Beef"
echo -n "Choose a number [1,2 or 3]? "

# Loop while the variable choice is equal 4
# bash while loop
while [ $choice -eq 4 ]; do
 
# read user input
read choice
# bash nested if/else
if [ $choice -eq 1 ] ; then
    echo "You have chosen Fish"
else                   
    if [ $choice -eq 2 ] ; then
        echo "You have chosen Chicken"
    else
        if [ $choice -eq 3 ] ; then
            echo "You have chosen Beef"
        else
            echo "Please make a choice between 1-3 !"
            echo "1. Fish"
            echo "2. Chicken"
            echo "3. Beef"
            echo -n "Choose a number [1,2 or 3]? "
            choice=4
        fi   
    fi
fi
done 
echo

echo "=== Check integers"
# declare integers
NUM1=2
NUM2=3
if [ $NUM1 -eq $NUM2 ]; then
    echo "Both Values are equal"
elif [ $NUM1 -gt $NUM2 ]; then 
    echo "Number 1 is greater then number 2"
elif [ $NUM2 -gt $NUM1 ]; then 
    echo "Number 2 is greater then number 1"
fi
echo
((NUM2--))
if [ $NUM1 -eq $NUM2 ]; then
    echo "Both Values are equal"
fi
echo

echo "=== String comparison"
echo "  =       equal"
echo "  !=      not equal"
echo "  <       less then"
echo "  >       greater then"
echo "  -n s1   string s1 is not empty"
echo "  -z s1   string s1 is empty"
echo

echo "=== File testing"
echo "-b filename       Block special file"
echo "-c filename       Special character file"
echo "-d directoryname  Check for directory existence"
echo "-e filename       Check for file existence"
echo "-f filename       Check for regular file existence not a directory"
echo "-G filename       Check if file exists and is owned by effective group ID."
echo "-g filename       true if file exists and is set-group-id."
echo "-k filename       Sticky bit"
echo "-L filename       Symbolic link"
echo "-O filename       True if file exists and is owned by the effective user id."
echo "-r filename       Check if file is a readable"
echo "-S filename       Check if file is socket"
echo "-s filename       Check if file is nonzero size"
echo "-u filename       Check if file set-ser-id bit is set"
echo "-w filename       Check if file is writable"
echo "-x filename       Check if file is executable"


exit 0
