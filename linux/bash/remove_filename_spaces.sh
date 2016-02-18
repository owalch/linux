#!/bin/bash
set -e

# locate and replace spaces in the filenames
DIR="."
find $DIR -type f | while read file; do
    # using POSIX class [:space:] to find spaces
    if [[ "$file" = *[[:space:]]* ]]; then
        # substitute space with "_" character and consequently rename the file
        mv "$file" `echo $file | tr ' ' '_'`
        echo "changelog: $file "
    fi;
done 