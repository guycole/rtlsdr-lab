#!/bin/bash
#
# Title: wz2504-file.sh
# Description: NOAA weather radio Sonoma
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
DURATION=30
TODAY=$(date '+%Y-%m-%d')
FILE_NAME="wz2504-${TODAY}.iq"
#
source venv/bin/activate
python catalog.py
#
rtl_sdr -f 162.475M -s 64k -g 90 $FILE_NAME &
pid=$!
sleep $DURATION
kill -9 $pid
#
