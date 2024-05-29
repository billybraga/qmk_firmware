#!/usr/bin/bash
set -e

file=/mnt/c/Users/bbraga/Downloads/handwired_dactyl_manuform_5x6_billybraga.json

cd ~/dev/thirdparty/qmk/qmk_firmware/
git pull
if [ -f $file ]; then
    cat $file > backups/manuform_5x6.json
    rm $file 
elif [ -f $file ]; then
    cat $file > backups/manuform_5x6.json
    rm $file
else
    echo ----
    echo REUSING OLD JSON
    echo ----
fi
qmk json2c backups/manuform_5x6.json > keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/retro_keymap.c
make --jobs=16 handwired/dactyl_manuform/5x6:retro
echo ----
echo DONE COMPILING
date
echo ----

git add .
git commit -m updateBackup
git push
wait
