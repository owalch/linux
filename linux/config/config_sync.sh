#!/bin/bash
# ------------------------------------------------------------------------------
# Bash Shell Script
#
# @desc:    Execute this shell script to personalize your PC.
#
# @file:    ~/config/config_sync.sh
# @date:    2014-04-24
# @author:  Oliver Walch
# ------------------------------------------------------------------------------
set -e

# global directories and files
scriptsDir="${HOME}/config/scripts/"
# ------------------------------------------------------------------------------

# check if directory exists
if [ -d "$scriptsDir" ]; then
    echo "Copy scripts to $scriptsDir"
    cp -r scripts/* $scriptsDir
else
    echo "Directory $scriptsDir does not exists, create directory"
    mkdir -p $scriptsDir
    cp -r scripts/* $scriptsDir
fi
echo ">>> scripts copied"
# ------------------------------------------------------------------------------

# replace local bashrc and bash_aliases
cp bashrc ~/.bashrc
cp bash_aliases ~/.bash_aliases
cp bashrc_common ~/.bashrc_common
echo ">>> .bashrc copied"
echo ">>> .bash_aliases copied"
echo ">>> .bashrc_common copied"
# ------------------------------------------------------------------------------

# kate config
cp katerc ~/.kde/share/config/katerc
echo ">>> katerc copied"
# ------------------------------------------------------------------------------

# ssh config
cp ssh_config ~/.ssh/config
# ------------------------------------------------------------------------------

# vim settings
cp vimrc ~/.vimrc
# ------------------------------------------------------------------------------

# git settings
cp gitconfig ~/.gitconfig
# ------------------------------------------------------------------------------

# copy autostart settings
sudo cp autostart_priv.desktop /etc/xdg/autostart/
echo ">>> autostart_priv.desktop copied"
# ------------------------------------------------------------------------------

# copy autostart.sh
cp autostart.sh ~/config/
echo ">>> autostart.sh copied"
# ------------------------------------------------------------------------------

# copy terminal settings
cp ./%gconf.xml ~/.gconf/apps/gnome-terminal/profiles/Default
echo ">>> gnome-terminal config copied"
# ------------------------------------------------------------------------------

# copy radiotray bookmarks
cp ./radiotray/bookmarks.xml ~/.local/share/radiotray/bookmarks.xml
echo ">>> radiotray bookmarks copied"

exit 0
