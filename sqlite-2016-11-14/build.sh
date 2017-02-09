#!/bin/bash
# Copyright 2016 Google Inc. All Rights Reserved.
# Licensed under the Apache License, Version 2.0 (the "License");
. $(dirname $0)/../common.sh

wget https://hg.mozilla.org/projects/nss/raw-file/92e0af39805cb4ea99c108288d2f38bb1f4dca30/lib/sqlite/sqlite3.h

clang -c $FUZZ_CXXFLAGS $SCRIPT_DIR/sqlite3.c
clang -DMAIN -c $FUZZ_CXXFLAGS $SCRIPT_DIR/ossfuzz.c
clang++  sqlite3.o ossfuzz.o $FUZZ_CXXFLAGS -pthread -ldl -o sqlite-wrapper-binary 
