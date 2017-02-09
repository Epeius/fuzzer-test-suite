// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <string>
#include "re2/re2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) return 0;
  uint16_t f = (data[0] << 16) + data[1];
  RE2::Options opt;
  opt.set_log_errors(false);
  if (f & 1) opt.set_encoding(RE2::Options::EncodingLatin1);
  opt.set_posix_syntax(f & 2);
  opt.set_longest_match(f & 4);
  opt.set_literal(f & 8);
  opt.set_never_nl(f & 16);
  opt.set_dot_nl(f & 32);
  opt.set_never_capture(f & 64);
  opt.set_case_sensitive(f & 128);
  opt.set_perl_classes(f & 256);
  opt.set_word_boundary(f & 512);
  opt.set_one_line(f & 1024);
  const char *b = reinterpret_cast<const char*>(data) + 2;
  const char *e = reinterpret_cast<const char*>(data) + size;
  std::string s1(b, e);
  RE2 re(s1, opt);
  if (re.ok())
    RE2::FullMatch(s1, re);
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

