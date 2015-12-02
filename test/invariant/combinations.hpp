
// no #include guard

// Test all invariants combinations (static/cv/const-only) for all operations.

#include "../aux_/oteststream.hpp"
#include <boost/contract/base_types.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/public_function.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/guard.hpp>
#include <boost/contract/assert.hpp>
#include <boost/detail/lightweight_test.hpp>

boost::contract::aux::test::oteststream out;

struct b : private boost::contract::constructor_precondition<b> {
    // Test also with no base_types.

#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
    static void static_invariant() { out << "b::static_inv" << std::endl; }
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
    void invariant() const volatile { out << "b::cv_inv" << std::endl; }
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
    void invariant() const { out << "b::const_inv" << std::endl; }
#endif
    
    b() : boost::contract::constructor_precondition<b>([] {
        out << "b::ctor::pre" << std::endl;
    }) {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([] { out << "b::ctor::old" << std::endl; })
            .postcondition([] { out << "b::ctor::post" << std::endl; })
        ;
        out << "b::ctor::body" << std::endl;
    }

    virtual ~b() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([] { out << "b::dtor::old" << std::endl; })
            .postcondition([] { out << "b::dtor::post" << std::endl; })
        ;
        out << "b::dtor::body" << std::endl;
    }

    virtual void f(char x, boost::contract::virtual_* v = 0) volatile {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "b::f::volatile_pre" << std::endl;
                BOOST_CONTRACT_ASSERT(x == 'b');
            })
            .old([] { out << "b::f::volatile_old" << std::endl; })
            .postcondition([] { out << "b::f::volatile_post" << std::endl; })
        ;
        out << "b::f::volatile_body" << std::endl;
    }
    
    virtual void f(char x, boost::contract::virtual_* v = 0) {
        boost::contract::guard c = boost::contract::public_function(v, this)
            .precondition([&] {
                out << "b::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(x == 'b');
            })
            .old([] { out << "b::f::old" << std::endl; })
            .postcondition([] { out << "b::f::post" << std::endl; })
        ;
        out << "b::f::body" << std::endl;
    }
};

struct a
    #define BASES private boost::contract::constructor_precondition<a>, public b
    : BASES
{
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES

#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
    static void static_invariant() { out << "a::static_inv" << std::endl; }
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
    void invariant() const volatile { out << "a::cv_inv" << std::endl; }
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
    void invariant() const { out << "a::const_inv" << std::endl; }
#endif

    a() : boost::contract::constructor_precondition<a>([] {
        out << "a::ctor::pre" << std::endl;
    }) {
        boost::contract::guard c = boost::contract::constructor(this)
            .old([] { out << "a::ctor::old" << std::endl; })
            .postcondition([] { out << "a::ctor::post" << std::endl; })
        ;
        out << "a::ctor::body" << std::endl;
    }
    
    virtual ~a() {
        boost::contract::guard c = boost::contract::destructor(this)
            .old([] { out << "a::dtor::old" << std::endl; })
            .postcondition([] { out << "a::dtor::post" << std::endl; })
        ;
        out << "a::dtor::body" << std::endl;
    }

    virtual void f(char x, boost::contract::virtual_* v = 0)
            volatile /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(
            v,
            static_cast<void (a::*)(char x, boost::contract::virtual_*)
                    volatile>(&a::f),
            this, x
        )
            .precondition([&] {
                out << "a::f::volatile_pre" << std::endl;
                BOOST_CONTRACT_ASSERT(x == 'a');
            })
            .old([] { out << "a::f::volatile_old" << std::endl; })
            .postcondition([] { out << "a::f::volatile_post" << std::endl; })
        ;
        out << "a::f::volatile_body" << std::endl;
    }
    
    virtual void f(char x, boost::contract::virtual_* v = 0) /* override */ {
        boost::contract::guard c = boost::contract::public_function<
                override_f>(
            v,
            static_cast<void (a::*)(char x, boost::contract::virtual_*)>(&a::f),
            this, x
        )
            .precondition([&] {
                out << "a::f::pre" << std::endl;
                BOOST_CONTRACT_ASSERT(x == 'a');
            })
            .old([] { out << "a::f::old" << std::endl; })
            .postcondition([] { out << "a::f::post" << std::endl; })
        ;
        out << "a::f::body" << std::endl;
    }

    static void s() {
        boost::contract::guard c = boost::contract::public_function<a>()
            .precondition([] { out << "a::s::pre" << std::endl; })
            .old([] { out << "a::s::old" << std::endl; })
            .postcondition([] { out << "a::s::post" << std::endl; })
        ;
        out << "a::s::body" << std::endl;
    }

protected:
    void p() volatile {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "a::p::volatile_pre" << std::endl; })
            .old([] { out << "a::p::volatile_old" << std::endl; })
            .postcondition([] { out << "a::p::volatile_post" << std::endl; })
        ;
        out << "a::p::volatile_body" << std::endl;
    }
    
    void p() {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "a::p::pre" << std::endl; })
            .old([] { out << "a::p::old" << std::endl; })
            .postcondition([] { out << "a::p::post" << std::endl; })
        ;
        out << "a::p::body" << std::endl;
    }
public:
    void call_p() volatile { p(); }
    void call_p() { p(); }

