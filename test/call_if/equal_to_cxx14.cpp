
// Copyright (C) 2008-2017 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test call_if equality check with C++14 generic lambdas.

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX14_GENERIC_LAMBDAS

int main() { return 0; } // Test trivially always pass.

#else // This test requires C++14 generic lambdas.

#include "../detail/oteststream.hpp"
#include <boost/contract/call_if.hpp>
#include <boost/type_traits/has_equal_to.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <functional> // std::bind for generic lambdas.
#include <sstream>

boost::contract::test::detail::oteststream out;

struct x {}; // Does not have operator==.

int main() {
    std::ostringstream ok;
    x x1, x2;
    
    out.str("");
    out <<
        boost::contract::call_if<boost::has_equal_to<int> >(
            std::bind([] (auto a, auto b) { return a == b; }, 123, 456)
        ).else_([] { return true; })
    << std::endl;
    ok.str(""); ok << false << std::endl;
    BOOST_TEST(out.eq(ok.str()));

    out.str("");
    out <<
        boost::contract::call_if<boost::has_equal_to<x> >(
            std::bind([] (auto a, auto b) { return a == b; }, x1, x2)
        ).else_([] { return true; })
    << std::endl;
    ok.str(""); ok << true << std::endl;
    BOOST_TEST(out.eq(ok.str()));
    
    out.str("");
    out << // Test explicit result, cannot deduce from lambda missing `-> bool`.
        boost::contract::call_if<boost::has_equal_to<x> >(
            std::bind([] (auto a, auto b) { return a == b; }, x1, x2)
        ).else_([] { return true; })
    << std::endl;
    ok.str(""); ok << true << std::endl;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

#endif // BOOST_NO_CXX14_GENERIC_LAMBDAS

