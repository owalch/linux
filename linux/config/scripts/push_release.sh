#!/bin/bash
set -e

### path declaration -----------------------------------------------------------
DST_PATH=/home/$USER/mnt/dublin/www/releases/
RELEASES=/home/$USER/projects/releases/
WWW_PATH=dublin.zhaw.ch/~$USER/releases/

REL_LOG=${RELEASES}release_log.txt
ACCESS=${DST_PATH}.htaccess


### check if root --------------------------------------------------------------
if [ $UID -ne 0 ]; then
    echo "error: $0 must be executed as root"
    echo "e.g. sudo bash"
    exit 1
fi


### check user arguments -------------------------------------------------------
if [ $# -ne 3 ]; then
    echo "usage: push_release <paht_bin> <username> <password>"
    exit 1
else
    BINARY=$1
    USER=$2
    PASSWD=$3
    WWW_PATH=${WWW_PATH}$BINARY
fi

### check if www is mounted ----------------------------------------------------
if [ ! -d $DST_PATH ]; then
    echo "can not access $DST_PATH"
    exit 1
fi


### copy binary ----------------------------------------------------------------
cp $BINARY $DST_PATH


### generate password & write log file
HT_PASSWD=`htpasswd -nb $USER $PASSWD`
echo "$HT_PASSWD"                                       >${DST_PATH}htpasswd_tmp


### write release log ----------------------------------------------------------
echo "date      `date +%F" "%T`"                        >> $REL_LOG
echo "file      $BINARY"                                >> $REL_LOG
echo "user      $USER"                                  >> $REL_LOG
echo "passwd    $PASSWD"                                >> $REL_LOG
echo "htpasswd  $HT_PASSWD"                             >> $REL_LOG
echo "path      $WWW_PATH"                              >> $REL_LOG
echo "------------------------------------------------" >> $REL_LOG


### create htaccess ------------------------------------------------------------
if [ ! -f $ACCESS ]; then # file does not exist
    echo "AuthUserFile /home/staff/$USER/.htpasswd" 		> $ACCESS
    echo "AuthType Basic"                               >>$ACCESS
    echo "AuthName \"File upload\""                     >>$ACCESS
    echo                                                >>$ACCESS
    echo "<Files \"$BINARY\">"                          >>$ACCESS
    echo "    Require valid-user"                       >>$ACCESS
    echo "</Files>"                                     >>$ACCESS
    echo                                                >>$ACCESS
else # file exists
    echo "<Files \"$BINARY\">"                          >>$ACCESS
    echo "    Require valid-user"                       >>$ACCESS
    echo "</Files>"                                     >>$ACCESS
    echo                                                >>$ACCESS
fi

### copy password to the server ------------------------------------------------
ssh_log=`ssh $USER@dublin.zhaw.ch "cat /home/staff/$USER/www/releases/htpasswd_tmp>>.htpasswd"`

### clean up -------------------------------------------------------------------
rm -f ${DST_PATH}htpasswd_tmp

### print mail log -------------------------------------------------------------
echo "----------------------------Upload done----------------------------------"
echo "user:     $USER"
echo "passwd:   $PASSWD"
echo "path:     $WWW_PATH"
echo "------------------------------FINISHED-----------------------------------"

exit 0
