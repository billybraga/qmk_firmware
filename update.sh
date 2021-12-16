#!/usr/bin/bash
set -x
set -e

cd ~/dev/thirdparty/qmk/qmk_firmware/
rm -f backups/manuform_5x6.json
mv /mnt/c/Users/bbraga/Downloads/billybraga.json backups/manuform_5x6.json
qmk json2c backups/manuform_5x6.json > keyboards/handwired/dactyl_manuform/5x6/keymaps/retro/retro_keymap.c
make --jobs=16 handwired/dactyl_manuform/5x6:retro

echo DONE COMPILING
date

git add .
git commit -m updateBackup
git push
wait
