#ifndef _LUACOMPILER_TEST_HPP
#define _LUACOMPILER_TEST_HPP

#include <parser.hpp>
#include <ast.hpp>

template<typename T, typename P>
bool test_parser(std::string input, P const& parser, bool full_match = true)
{
    using boost::spirit::ascii::space;

    T result;
    std::string::const_iterator iter = input.begin();
    std::string::const_iterator end = input.end();

    bool success = phrase_parse(iter, end, parser, space, result);

    return (success && iter == end);
}

#endif // _LUACOMPILER_TEST_HPP
