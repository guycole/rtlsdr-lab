#rtl_fm -f 88.5M -M wbfm -s 256k -r 48k - | aplay -t raw -r 48k -c 1 -f S16_LE
#rtl_fm -f 162.55M -M wbfm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
rtl_fm -f 162.475M -s 24000 - | aplay -r 24k -f S16_LE -t raw -c 1
