#include "FatoracaoLU.hpp"
#include <vector>
#include <stdexcept>

using namespace std;

vector<double> FatoracaoLU::resolver(const SistemaLinear& sistema) {

    int n = sistema.n;
    vector<vector<double>> A = sistema.A;
    vector<double> f = sistema.f;

    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    // ==============================
    // FATORAÇÃO LU (Doolittle)
    // ==============================
    for (int i = 0; i < n; i++) {

        // Matriz U (triangular superior)
        for (int k = i; k < n; k++) {
            double soma = 0.0;
            for (int j = 0; j < i; j++)
                soma += L[i][j] * U[j][k];

            U[i][k] = A[i][k] - soma;
        }

        // Verificação de pivô nulo
        if (U[i][i] == 0.0) {
            throw runtime_error("Falha na fatoracao LU: pivô nulo.");
        }

        // Matriz L (triangular inferior, diagonal unitária)
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1.0;
            } else {
                double soma = 0.0;
                for (int j = 0; j < i; j++)
                    soma += L[k][j] * U[j][i];

                L[k][i] = (A[k][i] - soma) / U[i][i];
            }
        }
    }

    // ==============================
    // SUBSTITUIÇÃO DIRETA: Ly = f
    // ==============================
    vector<double> y(n);

    for (int i = 0; i < n; i++) {
        double soma = 0.0;
        for (int j = 0; j < i; j++)
            soma += L[i][j] * y[j];

        y[i] = f[i] - soma;
    }

    // ==============================
    // SUBSTITUIÇÃO RETROATIVA: Ud = y
    // ==============================
    vector<double> d(n);

    for (int i = n - 1; i >= 0; i--) {
        double soma = 0.0;
        for (int j = i + 1; j < n; j++)
            soma += U[i][j] * d[j];

        d[i] = (y[i] - soma) / U[i][i];
    }

    return d;
};