#pragma once
#include "../relatorios/Relatorio.hpp"
#include "../menu/Menu.hpp"

using namespace std;

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

class SistemaJatos {

    private:
        Relatorio relatorio;
        Menu menu;
    public:
        SistemaJatos();

        void executar();
};
