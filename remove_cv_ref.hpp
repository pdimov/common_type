#ifndef BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{

template<class T> struct remove_cv_ref: public boost::remove_cv< typename boost::remove_reference<T>::type >
{
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED
