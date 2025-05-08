#!/bin/bash
#
# Title: wxl88_audio.sh
# Description: 
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
rtl_fm -f 162.4M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.425M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.45M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.475M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.5M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.525M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#rtl_fm -f 162.55M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
#
