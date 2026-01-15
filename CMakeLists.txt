cmake_minimum_required(VERSION 3.10)
project(Trabalho2_MN1)
set(CMAKE_CXX_STANDARD 17)

# Inclui diretórios de cabeçalho
include_directories(.)
include_directories(metodos)
include_directories(app)
include_directories(menu)
include_directories(relatorios)

# Lista de arquivos fonte
set(SOURCES
    main.cpp
    app/SistemaJatos.cpp
    menu/Menu.cpp
    relatorios/Relatorio.cpp
    metodos/SistemaLinear.cpp
    metodos/FatoracaoLU/FatoracaoLU.cpp
    metodos/FatoracaoLDP/FatoracaoLDP.cpp
)

# Cria o executável
add_executable(sistema_jatos ${SOURCES})
