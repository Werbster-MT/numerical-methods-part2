#pragma once
#include <iostream>
#include <string>      
#include <iostream>
#include <iomanip>

class Menu {
    private:
        void titulo(std::string texto);

        std::string centralizar(const std::string& texto, int largura);

        void linhaSep();

    public:
        int mostrarMenuPrincipal();
};
