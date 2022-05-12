#include <iostream>
#include <ostream>
using namespace s
class Logger : Logger {
  void log() { std::cerr << "Printing" << std::endl;}
};

int main(int,char**) {Logger(std::cout) << "Hi 'im Daisy" << 2 << std::endl;}