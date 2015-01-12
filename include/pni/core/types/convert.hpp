//
// Declaration of template class TypeInfo
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
// 
// ============================================================================
//
//  Created on: Dec 10, 2011
//      Author: Eugen Wintersberger
//
#pragma once

#include "type_id_map.hpp"
#include <boost/static_assert.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "../error/exceptions.hpp"
#include "../error/exception_utils.hpp"
#include "type_info.hpp"
#include "unchecked_convertible.hpp"
#include "checked_convertible.hpp"
#include "convertible.hpp"
#include "type_conversion.hpp"


namespace pni{
namespace core{

    using namespace boost::numeric;

    //!
    //! \ingroup type_classes_internal
    //! \brief simple numeric converter
    //!
    //! Implements conversion between simple scalar numeric types.
    //! 
    //! \tparam TT target type
    //! \tparam ST source type
    //!
    template<
             typename TT,
             typename ST
            >
    struct converter
    {
        static TT convert(const ST &value)
        {
            return boost::numeric_cast<TT>(value);
        }
    };

    template<typename TT>
    struct converter<TT,TT>
    {
        static TT convert(const TT &value)
        {
            return value;
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief simple to complex conversion
    //!
    //! Implements conversion from a simple scalar type to a complex type. 
    //!
    //! \tparam BT target base type
    //! \tparam ST simple source type
    //!
    template<
             typename BT,
             typename ST
            >
    struct converter<std::complex<BT>,ST>
    {
        static std::complex<BT> convert(const ST &value)
        {
            BT real = boost::numeric_cast<BT>(value);

            return std::complex<BT>(real,0);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief complex to complex conversion
    //!
    //! Implements complex to complex conversion.
    //!
    //! \tparam BTT target base type
    //! \tparam BST source base type
    //! 
    template<
             typename BTT,
             typename BST
            >
    struct converter<std::complex<BTT>,std::complex<BST>>
    {
        static std::complex<BTT> convert(const std::complex<BST> &value)
        {
            BTT real = boost::numeric_cast<BTT>(value.real());
            BTT imag = boost::numeric_cast<BTT>(value.imag());

            return std::complex<BTT>(real,imag);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief simple unchecked strategy
    //! 
    //! This strategy implements a simple unchecked type conversion. 
    //! 
    //! \tparam T target type
    //! \tparam S source type
    //! \tparam unchecked_convertible a flag if true use this strategy
    //!
    template<
             typename T,
             typename S,
             bool unchecked_convertible=true
            > 
    struct conversion_strategy
    {
        static T convert(const S &value)
        {
            return T(value);
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief checked conversion strategy
    //!
    //! This strategy uses the numeric_cast function to implement the 
    //! conversion.
    //!
    //! \tparam T target type
    //! \tparam S source type
    //!
    template<
             typename T,
             typename S
            >
    struct conversion_strategy<T,S,false>
    {
        static T convert(const S &value)
        {
            try
            {
                return converter<T,S>::convert(value);
            }
            catch(const boost::numeric::positive_overflow &error)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(const boost::numeric::negative_overflow &error)
            {
                throw range_error(EXCEPTION_RECORD,
                        "Source value exceeded range of target type!");
            }
            catch(...)
            {
                throw type_error(EXCEPTION_RECORD,
                        "Unknown error during type conversion!");
            }
        }
    
    };

    //-------------------------------------------------------------------------
    //!
    //! ingroup type_classes_internal
    //! \brief type conversion function template
    //! 
    //! This function template finally performs the type conversion. Several
    //! static asserts are performed which ensure the two cases of conversions
    //! will not even compile: conversion from a floating point number of an
    //! integer value and conversion from a complex value to a non-complex 
    //! type.
    //!
    //! \throws range_error if u does not fit in the range covered by T
    //! \throws type_error in case of all other errors
    //! \tparam T target type
    //! \tparam S source type
    //! \param source value of type S
    //! \return value of u converted to T
    //!
    template<
             typename T,
             typename S
            > 
    T convert(const S &source)
    {
        static_assert(convertible<S,T>::value,
                      "Types are in no way convertible!");

        typedef conversion_strategy<T,S,unchecked_convertible<S,T>::value> strategy;
        return strategy::convert(source);

    }

//end of namespace
}
}
