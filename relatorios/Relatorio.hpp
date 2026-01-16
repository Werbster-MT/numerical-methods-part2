#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

class Relatorio {
    public:
        void imprimir_D_Y(const std::vector<double>& D, const std::vector<double>& Y);
        void imprimirQuadroResposta(const std::vector<double> deslocamentos);
        void imprimirQuadroComparativo(const std::vector<double> deslocamentos_metodo01, const std::vector<double> deslocamentos_metodo02);
};

#endif // RELATORIO_HPP