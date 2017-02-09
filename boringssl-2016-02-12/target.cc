#include <openssl/evp.h>

extern "C" int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {
  const uint8_t *bufp = buf;
  EVP_PKEY_free(d2i_AutoPrivateKey(NULL, &bufp, len));
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
 LLVMFuzzerTestOneInput((uint8_t*)s.data(), s.size());
}

#endif
