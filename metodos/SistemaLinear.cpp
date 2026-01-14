#include "SistemaLinear.hpp"

SistemaLinear::SistemaLinear(int ordem)
    : n(ordem),
      A(ordem, std::vector<double>(ordem)),
      f(ordem) {}
