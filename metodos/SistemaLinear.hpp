#pragma once
#include <vector>

class SistemaLinear {
public:
    int n;
    std::vector<std::vector<double>> A;
    std::vector<double> f;

    SistemaLinear(int ordem);
};
