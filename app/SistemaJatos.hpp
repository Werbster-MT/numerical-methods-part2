#pragma once
#include "../relatorios/Relatorio.hpp"
#include "../menu/Menu.hpp"
#include "../metodos/SistemaLinear.hpp"

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

class SistemaJatos {

    private:
        Relatorio relatorio;
        Menu menu;

        SistemaLinear lerSistemaManual();
        SistemaLinear sistemaCalibracao();
        SistemaLinear obterSistema();

    public:
        // SistemaJatos();
        // Adicione a declaração
        void executarModoWeb();
        void executar();
};
