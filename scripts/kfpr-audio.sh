#!/bin/bash
#
# Title: kfpr-audio.sh
# Description: play KFPR audio
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
#rtl_fm -f 88.9M -M wbfm -r 64k - | aplay -t raw -r 32000 -c 2 -f S16_LE
rtl_fm -f 88.9M -M wbfm -r 64k - | aplay -t raw -r 64000 -c 1 -f S16_LE
#
