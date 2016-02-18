#!/bin/bash
set -e

PS3="Choose one Console: "

select word in "bash" "hash" "sh" "hasl" 
do
    echo "You selected : $word"
    # Break, otherwise endless loop
    break  
done

exit 0 
