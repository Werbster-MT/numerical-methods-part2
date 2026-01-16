#pragma once

#include "../SistemaLinear.hpp"
#include <vector>
#include <utility>

class FatoracaoLU {
public:
    std::pair<std::vector<double>, std::vector<double>> resolver(const SistemaLinear& sistema);
};
