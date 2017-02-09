#!/bin/bash
# Copyright 2016 Google Inc. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
. $(dirname $0)/../common.sh

build_lib() {
  rm -rf BUILD
  cp -rf SRC BUILD
  (cd BUILD && ./autogen.sh && CXX="clang++ $FUZZ_CXXFLAGS" CC="clang $FUZZ_CXXFLAGS" CCLD="clang++ $FUZZ_CXXFLAGS"  ./configure && make -j $JOBS)
}

get_git_tag git://git.gnome.org/libxml2  v2.9.2 SRC
get_git_revision https://github.com/mcarpenter/afl be3e88d639da5350603f6c0fee06970128504342 afl
build_lib
set -x
clang++ -DMAIN -std=c++11  $SCRIPT_DIR/target.cc  $FUZZ_CXXFLAGS  -I BUILD/include BUILD/.libs/libxml2.a -lz -o libxml2-wrapper-binary
