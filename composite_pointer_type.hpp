#ifndef BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_POINTER_TYPE_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_POINTER_TYPE_HPP_INCLUDED

#include "copy_cv.hpp"
#include "tp_identity.hpp"
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost
{

template<class T, class U> struct composite_pointer_type;

namespace detail
{

template<class T, class U> struct has_common_pointee
{
private:

    typedef typename boost::remove_cv<T>::type T2;
    typedef typename boost::remove_cv<U>::type U2;

public:

    BOOST_STATIC_CONSTANT( bool, value =
        (boost::is_same<T2, U2>::value)
        || boost::is_void<T2>::value
        || boost::is_void<U2>::value
        || (boost::is_base_of<T2, U2>::value)
        || (boost::is_base_of<U2, T2>::value) );
};

template<class T, class U> struct common_pointee
{
private:

    typedef typename boost::remove_cv<T>::type T2;
    typedef typename boost::remove_cv<U>::type U2;

public:

    typedef typename boost::conditional<

        boost::is_same<T2, U2>::value || boost::is_void<T2>::value || boost::is_base_of<T2, U2>::value,
        typename boost::copy_cv<T, U>::type,
        typename boost::copy_cv<U, T>::type

    >::type type;
};

template<class T, class U> struct composite_pointer_impl
{
private:

    typedef typename boost::remove_cv<T>::type T2;
    typedef typename boost::remove_cv<U>::type U2;

public:

    typedef typename boost::copy_cv<typename boost::copy_cv<typename composite_pointer_type<T2, U2>::type const, T>::type, U>::type type;
};

} // detail

template<class T, class U> struct composite_pointer_type<T*, U*>
{
    typedef typename boost::conditional<

        detail::has_common_pointee<T, U>::value,
        detail::common_pointee<T, U>,
        detail::composite_pointer_impl<T, U>

    >::type::type * type;
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_POINTER_TYPE_HPP_INCLUDED
