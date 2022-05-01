#include <cstdlib>
#include <ctime>
#include "utils.hpp"

int generateRandPortNum(void) {
  std::srand((unsigned)time(0));
  return (rand() % 10000 + 1);
}
