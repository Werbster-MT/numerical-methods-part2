
#include "SistemaJatos.hpp"
#include <cstring> 
#include <string>

int main(int argc, char* argv[]) {
    SistemaJatos app;

    bool modoWeb = false;
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--web") {
            modoWeb = true;
        }
    }

    if (modoWeb) {
        // Modo silencioso para o Streamlit
        app.executarModoWeb(); 
    } else {
        // Modo normal com Menu para o Professor
        app.executar(); 
    }

    return 0;
}