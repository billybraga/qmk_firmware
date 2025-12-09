#!/bin/bash

cd ~/dev/thirdparty/qmk/qmk_firmware/

if [ -f /mnt/c/Users/bbraga/Downloads/billybraga.json ]; then
    cat /mnt/c/Users/bbraga/Downloads/billybraga.json > backups/manuform_5x6.json
    rm /mnt/c/Users/bbraga/Downloads/billybraga.json
else
    echo ----
    echo REUSING OLD JSON
    echo ----
fi
qmk json2c backups/manuform_5x6.json > keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/retro_keymap.c

git add .
git commit -m "update"
git push

