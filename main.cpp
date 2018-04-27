#include <iostream>

#include "parser.hpp"
#include "ast.hpp"

int main()
{
    using boost::spirit::ascii::space;
    using iterator_type = std::string::const_iterator;
    using lua_parser = parser::lua_parser<iterator_type>;

    lua_parser parser;
    std::string input = "nil";
    ast::program program;
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator end = input.end();

    bool r = phrase_parse(iter, end, parser, space, program);
/*
    std::cout << test_parser<ast::print>("print ha", parser.print);
    std::cout << test_parser<ast::print>("print ja", parser.print);
    std::cout << test_parser<ast::print>("print", parser.print);

    std::cout << test_parser<ast::name>("print ha", parser.name);
    std::cout << test_parser<ast::name>("print ja", parser.name);
    std::cout << test_parser<ast::name>("print", parser.name);
    std::cout << test_parser<ast::name>("5print", parser.name);
    std::cout << test_parser<ast::name>("5", parser.name);
    std::cout << test_parser<ast::name>("", parser.name);
    std::cout << test_parser<ast::name>("_", parser.name);
*/
    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "got: " << program.to_string() << std::endl;
        std::cout << "\n-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }

    return 0;
}

