
#include <boost/contract/aux_/invariant.hpp>
#include <boost/detail/lightweight_test.hpp>

struct x {}; // Test no invariants.

struct c {
    void invariant() const {} // Test const invariant.
};

struct cv {
    void invariant() const volatile {} // Test const volatile invariant.
};

struct i {
    void invariant() {} // Test non-const, non-volatile invariant.
};

struct si {
    static void invariant() {} // Test static invariant.
};

struct s {
    static void static_invariant() {} // Test static invariant.
};

struct ns {
    void static_invariant() {} // Test non-static invariant.
};

int main() {
    BOOST_TEST(!boost::contract::aux::has_const_invariant<x>::value);
    BOOST_TEST(!boost::contract::aux::has_const_volatile_invariant<x>::value);
    BOOST_TEST(!boost::contract::aux::has_invariant<x>::value);
    BOOST_TEST(!boost::contract::aux::has_static_invariant<x>::value);
    BOOST_TEST(!boost::contract::aux::has_non_static_invariant<x>::value);
    
    BOOST_TEST( boost::contract::aux::has_const_invariant<c>::value);
    BOOST_TEST(!boost::contract::aux::has_const_volatile_invariant<c>::value);
    BOOST_TEST(!boost::contract::aux::has_invariant<c>::value);
    BOOST_TEST(!boost::contract::aux::has_static_invariant<c>::value);
    BOOST_TEST(!boost::contract::aux::has_non_static_invariant<c>::value);
    
    BOOST_TEST(!boost::contract::aux::has_const_invariant<cv>::value);
    BOOST_TEST( boost::contract::aux::has_const_volatile_invariant<cv>::value);
    BOOST_TEST(!boost::contract::aux::has_invariant<cv>::value);
    BOOST_TEST(!boost::contract::aux::has_static_invariant<cv>::value);
    BOOST_TEST(!boost::contract::aux::has_non_static_invariant<cv>::value);
    
    BOOST_TEST(!boost::contract::aux::has_const_invariant<i>::value);
    BOOST_TEST(!boost::contract::aux::has_const_volatile_invariant<i>::value);
    BOOST_TEST( boost::contract::aux::has_invariant<i>::value);
    BOOST_TEST(!boost::contract::aux::has_static_invariant<i>::value);
    BOOST_TEST(!boost::contract::aux::has_non_static_invariant<i>::value);
    
    BOOST_TEST(!boost::contract::aux::has_const_invariant<ns>::value);
    BOOST_TEST(!boost::contract::aux::has_const_volatile_invariant<ns>::value);
    BOOST_TEST(!boost::contract::aux::has_invariant<ns>::value);
    BOOST_TEST(!boost::contract::aux::has_static_invariant<ns>::value);
    BOOST_TEST( boost::contract::aux::has_non_static_invariant<ns>::value);

    return boost::report_errors();
}
