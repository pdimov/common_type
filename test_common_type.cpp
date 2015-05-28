#include "common_type_impl.hpp"
#include <boost/type_traits/add_rvalue_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>

template<class T> typename boost::add_rvalue_reference<T>::type declval();

#if !defined( BOOST_NO_CXX11_DECLTYPE )

template<class T, class U> struct common_type_decltype
{
    typedef decltype( declval<bool>()? declval<T>(): declval<U>() ) C;
    typedef typename boost::remove_cv< typename boost::decay<C>::type >::type type;
};

#endif

#if defined(USE_DECLTYPE)

template<class T, class U> struct common_type: public common_type_decltype<T, U>
{
};

#else

template<class T, class U> struct common_type: public boost::common_type_detail::common_type_impl<T, U>
{
};

#endif

//

template<class T, class U, class E> void test()
{
    typedef typename common_type<T, U>::type C;

    BOOST_TEST_TRAIT_TRUE(( boost::is_same<C, E> ));
    BOOST_TEST_TRAIT_TRUE(( boost::is_convertible<T, C> ));
    BOOST_TEST_TRAIT_TRUE(( boost::is_convertible<U, C> ));

#if !defined( BOOST_NO_CXX11_DECLTYPE )

    typedef typename common_type_decltype<T, U>::type E2;
    BOOST_TEST_TRAIT_TRUE(( boost::is_same<C, E2> ));

#endif
}

//

struct C1 {};
    
struct C2 {};
    
struct C3: C2 {};

struct C1C2
{
    C1C2(C1 const&) {}
    C1C2(C2 const&) {}
};

enum E1
{
    e1
};

enum E2
{
    e2
};

struct C4
{
    C4( int ) {}
};

struct C5
{
    C5( E1 ) {}
};

struct C6
{
    operator E2() const { return e2; }
};

template<class T> struct C7
{
    operator T() const { return 0; }
};

static void test_class_types()
{
    test<C1C2&, C1&, C1C2>();
    test<C1C2&, C2&, C1C2>();

    test<C1, C1C2, C1C2>();
    test<C2, C1C2, C1C2>();
    test<C1C2, C1, C1C2>();
    test<C1C2, C2, C1C2>();

    test<C2&, C3&, C2>();
    test<C3&, C2&, C2>();

    test<int, C4, C4>();
    test<C4, int, C4>();

    test<int&, C4&, C4>();
    test<C4&, int&, C4>();

    test<E1, C4, C4>();
    test<C4, E1, C4>();

    test<E1&, C4&, C4>();
    test<C4&, E1&, C4>();

    test<E1, C5, C5>();
    test<C5, E1, C5>();

    test<E1&, C5&, C5>();
    test<C5&, E1&, C5>();

    test<E2, C6, E2>();
    test<C6, E2, E2>();

    test<E2&, C6&, E2>();
    test<C6&, E2&, E2>();

    test<int, C6, int>();
    test<C6, int, int>();

    test<int&, C6&, int>();
    test<C6&, int&, int>();
}

