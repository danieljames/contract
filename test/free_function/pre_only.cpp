
// Test pre only specified (for free func, but same for all contracts).

#include "../aux_/oteststream.hpp"
#include <boost/contract/free_function.hpp>
#include <boost/contract/var.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

boost::contract::aux::test::oteststream out;

void f() {
    boost::contract::var contract = boost::contract::free_function()
        .precondition([] { out << "f::pre" << std::endl; })
    ;
    out << "f::body" << std::endl;
}

int main() {
    std::ostringstream ok;

    out.str("");
    f();
    ok.str("");
    ok
        << "f::pre" << std::endl
        << "f::body" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}
