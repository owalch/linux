#!/bin/bash
set -e

echo "### reading user input"

echo -e "Type your name: \c"
read  NAME
echo -e "Please enter ZIP and City: \c"
read ZIP CITY
echo -e "Your Name is \"$NAME\" \c"
echo -e "and you live in  \"$ZIP $CITY\""

echo -e "Which day is today?"
# read into the default build-in variable $REPLY
read
echo "$REPLY, Thanks!"

echo -e "Give me three letters "
# -a reads into an array
read -a LETTERS
echo "Your letters are ${LETTERS[0]}, ${LETTERS[1]} and ${LETTERS[2]}"

exit 0
