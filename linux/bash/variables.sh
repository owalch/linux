#!/bin/bash
set -e

# global variable
echo "### Variables"
VAR="global variable"
function global_vs_local {
    # Define local variable
    local VAR="local variable"
    echo $VAR
}
echo $VAR
global_vs_local

echo $VAR

exit 0
