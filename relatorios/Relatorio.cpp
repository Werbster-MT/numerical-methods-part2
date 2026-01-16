#include "Relatorio.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

// função para imprimir vetores D e Y da fatoração LU
void Relatorio::imprimir_D_Y(const vector<double>& D, const vector<double>& Y) {
    cout << "\nVetor D (Deslocamentos):\n";
    for (size_t i = 0; i < D.size(); ++i) {
        cout << "D[" << i + 1 << "] = " << D[i] << " cm" << endl;
    }

    // vetor para calcular D
    cout << "\nVetor Y:\n";
    for (size_t i = 0; i < Y.size(); ++i) {
        cout << "Y[" << i + 1 << "] = " << Y[i] << endl;
    }
}

void Relatorio::imprimirQuadroResposta(const std::vector<double> deslocamentos) {
    cout << "\n>>> QUADRO DE RESPOSTA (D) <<<\n";
    cout << setprecision(6) << fixed;
    bool explodiu = false;

    for (size_t i = 0; i < deslocamentos.size(); ++i) {
        double d = deslocamentos[i];
        cout << "d[" << i + 1 << "] = " << setw(10) << d << " cm";
        if (fabs(d) > 2.0) {
            cout << " [ALERTA: EXCEDEU 2cm!]";
            explodiu = true;
        }
        cout << endl;
    }

    if (explodiu) {
        cout << "\nSTATUS FINAL: O JATO EXPLODIU! (Prejuizo gigantesco)\n";
    } else {
        cout << "\nSTATUS FINAL: O JATO ESTA SEGURO.\n";
    }
}

void Relatorio::imprimirQuadroComparativo(const std::vector<double> d1, const std::vector<double> d2) {
    cout << "\n>>> COMPARATIVO LU vs LDP <<<\n";
    cout << setw(6) << " di" << " | " << setw(15) << "LU (cm)" << " | " << setw(15) << "LDP (cm)" << " | " << setw(15) << "Diferenca" << endl;
    cout << string(60, '-') << endl;
    
    for (size_t i = 0; i < d1.size(); ++i) {
        double diff = fabs(d1[i] - d2[i]);
        cout << setw(5) << "d" << i + 1 << " | " 
             << setw(15) << d1[i] << " | " 
             << setw(15) << d2[i] << " | " 
             << setw(15) << diff << endl;
    }
}
