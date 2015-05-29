#ifndef BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED
#define BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED

//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{

template<class T> struct remove_cv_ref: public boost::remove_cv< typename boost::remove_reference<T>::type >
{
};

} // namespace boost

#endif // #ifndef BOOST_TYPE_TRAITS_DETAIL_REMOVE_CV_REF_HPP_INCLUDED
