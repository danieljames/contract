
// Test only middle base class has entry invariants.

#define BOOST_CONTRACT_AUX_TEST_NO_A_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_INV
#define BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "./decl.hpp"

#include "../aux_/oteststream.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    struct err {};
    boost::contract::set_entry_invariant_failed(
            [] (boost::contract::from) { throw err(); });

    a aa;

    a_entry_inv = false;
    b_entry_inv = true;
    c_entry_inv = true;
    out.str("");
    try {
        a_entering_inv = b_entering_inv = c_entering_inv = true;
        aa.f();
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl

            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = true;
    b_entry_inv = false;
    c_entry_inv = true;
    out.str("");
    try {
        a_entering_inv = b_entering_inv = c_entering_inv = true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl // Test this fail.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = true;
    b_entry_inv = true;
    c_entry_inv = false;
    out.str("");
    try {
        a_entering_inv = b_entering_inv = c_entering_inv = true;
        aa.f();
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl

            << "c::f::pre" << std::endl
            
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            
            << "a::f::body" << std::endl
            
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl

            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = false;
    b_entry_inv = false;
    c_entry_inv = false;
    out.str("");
    try {
        a_entering_inv = b_entering_inv = c_entering_inv = true;
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl // Test this failed (as all did).
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}
