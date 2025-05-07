!/bin/bash
#
# Title: kfpr-audio.sh
# Description: north state public radio
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
FREQ=88.9M
FREQ=102.7M
SAMPLE=256k
#
#rtl_fm -f 88.9M -M wbfm -g 80 -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
rtl_fm -f $FREQ -M wbfm -s $SAMPLE - | aplay -t raw -r 28000 -c 1 -f S16_LE
#
