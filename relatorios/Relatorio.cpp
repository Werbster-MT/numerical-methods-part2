#include "Relatorio.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

void Relatorio::imprimir_D_Y(const vector<double>& D, const vector<double>& Y) {
    cout << fixed << setprecision(6);

    cout << "\n========================================\n";
    cout << "         VETORES INTERMEDIARIOS         \n";
    cout << "========================================\n";

    // --- BLOCO Y AGORA VEM PRIMEIRO ---
    cout << "\n[ Vetor Y ]\n";
    cout << string(40, '-') << endl;
    for (size_t i = 0; i < Y.size(); ++i) {
        cout << " Y[" << setw(2) << i + 1 << "] = " << setw(12) << Y[i] << endl;
    }

    // --- BLOCO D VEM DEPOIS ---
    cout << "\n[ Vetor D (Deslocamentos) ]\n";
    cout << string(40, '-') << endl;
    for (size_t i = 0; i < D.size(); ++i) {
        cout << " D[" << setw(2) << i + 1 << "] = " << setw(12) << D[i] << " cm" << endl;
    }
    
    cout << endl;
}

void Relatorio::imprimirQuadroResposta(const std::vector<double> deslocamentos) {
    cout << "\n==============================================\n";
    cout << "            QUADRO DE RESPOSTA (D)            \n";
    cout << "==============================================\n";
    
    cout << setprecision(6) << fixed;
    bool explodiu = false;

    for (size_t i = 0; i < deslocamentos.size(); ++i) {
        double d = deslocamentos[i];
        cout << " d[" << setw(2) << i + 1 << "] = " << setw(12) << d << " cm";
        if (fabs(d) > 2.0) {
            cout << "   <-- [ALERTA: EXCEDEU 2cm!]";
            explodiu = true;
        }
        cout << endl;
    }

    cout << string(46, '-') << endl;
    if (explodiu) {
        cout << " STATUS FINAL: O JATO EXPLODIU! (FALHA CRITICA)\n";
    } else {
        cout << " STATUS FINAL: O JATO ESTA SEGURO (OK)\n";
    }
    cout << "==============================================\n";
}

void Relatorio::imprimirQuadroComparativo(const std::vector<double> d1, const std::vector<double> d2) {
    int w_col = 16; 

    cout << "\n===================================================================\n";
    cout << "                       COMPARATIVO LU vs LDP                       \n";
    cout << "===================================================================\n";
    
    cout << setprecision(6) << fixed;

    cout << setw(6) << "Indice" << " | " 
         << setw(w_col) << "LU (cm)" << " | " 
         << setw(w_col) << "LDP (cm)" << " | " 
         << setw(w_col) << "Diferenca" << endl;

    cout << string(67, '-') << endl;
    
    for (size_t i = 0; i < d1.size(); ++i) {
        double diff = fabs(d1[i] - d2[i]);
        cout << setw(6) << i + 1 << " | " 
             << setw(w_col) << d1[i] << " | " 
             << setw(w_col) << d2[i] << " | " 
             << setw(w_col) << diff << endl;
    }
    cout << "===================================================================\n";
}