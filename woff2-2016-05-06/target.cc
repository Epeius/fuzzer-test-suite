// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <stddef.h>
#include <stdint.h>

#include "woff2_dec.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::string buf;
  woff2::WOFF2StringOut out(&buf);
  out.SetMaxSize(30 * 1024 * 1024);
  woff2::ConvertWOFF2ToTTF(data, size, &out);
  return 0;
}


#ifdef MAIN
#include <iostream>
#include <iterator>
#include <fstream>
#include <assert.h>
#include <sys/stat.h>
#include <unistd.h>


std::string FileToString(const std::string &Path) {
 if (access( Path.c_str(), F_OK ) == -1) {
    std::cout << "Cannot find target file" << std::endl;
    _exit(-1);
 }
 std::ifstream T(Path.c_str());
 return std::string((std::istreambuf_iterator<char>(T)),
                         std::istreambuf_iterator<char>());
}

int main(int argc, char **argv) {
 if (argc != 2) {
   std::cout << "Usage: " << argv[0] << " filemame" << std::endl;
   return 0;
 }

 std::string s = FileToString(argv[1]);
 LLVMFuzzerTestOneInput((const unsigned char*)s.data(), s.size());
}

#endif

