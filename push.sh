#!/bin/bash

cd "$(dirname "$(readlink -f "$0")")"
export PATH=~/.qmk-venv/bin:$PATH

if [ -f /mnt/c/Users/BillyProgi/Downloads/billybraga.json ]; then
    cat /mnt/c/Users/BillyProgi/Downloads/billybraga.json > backups/manuform_5x6.json
    rm /mnt/c/Users/BillyProgi/Downloads/billybraga.json
else
    echo ----
    echo REUSING OLD JSON
    echo ----
fi
qmk json2c backups/manuform_5x6.json > keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/retro_keymap.c

git add .
git commit -m "update"
git push

