#!/bin/bash
set -e

echo "### Passing Arguments"
echo "-> \$1 = $1"
echo "-> \$2 = $2"
echo "-> \$@ = $@"
echo "-> \$# = $# (Number of Arguments)"

# Store arguments from bash command line in an array
args=("$@")
# use one argument
echo "Array[0]=${args[0]}"
echo "Array[1]=${args[1]}"

exit 0
