#!/bin/bash
set -x
set -e
cd ~/dev/thirdparty/qmk/qmk_firmware/
rm -f ~/dev/thirdparty/qmk/qmk_firmware/backups/manuform_5x6.json
mv /mnt/c/Users/bbraga/Downloads/billybraga.json ~/dev/thirdparty/qmk/qmk_firmware/backups/manuform_5x6.json
git add .
git commit -m updateBackup
cd ~/dev/thirdparty/qmk/qmk_firmware/keyboards/handwired/dactyl_manuform/5x6/keymaps/retro
qmk json2c ~/dev/thirdparty/qmk/qmk_firmware/backups/manuform_5x6.json> keymap.c
qmk compile -j16
