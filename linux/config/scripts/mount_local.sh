#!/bin/bash
sudo modprobe fuse

remote=$USER@$HOST
echo "MOUNT #1:"
sudo sshfs -o uid=1000 -o gid=1000 $remote:/home/$USER/test /mnt/$USER

echo "DONE."

