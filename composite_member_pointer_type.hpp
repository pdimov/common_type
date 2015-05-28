#ifndef BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_MEMBER_POINTER_TYPE_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_MEMBER_POINTER_TYPE_HPP_INCLUDED

#include "composite_pointer_type.hpp"
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost
{

template<class T, class U> struct composite_member_pointer_type;

namespace detail
{

template<class C1, class C2> struct common_member_class;

template<class C> struct common_member_class<C, C>
{
    typedef C type;
};

template<class C1, class C2> struct common_member_class
{
    typedef typename boost::conditional<

        boost::is_base_of<C1, C2>::value,
        C2,
        typename boost::conditional<boost::is_base_of<C2, C1>::value, C1, void>::type

    >::type type;
};

} // namespace detail

template<class C1, class T1, class C2, class T2> struct composite_member_pointer_type<T1 C1::*, T2 C2::*>
{
private:

    typedef typename boost::composite_pointer_type<T1*, T2*>::type CPT;
    typedef typename boost::remove_pointer<CPT>::type CT;

    typedef typename detail::common_member_class<C1, C2>::type CB;

public:

    typedef CT CB::* type;
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_COMPOSITE_MEMBER_POINTER_TYPE_HPP_INCLUDED
