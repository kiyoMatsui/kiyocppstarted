// kiyostarter

#include <exception>

#include "server/serverclass.h"
#include "tplib/libclass.hh"

int main() {
  try {
    tplib::libclass test;
    serverlib::serverclass test2;
    return test2.method() + test.method();

  } catch (const std::exception& e) {
  }

  return 0;
}
