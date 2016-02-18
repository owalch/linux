#!/bin/bash
set -e

# Declare array
declare -a ARRAY

# Link filedescriptor 10 with stdin
exec 10<&0

# stdin replaced with a file supplied as a first argument
echo "Dies ist der Inhalt des temp files" >tmpfile
echo "Und noch eine zweite Zeile mit Kommentar" >>tmpfile
exec < tmpfile
let INDEX=0

while read LINE; do

    ARRAY[$INDEX]=$LINE
    ((INDEX++))
done

echo Number of elements: ${#ARRAY[@]}
# echo array's content
echo ${ARRAY[@]}

# restore stdin from filedescriptor 10 and close filedescriptor 10
exec 0<&10 10<&-

# if ( tmpfile -r ) ; then
#     rm tmpfile
# fi

exit 0
