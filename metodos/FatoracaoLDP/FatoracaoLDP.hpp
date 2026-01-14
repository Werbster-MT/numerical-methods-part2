#pragma once

#include "../SistemaLinear.hpp"
#include <vector>

class FatoracaoLDP {
public:
    std::vector<double> resolver(const SistemaLinear& sistema);
};
