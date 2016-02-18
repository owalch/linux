#!/bin/bash
set -e

# %j gives the number of days since the year's beginning
echo "The number of days since the year's beginning is `date +%j`"

# %s yields number of seconds since "UNIX epoch" began
echo "The number of seconds elapsed since 01/01/1970 is `date +%s`"

# example for a %s usage
PREFIX=temp
SUFFIX=`date +%s`
FILENAME=$PREFIX.$SUFFIX
echo "Temporary filename = $FILENAME"

# usage of date cmd
YEAR=`date +%y`
MONTH=`date +%m`
DAY=`date +%d`
echo "We are in 20$YEAR, $DAY.$MONTH"
echo "or shortform: `date +%d"."%m"."%y`"