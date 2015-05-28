#ifndef BOOST_TYPE_TRAITS_DETAIL_COPY_CV_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_COPY_CV_HPP_INCLUDED

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/conditional.hpp>

namespace boost
{

template<class T, class U> struct copy_cv
{
private:

    typedef typename boost::conditional<boost::is_const<U>::value, typename boost::add_const<T>::type, T>::type CT;

public:

    typedef typename boost::conditional<boost::is_volatile<U>::value, typename boost::add_volatile<CT>::type, CT>::type type;
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_COPY_CV_HPP_INCLUDED