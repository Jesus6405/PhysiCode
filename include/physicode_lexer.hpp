#ifndef PHYSICODE_LEXER_HPP
#define PHYSICODE_LEXER_HPP

#include <string>
#include <llparser.hpp>

namespace PhysiCode
{

class PhysiCodeLexer
{
public:
    PhysiCodeLexer();

    // Construye y configura el Lexer de DeSiGNAR con todas las reglas de PhysiCode
    static Designar::Lexer make_lexer();

    // Tokeniza una cadena de entrada e ignora espacios en blanco y comentarios
    Designar::DynArray<Designar::Token> tokenize(const std::string& input) const;

    // Tokeniza directamente desde un archivo de codigo fuente (.pcode)
    Designar::DynArray<Designar::Token> tokenize_file(const std::string& filepath) const;

    // Accede a la instancia interna del lexer de DeSiGNAR
    const Designar::Lexer& get_lexer() const;

private:
    Designar::Lexer lexer_;
};

} // namespace PhysiCode

#endif // PHYSICODE_LEXER_HPP