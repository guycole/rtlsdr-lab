#!/bin/bash
#
# Title: wxl88_file.sh
# Description: 
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
DURATION=10
TODAY=$(date '+%Y-%m-%d')
FILE_NAME="wxl88-${TODAY}.iq"
#
rtl_sdr -f 162.55M -s 256k -g 90 $FILE_NAME &
pid=$!
sleep $DURATION
kill -9 $pid
#
