#!/bin/bash
sudo modprobe fuse

remote=user@host.ch
echo "MOUNT #1:"
sudo sshfs -o uid=1000 -o gid=1000 $remote:/home/user/projects/nios2-linux /mnt/user

echo "DONE."
echo "insmod IEEE1588nic.ko"

