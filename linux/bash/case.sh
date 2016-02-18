#!/bin/bash
set -e

echo "What is your preferred meal"
echo "1) Pizza"
echo "2) Lasagne"
echo "3) Spaghetti"
echo "4) Rice"
echo "5) MC Donalds"
echo "6) Can't decide"
read case;
case $case in
    1) echo "You like Pizza";;
    2) echo "You like Lasagne";;
    3) echo "You like Spaghetti";;
    4) echo "You like Rice+";;
    5) echo "You like MC Donalds";;
    6) exit
esac 

exit 0
