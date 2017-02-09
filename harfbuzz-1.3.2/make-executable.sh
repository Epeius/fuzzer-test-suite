#!/bin/bash
#Usage: ./run-docker.sh ./make-kernel.sh
#

function colorize_text() {
  color_code=${color_code?-0}
  echo -e "\033[${color_code}m$*\033[0m"
}

function info() {
  color_code="0;32"
  colorize_text " *** $*"
}

function err() {
  color_code="0;31"
  colorize_text " *** $*" 1>&2
  exit 1
}

ln -sf /usr/bin/clang-3.8 /usr/bin/clang
ln -sf /usr/bin/clang++-3.8 /usr/bin/clang++

apt-get -y install autotools-dev
apt-get -y install automake
apt-get -y install ragel

apt-get -y install libglib2.0-dev

./build.sh || echo "Build ERROR"

