#!/bin/bash
# Copyright 2016 Google Inc. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
. $(dirname $0)/../common.sh

build_lib() {
  rm -rf BUILD
  cp -rf SRC BUILD
  (cd BUILD && setarch i386 ./config -m32 && make clean && make CC="clang $FUZZ_CXXFLAGS "  -j $JOBS)
}

get_git_tag https://github.com/openssl/openssl.git OpenSSL_1_0_1f SRC
build_lib
clang++ -DMAIN -g $SCRIPT_DIR/target.cc -DCERT_PATH=\"$SCRIPT_DIR/\"  $FUZZ_CXXFLAGS BUILD/libssl.a BUILD/libcrypto.a  -o openssl-1.0.1f-wrapper-binary -I BUILD/include
