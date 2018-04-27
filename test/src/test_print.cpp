#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "test.hpp"

BOOST_AUTO_TEST_CASE( my_test )
{
    using iterator_type = std::string::const_iterator;
    using lua_parser = parser::lua_parser<iterator_type>;
    lua_parser parser;

    BOOST_CHECK( test_parser<ast::print>("print", parser.print) );
    BOOST_CHECK( test_parser<ast::print>("print ha", parser.print) );
}
