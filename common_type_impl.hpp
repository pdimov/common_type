#ifndef BOOST_TYPE_TRAITS_DETAIL_COMMON_TYPE_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_COMMON_TYPE_HPP_INCLUDED

#include "tp_identity.hpp"
#include "remove_cv_ref.hpp"
#include "common_arithmetic_type.hpp"
#include "composite_pointer_type.hpp"
#include "composite_member_pointer_type.hpp"
#include <boost/type_traits/is_lvalue_reference.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_union.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/decay.hpp>

namespace boost
{

namespace common_type_detail
{

// ?: preserves lvalue references, but std::common_type applies decay as a last
// step, so references are lost; we may as well decay in the beginning

template<class T, class U> struct common_type_impl2;

template<class T, class U> struct common_type_impl: public common_type_impl2<
    typename boost::remove_cv< typename boost::decay<T>::type >::type,
    typename boost::remove_cv< typename boost::decay<U>::type >::type
>
{
};


// void

template<> struct common_type_impl2<void, void>
{
    typedef void type;
};

template<class T> struct common_type_impl2<T, void>
{
    typedef T type;
};

template<class T> struct common_type_impl2<void, T>
{
    typedef T type;
};

// same type

template<class T> struct common_type_impl2<T, T>
{
    typedef T type;
};

// one of the operands is a class type, try conversions in both directions

template<class T, class U> struct ct_class
{
    BOOST_STATIC_CONSTANT( bool, ct = boost::is_class<T>::value || boost::is_union<T>::value );
    BOOST_STATIC_CONSTANT( bool, cu = boost::is_class<U>::value || boost::is_union<U>::value );

    BOOST_STATIC_CONSTANT( bool, value = ct || cu );
};

template<class T, class U> struct common_type_impl3;

template<class T, class U> struct common_type_class: public boost::conditional<

    boost::is_convertible<T, U>::value && !boost::is_convertible<U, T>::value,
    boost::tp_identity<U>,

    typename boost::conditional<

        boost::is_convertible<U, T>::value && !boost::is_convertible<T, U>::value,
        boost::tp_identity<T>,

        common_type_impl3<T, U>
    >::type
>::type
{
};

template<class T, class U> struct common_type_impl2: public boost::conditional<
    ct_class<T, U>::value,
    common_type_class<T, U>,
    common_type_impl3<T, U> >::type
{
};

// pointers

template<class T, class U> struct common_type_impl4;

template<class T, class U> struct common_type_impl3: public boost::conditional<
    boost::is_pointer<T>::value || boost::is_pointer<U>::value,
    composite_pointer_type<T, U>,
    common_type_impl4<T, U> >::type
{
};

// pointers to members

template<class T, class U> struct common_type_impl5;

template<class T, class U> struct common_type_impl4: public boost::conditional<
    boost::is_member_pointer<T>::value || boost::is_member_pointer<U>::value,
    composite_member_pointer_type<T, U>,
    common_type_impl5<T, U> >::type
{
};

// arithmetic types (including class types w/ conversions to arithmetic and enums)

template<class T, class U> struct common_type_impl5: public common_arithmetic_type<T, U>
{
};

} // namespace common_type_detail

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_COMMON_TYPE_HPP_INCLUDED
