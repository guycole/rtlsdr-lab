rtl_fm -f 156.6M,156.65M,156.7M,156.8M fm -s 44100 -g 80 -l 50 - | aplay -t raw -r 44100 -f S16_LE -c 1
#rtl_fm -f 156.8M -M fm -s 256k - | aplay -t raw -r 28000 -c 1 -f S16_LE
