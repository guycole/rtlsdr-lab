#!/bin/bash
#
# Title: kqed-file.sh
# Description: 
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
DURATION=30
TODAY=$(date '+%Y-%m-%d')
FILE_NAME="kqed-${TODAY}.iq"
#
source venv/bin/activate
python catalog.py
#
rtl_sdr -f 88.5M -s 64k -g 90 $FILE_NAME &
pid=$!
sleep $DURATION
kill -9 $pid
#
