#include <iostream>
#include <redox.hpp>

using namespace std;
using namespace redox;

int main(int argc, char* argv[]) {

  Redox rdx;
  if(!rdx.connect("localhost", 9851)) return 1;
  std::string key_test = "hello";
  std::string value_test = "world";
  if(rdx.set(key_test, value_test)) {
    std::cout << "set success" << std::endl;
    std::cout << rdx.get(key_test) << std::endl;
  } else {
    std::cout << "Set fail" << std::endl;
  }

  return 0;
}