#!/usr/bin/bash
set -x
set -e

while read i; do if [ "$i" = billybraga.json ]; then break; fi; done \
   < <(inotifywait  -e create,open --format '%f' --quiet /mnt/c/Users/bbraga/Downloads --monitor)

~/dev/thirdparty/qmk/qmk_firmware/update.sh
