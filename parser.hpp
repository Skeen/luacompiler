#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

#include "ast.hpp"

namespace parser
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    namespace phoenix = boost::phoenix;

    template <typename Iterator>
    struct lua_parser : qi::grammar<Iterator, ast::program(), ascii::space_type>
    {
        lua_parser() : lua_parser::base_type(start)
        {
            using qi::int_;
            using qi::lit;
            using qi::double_;
            using qi::lexeme;
            using qi::_1;

            using ascii::char_;
            using ascii::alpha;
            using ascii::alnum;

            using phoenix::push_back;

            start %= program;

            program %= statement % ';';

            statement %= print_or_assignment;
            
            print_or_assignment %= print | assignment;

            assignment %= lit("local") >> +(char_ - ';' - '=') >> '=' >> expression;
                
            print %= lit("print") >> +(char_ - ';');

            expression %= atom_nil | atom_false | atom_true;

            atom_nil %= lit("nil");
            atom_false %= lit("false");
            atom_true %= lit("true");

            name %= (alpha | char_('_')) >> *(alnum | char_('_'));

                /*
and       break     do        else      elseif
     end       false     for       function  if
     in        local     nil       not       or
     repeat    return    then      true      until     while
     */
        }

        qi::rule<Iterator, ast::program(), ascii::space_type> start;
        qi::rule<Iterator, std::vector<ast::statement>(), ascii::space_type> program;
        qi::rule<Iterator, ast::statement(), ascii::space_type> statement;
        qi::rule<Iterator, ast::print_or_assign(), ascii::space_type> print_or_assignment;
        qi::rule<Iterator, ast::assignment(), ascii::space_type> assignment;
        qi::rule<Iterator, ast::print(), ascii::space_type> print;
        qi::rule<Iterator, ast::expression(), ascii::space_type> expression;
        qi::rule<Iterator, std::string(), ascii::space_type> atom_nil;
        qi::rule<Iterator, std::string(), ascii::space_type> atom_false;
        qi::rule<Iterator, std::string(), ascii::space_type> atom_true;
        qi::rule<Iterator, ast::name(), ascii::space_type> name;
        /*
        qi::rule<Iterator, ast::atom_nil(), ascii::space_type> atom_nil;
        qi::rule<Iterator, ast::atom_false(), ascii::space_type> atom_false;
        qi::rule<Iterator, ast::atom_true(), ascii::space_type> atom_true;
        */
    };
}
