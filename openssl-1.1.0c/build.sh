#!/bin/bash
# Copyright 2017 Google Inc. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
. $(dirname $0)/../common.sh

build_lib() {
  rm -rf BUILD
  cp -rf SRC BUILD
  (cd BUILD && setarch i386 ./config -m32 && make clean && make CC="clang $FUZZ_CXXFLAGS"  -j $JOBS)
}

get_git_tag https://github.com/openssl/openssl.git OpenSSL_1_1_0c SRC
#apt-get -y install g++-multilib
build_lib
set -x
clang++  -DMAIN -g target.cc -I BUILD/include $FUZZ_CXXFLAGS BUILD/libssl.a BUILD/libcrypto.a -lgcrypt -ldl -pthread -o openssl-1.1.0c-wrapper-bianry
