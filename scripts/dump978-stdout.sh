#!/bin/bash
#
# Title: dump978-stdout.sh
# Description: dump978 to stdout
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
BINARY=/home/gsc/Documents/github/dump978/dump978
RTL_SDR=/usr/local/bin/rtl_sdr
#
$RTL_SDR -f 978000000 -s 2083334 - | $BINARY
#
