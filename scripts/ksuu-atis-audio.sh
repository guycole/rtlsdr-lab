#!/bin/bash
#
# Title: ksuu-atis-audio.sh
# Description: Travis AFB ATIS
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
rtl_fm -f 135.55M -M am -s 64k - | aplay -t raw -r 64000 -c 1 -f S16_LE
#
