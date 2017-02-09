// Copyright 2016 Google Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
#include <string>
#include <vector>
#include "libxml/xmlversion.h"
#include "libxml/parser.h"
#include "libxml/HTMLparser.h"
#include "libxml/tree.h"

void ignore (void * ctx, const char * msg, ...) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  xmlSetGenericErrorFunc(NULL, &ignore);
  if (auto doc = xmlReadMemory(reinterpret_cast<const char *>(data), size,
                               "noname.xml", NULL, 0))
    xmlFreeDoc(doc);
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
  /* TODO This silently passes if file does not exist.  Fix it! */
  if(access( Path.c_str(), F_OK ) == -1) {
    std::cout << "Cannot find the file" << std::endl;
    exit(-1);
  }
  std::ifstream T(Path.c_str());
  return std::string((std::istreambuf_iterator<char>(T)),
                        std::istreambuf_iterator<char>());
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " file " << std::endl;
    exit(-1);
  }
  std::string s = FileToString(argv[1]);
  LLVMFuzzerTestOneInput((const unsigned char*)s.data(), s.size());
}
#endif

