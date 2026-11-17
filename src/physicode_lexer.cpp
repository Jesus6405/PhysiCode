#include "physicode_lexer.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace Designar;

namespace PhysiCode
{

PhysiCodeLexer::PhysiCodeLexer() : lexer_(make_lexer()) {}

Lexer PhysiCodeLexer::make_lexer()
{
    Lexer lexer;

    const std::string DIGIT = "(0|1|2|3|4|5|6|7|8|9)";
    const std::string LOWER = "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)";
    const std::string UPPER = "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)";
    const std::string LETTER = "(" + LOWER + "|" + UPPER + ")";
    const std::string ID_START = "(" + LETTER + "|_)";
    const std::string ID_CHAR = "(" + LETTER + "|" + DIGIT + "|_)";

    // Comentarios
    const std::string TEXT_CHAR = "(" + LETTER + "|" + DIGIT + "| |\\t|_|\\.|,|;|:|\\+|\\-|\\*|/|\\^|=|<|>|!|&|\\||\\(|\\)|\\[|\\]|\\{|\\}|\"|')";
    const std::string LINE_COMMENT = "//" + TEXT_CHAR + "*";
    const std::string BLOCK_COMMENT = "/\\*(" + TEXT_CHAR + "|\\n|\\r)*\\*/";
    lexer.add_token("COMENTARIO", "(" + LINE_COMMENT + "|" + BLOCK_COMMENT + ")");

    // Palabras Reservadas
    // Declaracion y estructura
    lexer.add_token("KW_VAR", "var");
    lexer.add_token("KW_CONST", "const");
    lexer.add_token("KW_FORMULA", "formula");

    // Control de flujo (decision)
    lexer.add_token("KW_IF", "if");
    lexer.add_token("KW_ELSE", "else");
    lexer.add_token("KW_ELIF", "elif");

    // Control de flujo (repeticion)
    lexer.add_token("KW_WHILE", "while");
    lexer.add_token("KW_FOR", "for");

    // Entrada y salida
    lexer.add_token("KW_INPUT", "input");
    lexer.add_token("KW_SHOW", "show");
    lexer.add_token("KW_PRINT", "print");

    // Constantes fisicas y matematicas
    lexer.add_token("CONST_PI", "PI");
    lexer.add_token("CONST_EULER", "EULER");
    lexer.add_token("CONST_G", "G");

    // Tipos de datos basicos
    lexer.add_token("TYPE_NUM", "num");
    lexer.add_token("TYPE_BOOL", "bool");
    lexer.add_token("TYPE_STRING", "string");

    // Operador de conversion y definicion de magnitudes
    lexer.add_token("KW_TO", "to");
    lexer.add_token("KW_MAGNITUDE", "magnitude");
    lexer.add_token("KW_UNIT", "unit");

    // Literales booleanos
    lexer.add_token("TOKEN_BOOL", "(true|false)");

    // Reglas lexicas
    // TOKEN_UNIT: \[[a-zA-Z_/0-9\^\.\*\-]+\] (ej: [m/s^2], [kg], [km/h], [N])
    const std::string UNIT_CHAR = "(" + LETTER + "|" + DIGIT + "|_|/|\\^|\\.|\\*|\\-)";
    lexer.add_token("TOKEN_UNIT", "\\[" + UNIT_CHAR + "+\\]");

    // TOKEN_NUMBER: [0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)? (ej: 7.51, 2e9, 21)
    const std::string INT_NUM = DIGIT + "+";
    const std::string DEC_NUM = INT_NUM + "\\." + INT_NUM;
    const std::string BASE_NUM = "(" + INT_NUM + "|" + DEC_NUM + ")";
    const std::string EXP_PART = "(e|E)(" + INT_NUM + "|(\\+|\\-)" + INT_NUM + ")";
    lexer.add_token("TOKEN_NUMBER", "(" + BASE_NUM + "|" + BASE_NUM + EXP_PART + ")");

    // TOKEN_STRING: "([^"\\]|\\.)*"
    const std::string STR_CHAR = "(" + LETTER + "|" + DIGIT + "| |\\t|_|\\.|,|;|:|\\+|\\-|\\*|/|\\^|=|<|>|!|\\(|\\)|\\[|\\]|\\{|\\})";
    lexer.add_token("TOKEN_STRING", "\"" + STR_CHAR + "*\"");

    // TOKEN_OP_REL: ==|!=|<=|>=|<|>
    lexer.add_token("TOKEN_OP_REL", "(==|!=|<=|>=|<|>)");

    // TOKEN_OP_LOGIC: &&|\|\||!
    lexer.add_token("TOKEN_OP_LOGIC", "(&&|\\|\\||!)");

    // TOKEN_ASIGN: =
    lexer.add_token("TOKEN_ASIGN", "=");

    // TOKEN_OP_ARIT: [+\-*/^]
    lexer.add_token("TOKEN_OP_ARIT", "(\\+|\\-|\\*|/|\\^)");

    // TOKEN_DELIM: [;(){},]
    lexer.add_token("TOKEN_DELIM", "(;|\\(|\\)|\\{|\\}|,)");

    // TOKEN_ID: [a-zA-Z_][a-zA-Z0-9_]*
    lexer.add_token("TOKEN_ID", ID_START + ID_CHAR + "*");

    // IGNORAR: [ \t\n\r]+
    lexer.add_token("IGNORAR", "( |\\t|\\n|\\r)+");

    return lexer;
}

DynArray<Token> PhysiCodeLexer::tokenize(const std::string& input) const
{
    DynArray<Token> all = lexer_.tokenize(input);
    DynArray<Token> filtered;

    for (nat_t i = 0; i < all.size(); ++i)
    {
        if (all[i].name != "IGNORAR" && all[i].name != "COMENTARIO")
        {
            filtered.append(all[i]);
        }
    }

    return filtered;
}

DynArray<Token> PhysiCodeLexer::tokenize_file(const std::string& filepath) const
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw std::runtime_error("No se pudo abrir el archivo: " + filepath);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return tokenize(buffer.str());
}

const Lexer& PhysiCodeLexer::get_lexer() const
{
    return lexer_;
}

} // namespace PhysiCode