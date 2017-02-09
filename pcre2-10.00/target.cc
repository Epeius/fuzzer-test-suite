// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");

#include <string>
#include "pcre2posix.h"

using std::string;

extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size) {
  if (size < 1) return 0;
  regex_t preg;
  string str(reinterpret_cast<const char*>(data), size);
  string pat(str);
  int flags = data[size/2] - 'a';  // Make it 0 when the byte is 'a'.
  if (0 == regcomp(&preg, pat.c_str(), flags)) {
    regmatch_t pmatch[5];
    regexec(&preg, str.c_str(), 5, pmatch, 0);
    regfree(&preg);
  }
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
   exit(-1);
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
