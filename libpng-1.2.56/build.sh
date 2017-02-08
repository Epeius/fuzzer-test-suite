#!/bin/bash
# Copyright 2016 Google Inc. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");

. $(dirname $0)/../common.sh

[ ! -e libpng-1.2.56.tar.gz ] && wget --no-check-certificate https://sourceforge.net/projects/libpng/files/libpng12/1.2.56/libpng-1.2.56.tar.gz 
[ ! -e libpng-1.2.56 ] && tar xf libpng-1.2.56.tar.gz

build_lib() {
  rm -rf BUILD
  cp -rf libpng-1.2.56 BUILD
  (cd BUILD && ./configure CC="clang" CFLAGS="$FUZZ_CXXFLAGS" &&  make -j)
}

build_lib
set -x

g++ -g -std=c++11 $FUZZ_CXXFLAGS $SCRIPT_DIR/target.cc BUILD/.libs/libpng12.a  -I BUILD/ -I BUILD -lz -o png-1.2.56-wrapper-binary

