# NOAA weather WNG655 Contra Costa County
#rtl_fm -f 162.425M -M fm -s 44100 -g 90 -l 40 - | aplay -t raw -r 44100 -f S16_LE -c 1
# NOAA weather WZ2504 Sonoma County 
rtl_fm -f 162.475M -M fm -s 44100 -g 90 -l 40 - | aplay -t raw -r 44100 -f S16_LE -c 1
