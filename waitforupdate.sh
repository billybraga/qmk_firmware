#! /usr/bin/bash

set -e

while [ 1=1 ]; do
  echo WAITING
  while [ ! -f /mnt/c/Users/bbraga/Downloads/billybraga.json ]; do sleep 2; done
  $(dirname $0)/update.sh
  if [ -f /mnt/c/Users/bbraga/Downloads/billybraga.json ]; then
    echo "file wasn't deleted"
    exit 1
  fi
done
