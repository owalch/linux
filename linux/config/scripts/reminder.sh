#!/bin/bash

gmessage "It is time to chant your Gayatri mantras" -center -title "Take action" -font "Sans bold 7" -geometry 300x100 -default "Remind me later" -center -buttons "_Remind me later":1,"I'll _chant now":2 >/dev/null

case $? in
1)
(sleep 10m && /home/$USER/.scripts/Gayatri_gmessage);;

2)
echo "Exit";;

esac
