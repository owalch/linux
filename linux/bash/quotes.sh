#!/bin/bash
set -e

# Declare bash string variable
BASH_VAR="Bash Script"

# echo variable BASH_VAR
echo $BASH_VAR

# when meta character such us "$" is escaped with "\" it will be read literally
echo \$BASH_VAR 

# backslash has also special meaning and it can be suppressed with yet another "\"
echo "\\"

# meta characters special meaning in bash is suppressed when using single quotes 
echo '$BASH_VAR  "$BASH_VAR"'

# meta characters and its special meaning in bash is 
# suppressed when using double quotes except "$", "\" and "`"
echo "It's $BASH_VAR  and \"$BASH_VAR\" using backticks: `date`" 
echo
echo "=== Bash quoting Overview"
echo "\a    alert (bell)"
echo "\b    backspace"
echo "\e    an escape character"
echo "\f    form feed"
echo "\n    newline"
echo "\r    carriage return"
echo "\t    horizontal tab"
echo "\v    vertical tab"
echo "\\    backslash"
echo "\`    single quote"
echo "\nnn  octal value of characters"
echo "\xnn  hexadecimal value of characters"
echo "\b    backspace"

echo $'info\x40walcholi\x2e.ch'

exit 0
