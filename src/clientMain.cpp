// kiyostarter

#include <exception>

#include "client/clientclass.h"
#include "tplib/libclass.hh"

int main() {
  try {
    tplib::libclass test;
    clientlib::clientclass test2;
    return test2.method() + test.method();

  } catch (const std::exception& e) {
  }

  return 0;
}