private:
    void q() volatile {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "a::q::volatile_pre" << std::endl; })
            .old([] { out << "a::q::volatile_old" << std::endl; })
            .postcondition([] { out << "a::q::volatile_post" << std::endl; })
        ;
        out << "a::q::volatile_body" << std::endl;
    }
    
    void q() {
        boost::contract::guard c = boost::contract::function()
            .precondition([] { out << "a::q::pre" << std::endl; })
            .old([] { out << "a::q::old" << std::endl; })
            .postcondition([] { out << "a::q::post" << std::endl; })
        ;
        out << "a::q::body" << std::endl;
    }
public:
    void call_q() volatile { q(); }
    void call_q() { q(); }

    BOOST_CONTRACT_OVERRIDE(f)
};

int main() {
    std::ostringstream ok;

    { // Test volatile call with bases.
        out.str("");
        a volatile av;
        ok.str(""); ok // Ctors always check const_inv (even if volatile).
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::ctor::post" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "a::const_inv" << std::endl
#endif
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));

        out.str("");
        av.f('a');
        ok.str(""); ok // Volatile checks static and cv (but not const) inv.
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
            << "b::f::volatile_pre" << std::endl
            << "a::f::volatile_pre" << std::endl
            << "b::f::volatile_old" << std::endl
            << "a::f::volatile_old" << std::endl
            << "a::f::volatile_body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
            << "b::f::volatile_old" << std::endl
            << "b::f::volatile_post" << std::endl
            // No old call here because not a base object.
            << "a::f::volatile_post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
    
        out.str("");
        av.s(); // Test static call.
        ok.str(""); ok
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::s::pre" << std::endl
            << "a::s::old" << std::endl
            << "a::s::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::s::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        av.call_p(); // Test (indirect) protected call.
        ok.str(""); ok
            << "a::p::volatile_pre" << std::endl
            << "a::p::volatile_old" << std::endl
            << "a::p::volatile_body" << std::endl
            << "a::p::volatile_post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        av.call_q(); // Test (indirect) private call.
        ok.str(""); ok
            << "a::q::volatile_pre" << std::endl
            << "a::q::volatile_old" << std::endl
            << "a::q::volatile_body" << std::endl
            << "a::q::volatile_post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
    } // Call a's destructor.
    ok.str(""); ok // Dtors always check const_inv (even if volatile).
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "a::const_inv" << std::endl
#endif
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "a::static_inv" << std::endl
#endif
        << "a::dtor::post" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "b::const_inv" << std::endl
#endif
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
        << "b::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    { // Test non-volatile call with bases.
        out.str("");
        a aa;
        ok.str(""); ok
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::ctor::post" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::ctor::old" << std::endl
            << "a::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "a::const_inv" << std::endl
#endif
            << "a::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));

        out.str("");
        aa.f('a');
        ok.str(""); ok // Mutable checks static, cv, and const-only inv.
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "a::const_inv" << std::endl
#endif
            << "b::f::pre" << std::endl
            << "a::f::pre" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
            << "a::f::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "a::const_inv" << std::endl
#endif
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        aa.s(); // Test static call.
        ok.str(""); ok
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::s::pre" << std::endl
            << "a::s::old" << std::endl
            << "a::s::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "a::static_inv" << std::endl
#endif
            << "a::s::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        aa.call_p(); // Test (indirect) protected call.
        ok.str(""); ok
            << "a::p::pre" << std::endl
            << "a::p::old" << std::endl
            << "a::p::body" << std::endl
            << "a::p::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        aa.call_q(); // Test (indirect) private call.
        ok.str(""); ok
            << "a::q::pre" << std::endl
            << "a::q::old" << std::endl
            << "a::q::body" << std::endl
            << "a::q::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));

        out.str("");
    } // Call a's destructor.
    ok.str(""); ok
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "a::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "a::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "a::const_inv" << std::endl
#endif
        << "a::dtor::old" << std::endl
        << "a::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "a::static_inv" << std::endl
#endif
        << "a::dtor::post" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "b::const_inv" << std::endl
#endif
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
        << "b::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    
    { // Test volatile call with no bases.
        out.str("");
        b volatile bv;
        ok.str(""); ok // Ctors always check const_inv (even if volatile).
            << "b::ctor::pre" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
        bv.f('b');
        ok.str(""); ok // Volatile checks static and cv (but not const) inv.
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
            << "b::f::volatile_pre" << std::endl
            << "b::f::volatile_old" << std::endl
            << "b::f::volatile_body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
            << "b::f::volatile_post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
    } // Call b's destructor.
    ok.str(""); ok // Dtors always check const_inv (even if volatile).
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "b::const_inv" << std::endl
#endif
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
        << "b::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    { // Test non-volatile call with no bases.
        out.str("");
        b bb;
        ok.str(""); ok
            << "b::ctor::pre" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
            << "b::ctor::old" << std::endl
            << "b::ctor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::ctor::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));

        out.str("");
        bb.f('b');
        ok.str(""); ok // Mutable checks static, cv, and const-only inv.
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::f::pre" << std::endl
            << "b::f::old" << std::endl
            << "b::f::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
            << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
            << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
            << "b::const_inv" << std::endl
#endif
            << "b::f::post" << std::endl
        ;
        BOOST_TEST(out.eq(ok.str()));
        
        out.str("");
    } // Call b's destructor.
    ok.str(""); ok
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CV_INV
        << "b::cv_inv" << std::endl
#endif
#ifdef BOOST_CONTRACT_AUX_TEST_CONST_INV
        << "b::const_inv" << std::endl
#endif
        << "b::dtor::old" << std::endl
        << "b::dtor::body" << std::endl
#ifdef BOOST_CONTRACT_AUX_TEST_STATIC_INV
        << "b::static_inv" << std::endl
#endif
        << "b::dtor::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}
