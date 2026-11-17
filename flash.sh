#!/usr/bin/bash
set -e

cd "$(dirname "$(readlink -f "$0")")"
git pull
# Caterina bootloader -> avrdude (":flash" picks it from rules.mk), not DFU
make handwired/dactyl_manuform/5x6:retro:flash
