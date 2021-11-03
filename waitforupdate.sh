#! /usr/bin/bash

set -e
while [ ! -f /mnt/c/Users/bbraga/Downloads/billybraga.json ]; do sleep 2; done

$(dirname $0)/update.sh
