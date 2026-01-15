#include "SistemaJatos.hpp"
#include "../menu/Menu.hpp"            
#include "../relatorios/Relatorio.hpp"       
#include "../metodos/FatoracaoLU/FatoracaoLU.hpp"     
#include "../metodos/FatoracaoLDP/FatoracaoLDP.hpp"   
#include "../metodos/SistemaLinear.hpp"  

#include <iostream>
#include <vector>


SistemaLinear SistemaJatos::lerSistemaManual() {
    int n;
    std::cout << "\nInforme a ordem do sistema (n): ";
    std::cin >> n;

    SistemaLinear sistema(n);

    std::cout << "\nDigite a matriz A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> sistema.A[i][j];

    std::cout << "\nDigite o vetor f (" << n << " elementos):\n";
    for (int i = 0; i < n; i++)
        std::cin >> sistema.f[i];

    return sistema;
}

SistemaLinear SistemaJatos::sistemaCalibracao() {
    SistemaLinear sistema(3);

    sistema.A = {
        { 3.0, -2.0,  1.0 },
        { 1.0, -3.0,  4.0 },
        { 9.0,  4.0, -5.0 }
    };

    sistema.f = { 8.0, 6.0, 11.0 };

    return sistema;
}

SistemaLinear SistemaJatos::obterSistema() {
    int n;
    std::cout << "\nInforme a ordem do sistema (n): ";
    std::cin >> n;

    if (n == 3) {
        char escolha;
        std::cout << "Deseja usar a matriz de calibracao? (s/n): ";
        std::cin >> escolha;

        if (escolha == 's' || escolha == 'S') {
            return sistemaCalibracao();
        }
    }

    // Caso geral
    SistemaLinear sistema(n);

    std::cout << "\nDigite a matriz A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> sistema.A[i][j];

    std::cout << "\nDigite o vetor f (" << n << " elementos):\n";
    for (int i = 0; i < n; i++)
        std::cin >> sistema.f[i];

    return sistema;
}

void SistemaJatos::executar() {
    // Objetos auxiliares
    Menu menu;
    Relatorio relatorio;
    FatoracaoLU solverLU;
    FatoracaoLDP solverLDP;

    while (true) {
        int opcao = menu.mostrarMenuPrincipal();

        try {
            switch (opcao) {

                case 0: {
                    std::cout << "Saindo do sistema..." << std::endl;
                    return;
                }

                case 1: {
                    std::cout << "\n[Calculando via Fatoracao LU...]\n";
                    SistemaLinear sistema = obterSistema();
                    std::vector<double> d = solverLU.resolver(sistema);
                    relatorio.imprimirQuadroResposta(d);
                    break;
                }

                case 2: {
                    std::cout << "\n[Calculando via Fatoracao LDP...]\n";
                    SistemaLinear sistema = obterSistema();
                    std::vector<double> d = solverLDP.resolver(sistema);
                    relatorio.imprimirQuadroResposta(d);
                    break;
                }

                case 3: {
                    std::cout << "\n[Realizando Analise Comparativa...]\n";
                    SistemaLinear sistema = obterSistema();
                    std::vector<double> d_lu  = solverLU.resolver(sistema);
                    std::vector<double> d_ldp = solverLDP.resolver(sistema);

                    relatorio.imprimirQuadroComparativo(d_lu, d_ldp);

                    std::cout << "Analise Estrutural (Baseada no LDP):\n";
                    relatorio.imprimirQuadroResposta(d_ldp);
                    break;
                }

                default:
                    std::cout << "\nOpcao invalida! Tente novamente.\n";
                    break;
            }

        } catch (const std::exception& e) {
            std::cerr << "\nERRO NUMERICO: " << e.what() << std::endl;
        }
    }
}
