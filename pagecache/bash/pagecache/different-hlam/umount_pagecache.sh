#!/bin/bash
set -e

service smbd stop
umount /mnt/overlay1/merged
umount /mnt/overlay1/lower
umount /mnt/overlay1/upper
umount /mnt/overlay1/lower
df -h

