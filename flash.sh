#!/usr/bin/bash
set -e

cd ~/dev/thirdparty/qmk/qmk_firmware/
git pull
make handwired/dactyl_manuform/5x6:retro:dfu