#include "Menu.hpp"
#include <limits>

using namespace std;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

const int W = 15;  // largura fixa das colunas

void Menu::titulo(std::string texto) {
    using std::cout;
    using std::endl;

    cout << "\n=================================================================================================================================\n";
    cout << "                                                     " << texto << "                                                         \n";
    cout << "=================================================================================================================================\n";
}

std::string Menu::centralizar(const std::string& texto, int largura) {
    int espacos = largura - texto.size();
    if (espacos <= 0) return texto;

    int esquerda = espacos / 2;
    int direita  = espacos - esquerda;

    return std::string(esquerda, ' ') + texto + std::string(direita, ' ');
}

void Menu::linhaSep() {
        cout << "-";
        for (int i = 0; i < 8; i++) cout << std::string(W, '-') << "-";
        cout << endl;
    };

int Menu::mostrarMenuPrincipal() {
    titulo("SISTEMA DESLOCAMENTO - JATO SUPERSONICO");
    cout << "1. Metodo Fatoracao LU\n";
    cout << "2. Metodo Fatoracao LDP\n";
    cout << "3. Analise Completa (Comparativo LU vs LDP)\n";
    cout << "0. Sair\n";
    cout << "Opcao: ";

    int op;
    std::cin >> op;

    if (std::cin.fail()) {
        std::cin.clear(); // limpa estado de erro
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1; // valor inválido
    }

    return op;
}
