#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "physicode_lexer.hpp"

using namespace Designar;
using namespace PhysiCode;

int main(int argc, char* argv[])
{
    PhysiCodeLexer phys_lexer;

    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <ruta_archivo_ejemplo.txt>\n";
        return 1;
    }

    const std::string filepath = argv[1];

    try
    {
        DynArray<Token> tokens = phys_lexer.tokenize_file(filepath);

        std::cout << " Archivo analizado: " << filepath << "\n";
        std::cout << " Total de tokens utiles reconocidos: " << tokens.size() << "\n";

        std::cout << std::left << std::setw(6) << "#" << std::setw(20) << "TOKEN" << "LEXEMA\n";
        std::cout << "---------------------------------------------------------\n";

        for (nat_t i = 0; i < tokens.size(); ++i)
        {
            std::cout << std::left << std::setw(6) << (i + 1) << std::setw(20) << tokens[i].name << "\"" << tokens[i].lexeme << "\"\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Error Lexico]: " << e.what() << '\n';
        return 1;
    }

    return 0;
}