static void test_arithmetic_types()
{
    test<char, char, char>();
    test<char, unsigned char, int>();
    test<char, short, int>();
    test<char, unsigned short, int>();
    test<char, int, int>();
    test<char, unsigned int, unsigned int>();
    test<char, long long, long long>();
    test<char, unsigned long long, unsigned long long>();
    test<char, float, float>();
    test<char, double, double>();
    test<char, long double, long double>();
    test<char, E1, int>();

    test<unsigned char, char, int>();
    test<unsigned char, unsigned char, unsigned char>();
    test<unsigned char, short, int>();
    test<unsigned char, unsigned short, int>();
    test<unsigned char, int, int>();
    test<unsigned char, unsigned int, unsigned int>();
    test<unsigned char, long long, long long>();
    test<unsigned char, unsigned long long, unsigned long long>();
    test<unsigned char, float, float>();
    test<unsigned char, double, double>();
    test<unsigned char, long double, long double>();
    test<unsigned char, E1, int>();

    test<short, char, int>();
    test<short, unsigned char, int>();
    test<short, short, short>();
    test<short, unsigned short, int>();
    test<short, int, int>();
    test<short, unsigned int, unsigned int>();
    test<short, long long, long long>();
    test<short, unsigned long long, unsigned long long>();
    test<short, float, float>();
    test<short, double, double>();
    test<short, long double, long double>();
    test<short, E1, int>();

    test<unsigned short, char, int>();
    test<unsigned short, unsigned char, int>();
    test<unsigned short, short, int>();
    test<unsigned short, unsigned short, unsigned short>();
    test<unsigned short, int, int>();
    test<unsigned short, unsigned int, unsigned int>();
    test<unsigned short, long long, long long>();
    test<unsigned short, unsigned long long, unsigned long long>();
    test<unsigned short, float, float>();
    test<unsigned short, double, double>();
    test<unsigned short, long double, long double>();
    test<unsigned short, E1, int>();

    test<int, char, int>();
    test<int, unsigned char, int>();
    test<int, short, int>();
    test<int, unsigned short, int>();
    test<int, int, int>();
    test<int, unsigned int, unsigned int>();
    test<int, long long, long long>();
    test<int, unsigned long long, unsigned long long>();
    test<int, float, float>();
    test<int, double, double>();
    test<int, long double, long double>();
    test<int, E1, int>();

    test<unsigned int, char, unsigned int>();
    test<unsigned int, unsigned char, unsigned int>();
    test<unsigned int, short, unsigned int>();
    test<unsigned int, unsigned short, unsigned int>();
    test<unsigned int, int, unsigned int>();
    test<unsigned int, unsigned int, unsigned int>();
    test<unsigned int, long long, long long>();
    test<unsigned int, unsigned long long, unsigned long long>();
    test<unsigned int, float, float>();
    test<unsigned int, double, double>();
    test<unsigned int, long double, long double>();
    test<unsigned int, E1, unsigned int>();

    test<long long, char, long long>();
    test<long long, unsigned char, long long>();
    test<long long, short, long long>();
    test<long long, unsigned short, long long>();
    test<long long, int, long long>();
    test<long long, unsigned int, long long>();
    test<long long, long long, long long>();
    test<long long, unsigned long long, unsigned long long>();
    test<long long, float, float>();
    test<long long, double, double>();
    test<long long, long double, long double>();
    test<long long, E1, long long>();

    test<unsigned long long, char, unsigned long long>();
    test<unsigned long long, unsigned char, unsigned long long>();
    test<unsigned long long, short, unsigned long long>();
    test<unsigned long long, unsigned short, unsigned long long>();
    test<unsigned long long, int, unsigned long long>();
    test<unsigned long long, unsigned int, unsigned long long>();
    test<unsigned long long, long long, unsigned long long>();
    test<unsigned long long, unsigned long long, unsigned long long>();
    test<unsigned long long, float, float>();
    test<unsigned long long, double, double>();
    test<unsigned long long, long double, long double>();
    test<unsigned long long, E1, unsigned long long>();

    test<float, char, float>();
    test<float, unsigned char, float>();
    test<float, short, float>();
    test<float, unsigned short, float>();
    test<float, int, float>();
    test<float, unsigned int, float>();
    test<float, long long, float>();
    test<float, unsigned long long, float>();
    test<float, float, float>();
    test<float, double, double>();
    test<float, long double, long double>();
    test<float, E1, float>();

    test<double, char, double>();
    test<double, unsigned char, double>();
    test<double, short, double>();
    test<double, unsigned short, double>();
    test<double, int, double>();
    test<double, unsigned int, double>();
    test<double, long long, double>();
    test<double, unsigned long long, double>();
    test<double, float, double>();
    test<double, double, double>();
    test<double, long double, long double>();
    test<double, E1, double>();

    test<long double, char, long double>();
    test<long double, unsigned char, long double>();
    test<long double, short, long double>();
    test<long double, unsigned short, long double>();
    test<long double, int, long double>();
    test<long double, unsigned int, long double>();
    test<long double, long long, long double>();
    test<long double, unsigned long long, long double>();
    test<long double, float, long double>();
    test<long double, double, long double>();
    test<long double, long double, long double>();
    test<long double, E1, long double>();

    test<E1, char, int>();
    test<E1, unsigned char, int>();
    test<E1, short, int>();
    test<E1, unsigned short, int>();
    test<E1, int, int>();
    test<E1, unsigned int, unsigned int>();
    test<E1, long long, long long>();
    test<E1, unsigned long long, unsigned long long>();
    test<E1, float, float>();
    test<E1, double, double>();
    test<E1, long double, long double>();
    test<E1, E1, E1>();
    test<E1, E2, int>();

    //

    test<int const, int const, int>();
    test<int const, long const, long>();

    //

    test<C7<char>, char, char>();
    test<C7<char>, unsigned char, unsigned char>();
    test<C7<char>, short, short>();
    test<C7<char>, unsigned short, unsigned short>();
    test<C7<char>, int, int>();
    test<C7<char>, unsigned int, unsigned int>();
    test<C7<char>, long long, long long>();
    test<C7<char>, unsigned long long, unsigned long long>();
    test<C7<char>, float, float>();
    test<C7<char>, double, double>();
    test<C7<char>, long double, long double>();

#if !defined( BOOST_MSVC ) || ( BOOST_MSVC > 1800 )

    // msvc-8.0, msvc-10.0, msvc-11.0, msvc-12.0 fail to compile x? C7<T>(): C7<U>()

    test<C7<char>, C7<char>, C7<char> >();
    test<C7<char>, C7<unsigned char>, int>();
    test<C7<char>, C7<short>, int>();
    test<C7<char>, C7<unsigned short>, int>();
    test<C7<char>, C7<int>, int>();
    test<C7<char>, C7<unsigned int>, unsigned int>();
    test<C7<char>, C7<long long>, long long>();
    test<C7<char>, C7<unsigned long long>, unsigned long long>();
    test<C7<char>, C7<float>, float>();
    test<C7<char>, C7<double>, double>();
    test<C7<char>, C7<long double>, long double>();

#endif
}

