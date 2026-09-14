#include "matmult.hpp"

int main(int argc, char *argv[]) {
  matmult::SGEMM(100, 100, 100);
  return 0;
}
