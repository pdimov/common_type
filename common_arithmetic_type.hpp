#ifndef BOOST_TYPE_TRAITS_DETAIL_COMMON_ARITHMETIC_TYPE_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_COMMON_ARITHMETIC_TYPE_HPP_INCLUDED

namespace boost
{

namespace detail
{

template<int I> struct arithmetic_type;

// Types bool, char, char16_t, char32_t, wchar_t,
// and the signed and unsigned integer types are
// collectively called integral types

template<> struct arithmetic_type<1>
{
    typedef bool type;
    typedef char (&result_type) [1];
};

template<> struct arithmetic_type<2>
{
    typedef char type;
    typedef char (&result_type) [2];
};

template<> struct arithmetic_type<3>
{
    typedef wchar_t type;
    typedef char (&result_type) [3];
};

// There are five standard signed integer types:
// “signed char”, “short int”, “int”, “long int”, and “long long int”.

template<> struct arithmetic_type<4>
{
    typedef signed char type;
    typedef char (&result_type) [4];
};

template<> struct arithmetic_type<5>
{
    typedef short type;
    typedef char (&result_type) [5];
};

template<> struct arithmetic_type<6>
{
    typedef int type;
    typedef char (&result_type) [6];
};

template<> struct arithmetic_type<7>
{
    typedef long type;
    typedef char (&result_type) [7];
};

template<> struct arithmetic_type<8>
{
    typedef long long type;
    typedef char (&result_type) [8];
};

// For each of the standard signed integer types, there exists a corresponding
// (but different) standard unsigned integer type: “unsigned char”, “unsigned short int”,
// “unsigned int”, “unsigned long int”, and “unsigned long long int”

template<> struct arithmetic_type<9>
{
    typedef unsigned char type;
    typedef char (&result_type) [9];
};

template<> struct arithmetic_type<10>
{
    typedef unsigned short type;
    typedef char (&result_type) [10];
};

template<> struct arithmetic_type<11>
{
    typedef unsigned int type;
    typedef char (&result_type) [11];
};

template<> struct arithmetic_type<12>
{
    typedef unsigned long type;
    typedef char (&result_type) [12];
};

template<> struct arithmetic_type<13>
{
    typedef unsigned long long type;
    typedef char (&result_type) [13];
};

// There are three floating point types: float, double, and long double.

template<> struct arithmetic_type<14>
{
    typedef float type;
    typedef char (&result_type) [14];
};

template<> struct arithmetic_type<15>
{
    typedef double type;
    typedef char (&result_type) [15];
};

template<> struct arithmetic_type<16>
{
    typedef long double type;
    typedef char (&result_type) [16];
};

template<class T, class U> class common_arithmetic_impl
{
private:

    static arithmetic_type<1>::result_type select( arithmetic_type<1>::type );
    static arithmetic_type<2>::result_type select( arithmetic_type<2>::type );
    static arithmetic_type<3>::result_type select( arithmetic_type<3>::type );
    static arithmetic_type<4>::result_type select( arithmetic_type<4>::type );
    static arithmetic_type<5>::result_type select( arithmetic_type<5>::type );
    static arithmetic_type<6>::result_type select( arithmetic_type<6>::type );
    static arithmetic_type<7>::result_type select( arithmetic_type<7>::type );
    static arithmetic_type<8>::result_type select( arithmetic_type<8>::type );
    static arithmetic_type<9>::result_type select( arithmetic_type<9>::type );
    static arithmetic_type<10>::result_type select( arithmetic_type<10>::type );
    static arithmetic_type<11>::result_type select( arithmetic_type<11>::type );
    static arithmetic_type<12>::result_type select( arithmetic_type<12>::type );
    static arithmetic_type<13>::result_type select( arithmetic_type<13>::type );
    static arithmetic_type<14>::result_type select( arithmetic_type<14>::type );
    static arithmetic_type<15>::result_type select( arithmetic_type<15>::type );
    static arithmetic_type<16>::result_type select( arithmetic_type<16>::type );

    static bool cond();

public:

    typedef typename arithmetic_type< sizeof(select( cond()? T(): U() )) >::type type;
};

} // namespace detail

template<class T, class U> struct common_arithmetic_type
{
    typedef typename detail::common_arithmetic_impl<T, U>::type type;
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_COMMON_ARITHMETIC_TYPE_HPP_INCLUDED
