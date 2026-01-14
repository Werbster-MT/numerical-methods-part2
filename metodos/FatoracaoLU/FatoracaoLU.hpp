#pragma once

#include "../SistemaLinear.hpp"
#include <vector>

class FatoracaoLU {
public:
    std::vector<double> resolver(const SistemaLinear& sistema);
};
