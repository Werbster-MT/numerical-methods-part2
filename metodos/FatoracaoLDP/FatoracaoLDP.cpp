#include "FatoracaoLDP.hpp"
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream> // Adicionado para printar
#include <iomanip>  // Adicionado para formatar

using namespace std;

using Vetor  = vector<double>;
using Matriz = vector<Vetor>;

vector<double> FatoracaoLDP::resolver(const SistemaLinear& sistema) {

    int n = sistema.n;
    const Matriz& A = sistema.A;
    const Vetor& f = sistema.f;

    Matriz L(n, Vetor(n, 0.0));
    Matriz D(n, Vetor(n, 0.0));
    Matriz P(n, Vetor(n, 0.0)); // P aqui atua como a Triangular Superior Unitária (U normalizada)

    // ==============================
    // INICIALIZAÇÃO
    // ==============================
    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
        P[i][i] = 1.0;
    }

    // ==============================
    // FATORAÇÃO LDP
    // ==============================
    for (int i = 0; i < n; i++) {

        double soma = 0.0;
        for (int k = 0; k < i; k++)
            soma += L[i][k] * D[k][k] * P[k][i];

        D[i][i] = A[i][i] - soma;

        if (fabs(D[i][i]) < 1e-12) {
            throw runtime_error("Falha na fatoracao LDP: elemento diagonal nulo.");
        }

        for (int j = i + 1; j < n; j++) {
            soma = 0.0;
            for (int k = 0; k < i; k++)
                soma += L[i][k] * D[k][k] * P[k][j];

            P[i][j] = (A[i][j] - soma) / D[i][i];
        }

        for (int j = i + 1; j < n; j++) {
            soma = 0.0;
            for (int k = 0; k < i; k++)
                soma += L[j][k] * D[k][k] * P[k][i];

            L[j][i] = (A[j][i] - soma) / D[i][i];
        }
    }

    // ==========================================
    // IMPRESSÃO DAS MATRIZES L, D e P (NOVO TRECHO)
    // ==========================================
    cout << fixed << setprecision(4);
    
    cout << "\n-----------------------------\n";
    cout << " Matriz L (Triangular Inferior):" << endl;
    for (int i = 0; i < n; i++) {
        cout << " |";
        for (int j = 0; j < n; j++) {
            cout << setw(10) << L[i][j] << " ";
        }
        cout << "|" << endl;
    }

    cout << "\n Matriz D (Diagonal):" << endl;
    for (int i = 0; i < n; i++) {
        cout << " |";
        for (int j = 0; j < n; j++) {
            cout << setw(10) << D[i][j] << " ";
        }
        cout << "|" << endl;
    }

    cout << "\n Matriz P (Triangular Superior Unitaria):" << endl;
    for (int i = 0; i < n; i++) {
        cout << " |";
        for (int j = 0; j < n; j++) {
            cout << setw(10) << P[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "-----------------------------\n";
    // ==========================================

    // ==============================
    // SUBSTITUIÇÃO DIRETA: Ly = f
    // ==============================
    Vetor y(n);
    for (int i = 0; i < n; i++) {
        y[i] = f[i];
        for (int j = 0; j < i; j++)
            y[i] -= L[i][j] * y[j];
    }

    // ==============================
    // SISTEMA DIAGONAL: Dz = y
    // ==============================
    Vetor z(n);
    for (int i = 0; i < n; i++)
        z[i] = y[i] / D[i][i];

    // ==============================
    // SUBSTITUIÇÃO RETROATIVA: Pd = z
    // ==============================
    Vetor d(n);
    for (int i = n - 1; i >= 0; i--) {
        d[i] = z[i];
        for (int j = i + 1; j < n; j++)
            d[i] -= P[i][j] * d[j];
    }

    return d;
}