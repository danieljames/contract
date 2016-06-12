
// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract.hpp>
#include <boost/optional.hpp>
#include <cassert>

//[named_override_pure_virtual_assert_false
template<typename T>
class generic_unary_pack {
public:
    virtual void _1(T const& value, boost::contract::virtual_* v = 0) = 0;
    virtual T _1(boost::contract::virtual_* v = 0) const = 0;
};

template<typename T>
void generic_unary_pack<T>::_1(T const& value, boost::contract::virtual_* v) {
    boost::contract::guard c = boost::contract::public_function(v, this)
        .precondition([&] {
            // Derived concrete classes will enforce preconditions.
            BOOST_CONTRACT_ASSERT(false);
        })
    ;
    assert(false);
}

/* ... */
//]

template<typename T>
T generic_unary_pack<T>::_1(boost::contract::virtual_* v) const {
    boost::optional<T> result; // Do not assume T has default constructor.
    boost::contract::guard c = boost::contract::public_function(v, result, this)
        .postcondition([&] (boost::optional<T const&> const& result) {
            BOOST_CONTRACT_ASSERT(*result == _1());
        })
    ;

    assert(false);
    return *result;
}

//[named_override
template<typename T>
class positive_unary_pack
    #define BASES public generic_unary_pack<T>
    : BASES
{
public:
    typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
    #undef BASES
    
    // BOOST_CONTRACT_OVERRIDE(_1) would generate reserved symbol `override__1`.
    BOOST_CONTRACT_NAMED_OVERRIDE(override1, _1)

    virtual void _1(T const& value, boost::contract::virtual_* v = 0)
            /* override */ {
        // Use `override1` type generated by NAMED_OVERRIDE macro above.
        boost::contract::guard c = boost::contract::public_function<override1>(
            v,
            static_cast<void (positive_unary_pack::*)(T const&,
                    boost::contract::virtual_*)>(&positive_unary_pack::_1),
            this,
            value
        )
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(value > 0);
            })
        ;
        value1_ = value;
    }

    /* ... */
//]

    virtual T _1(boost::contract::virtual_* v = 0) const /* override */ {
        T result; // Class default constructor already used T's default ctor.
        boost::contract::guard c = boost::contract::public_function<override1>(
            v,
            result,
            static_cast<T (positive_unary_pack::*)(boost::contract::virtual_*)
                    const>(&positive_unary_pack::_1),
            this
        )
            .postcondition([&] (T const& result) {
                BOOST_CONTRACT_ASSERT(result > 0);
            })
        ;
        return result = value1_;
    }

private:
    T value1_;
};

int main() {
    positive_unary_pack<int> u;
    u._1(123);
    assert(u._1() == 123);
    return 0;
}

