#!/bin/bash
#
# Title: wz2504-file.sh
# Description: NOAA weather radio Sonoma
# Development Environment: Ubuntu 22.04.05 LTS
# Author: Guy Cole (guycole at gmail dot com)
#
PATH=/bin:/usr/bin:/etc:/usr/local/bin; export PATH
#
BLOCK_SIZE=$((16 * 16384))
DURATION=30
FREQUENCY=162475000
HOST_NAME=$(hostname)
SAMPLE_RATE=2400000
SAMPLE_QUANTITY=$(($DURATION * $SAMPLE_RATE))
SCRIPT_NAME=$0
TODAY=$(date '+%Y-%m-%d')
UUID=$(uuidgen)
#
FILE_NAME="wz2504-${TODAY}.iq"
FILE_NAME="${UUID}.iq"
#
source venv/bin/activate
python catalog.py $UUID $DURATION $FREQUENCY $SAMPLE_RATE $SCRIPT_NAME $HOST_NAME
#
#rtl_sdr -f 162.475M -s 64k -g 90 $FILE_NAME &
#pid=$!
#sleep $DURATION
#kill -9 $pid
#
#rtl_sdr -f 162.475M -s 2.4M -g 90 -b 262144 -n $FILE_NAME &
#
rtl_sdr -f $FREQUENCY -s $SAMPLE_RATE -g 90 -b $BLOCK_SIZE -n $SAMPLE_QUANTITY $FILE_NAME
#
