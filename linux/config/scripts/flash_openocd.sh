#!/bin/bash
#
# Flash script for the Luminary board
#
set -e

#
# test root
#
if test $UID -ne 0
then
    echo "Be root!"
    echo "---> sudo bash"
    exit 0
fi

#
# check arguments
#
if test $# -lt 1
then
    echo "Use: flash_openocd <path_.bin>"
    echo $#
    exit 0
fi


#
# start telnet
#
(
    sleep 1;
    {
    echo "halt";
    echo "flash write_image erase $1";
    sleep 15;
    echo "reset";
    sleep 2;
    echo "exit";
    sleep 1;
    } | telnet localhost 4444
) &


#
# start debugger
#
openocd -f /home/$USER/projects/luminary/luminary-icdi.cfg -f /home/$USER/projects/luminary/stellaris.cfg



