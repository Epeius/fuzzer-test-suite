#!/bin/bash

# Runs command inside docker image

# NOTE: you have to first create docker image
# $ git clone git@github.com:CodeTickler/s2e-images.git
# $ cd s2e-images/oses/Linux
# $ docker build -t linux-kernel-cgc .

# Usage: ./run-docker.sh [COMMAND]

args=()
if [ $# -gt 0 ]; then
  dir=$(dirname $(readlink -f $0))
  args=("-c" "cd ${dir}; $*")
fi
docker run --rm -ti -v $HOME:$HOME -v /etc/ssl/certs:/etc/ssl/certs google-fuzz-testsuits:latest "${args[@]}" 

