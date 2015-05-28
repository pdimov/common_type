#ifndef BOOST_TYPE_TRAITS_DETAIL_TP_IDENTITY_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_TP_IDENTITY_HPP_INCLUDED

namespace boost
{

template<class T> struct tp_identity
{
    typedef T type;
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_TP_IDENTITY_HPP_INCLUDED
