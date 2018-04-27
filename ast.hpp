#ifndef _LUACOMPILER_AST_HPP
#define _LUACOMPILER_AST_HPP

#include <string>

#include <boost/fusion/include/adapt_struct.hpp>

namespace ast
{
    struct name
    {
        std::string name;

        std::string to_string()
        {
            return "name<" + name + ">";
        }
    };

    struct print
    {
        std::string variable;

        std::string to_string()
        {
            return "print<" + variable + ">";
        }
    };
/*
    using atom_nil = std::tuple<>;
    using atom_false = std::tuple<>;
    using atom_true = std::tuple<>;

    using expression_variant = boost::variant<
        ast::atom_nil,
        ast::atom_false,
        ast::atom_true
    >;
*/
    struct expression
    {
        //ast::expression_variant value;
        std::string value;

        std::string to_string()
        {
            std::string str = "statement<";
            /*
            if ( ast::atom_nil* atom = boost::get<ast::atom_nil>(&value))
                str += atom->to_string();
            if ( ast::atom_false* atom = boost::get<ast::atom_false>(&value))
                str += atom->to_string();
            if ( ast::atom_true* atom = boost::get<ast::atom_true>(&value))
                str += atom->to_string();
            */
            str += ">";
            return str;
        }
    };

    struct assignment
    {
        std::string variable;
        ast::expression value;

        std::string to_string()
        {
            return "assignment<" + variable + "=" + value.to_string() + ">";
        }
    };

    using print_or_assign = boost::variant<
        ast::print,
        ast::assignment
    >;

    struct statement
    {
        ast::print_or_assign contents;

        std::string to_string()
        {
            std::string str = "statement<";
            if ( ast::print* print = boost::get<ast::print>(&contents))
                str += print->to_string();
            else if ( ast::assignment* assign = boost::get<ast::assignment>(&contents))
                str += assign->to_string();
            str += ">";
            return str;
        }
    };

    struct program
    {
        std::vector<ast::statement> chunk;

        std::string to_string()
        {
            std::string str = "program<";
            if(not chunk.empty())
            {
                str += std::accumulate(
                    // Start at 2nd element
                    std::next(chunk.begin()), chunk.end(),
                    // Start string is first element
                    chunk[0].to_string(),
                    // For each element, concat with ',' in between
                    [](std::string a, statement b) {
                        return a + ',' + b.to_string();
                    }
                );
            }
            str += ">";
            return str;
        }
    };
}


BOOST_FUSION_ADAPT_STRUCT(
    ast::program,
    (std::vector<ast::statement>, chunk)
)

BOOST_FUSION_ADAPT_STRUCT(
    ast::statement,
    (ast::print_or_assign, contents)
)

BOOST_FUSION_ADAPT_STRUCT(
    ast::assignment,
    (std::string, variable),
    (ast::expression, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    ast::expression,
//    (ast::expression_variant, value)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    ast::print,
    (std::string, variable)
)

BOOST_FUSION_ADAPT_STRUCT(
    ast::name,
    (std::string, name)
)



#endif // _LUACOMPILER_AST_HPP