static void test_pointer_types()
{
    test<int*, int const*, int const*>();
    test<int*, int volatile*, int volatile*>();
    test<int const*, int volatile*, int const volatile*>();

    test<int*, void const*, void const*>();
    test<void*, int const*, void const*>();

    test<int*, void volatile*, void volatile*>();
    test<void*, int volatile*, void volatile*>();

    test<int const*, void volatile*, void const volatile*>();
    test<void const*, int volatile*, void const volatile*>();

    test<int const* const*, int volatile* const*, int const volatile* const*>();

#if !defined( BOOST_MSVC ) || ( BOOST_MSVC != 1600 )

    // add_rvalue_reference fails for int[] under msvc-10.0

    test<int[], int[], int*>();
    test<int[], int const[], int const*>();
    test<int volatile[], int const[], int const volatile*>();

    test<int volatile* const[], int const* const[], int const volatile* const*>();

#endif

    test<C3*, C2*, C2*>();
    test<C2*, C3*, C2*>();

    test<C3 const*, C2 volatile*, C2 const volatile*>();
    test<C2 const*, C3 volatile*, C2 const volatile*>();
}

static void test_member_pointer_types()
{
    test<int C1::*, int const C1::*, int const C1::*>();
    test<int C1::*, int volatile C1::*, int volatile C1::*>();
    test<int const C1::*, int volatile C1::*, int const volatile C1::*>();

    test<int C2::*, int const C3::*, int const C3::*>();
    test<int C2::*, int volatile C3::*, int volatile C3::*>();
    test<int const C2::*, int volatile C3::*, int const volatile C3::*>();

    test<int C3::*, int const C2::*, int const C3::*>();
    test<int C3::*, int volatile C2::*, int volatile C3::*>();
    test<int const C3::*, int volatile C2::*, int const volatile C3::*>();
}

int main()
{
    test_class_types();
    test_arithmetic_types();
    test_pointer_types();
    test_member_pointer_types();

    return boost::report_errors();
}
