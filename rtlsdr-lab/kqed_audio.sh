#!/bin/bash
#
# Title: kqed_audio.sh
# Description: 
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
#rtl_fm -f 88.5M -M wbfm -s 256k -r 48k - | aplay -t raw -r 48k -c 1 -f S16_LE
rtl_fm -f 88.9M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#
