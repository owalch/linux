#!/bin/bash
set -e

### global arguments ----------------------------------------------------------
prp1_ip="192.168.1.22"
executable="prp_pcap_tap_userspace"
def_ifaceA="eth0"
def_ifaceB="eth1"
prp1_stack="/home/$USER/projects/prp/trunk/"


### set root id ---------------------------------------------------------------
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root" 1>&2
    exit 1
fi

### check arguments -----------------------------------------------------------
if [ $# -ne "2" ]; then
    ifaceA=$def_ifaceA
    ifaceB=$def_ifaceB
    echo "using default interfaces"
    echo "$def_ifaceA -> LanA"
    echo "$def_ifaceB -> LanB"
else
    ifaceA=$1
    ifaceB=$2
    echo "$ifaceA -> LanA"
    echo "$ifaceB -> LanB"
fi

### compile software stack
cd $prp1_stack/sw_stack_prp1/prp_pcap_tap_userspace/
if [ ! -f $executable ]; then
    make
fi

### configure interface ------------------------------------------------------
(
sleep 1.5
ifconfig prp1 $prp1_ip
echo "set prp1 to $prp1_ip"
) &

### run stack -----------------------------------------------------------------
./$executable $ifaceA $ifaceB

