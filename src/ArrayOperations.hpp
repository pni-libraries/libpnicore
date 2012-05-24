/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Header files with template functions for array opterations
 *
 * Created on: 22.05.2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __ARRAYOPERATIONS_HPP__
#define __ARRAYOPERATIONS_HPP__

#include "Array.hpp"

namespace pni{
namespace utils{

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes
\brief compute the sum of all element in the array

Sum over all the elements in an Array type. The return type is choosen in a way
that no overflow can occur. This is necessary in particular for very small types
like 8Bit integers.
\param a array object over which to sum
\return number of type T
*/
template<typename ARRAYT> 
    typename ArrayType<typename ARRAYT::value_type>::Type sum(const ARRAYT &a)
{
    typedef typename ArrayType<typename ARRAYT::value_type>::Type RType;
    RType result(0);

    for(auto v: a) result += v;
    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes
\brief get minimum value of an array type

Returns the minimum value stored in an array type. The result is of the same
type as the array elements. This function does not work for array types with
complex numbers as their elements as there are no order relations defined for
complex numbers.
\param a array type
\return value of type T
*/
template<typename ARRAYT> typename ARRAYT::value_type min(const ARRAYT &a) 
{
    typedef typename ARRAYT::value_type RType;
    RType result(a[0]);

    for(auto v: a)
        if(v<result) result = v;

    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_clases
\brief get maximum value of an array type

Returns the larges value in an array type object. The result is of same type as
the elements in the array type. This function does not work for arrays of
complex numbers as there are no order relations for complex numbers.

\param a array for which to determine the maximum
\return value of type T
*/
template<typename ARRAYT> typename ARRAYT::value_type max(const ARRAYT &a)
{
    typedef typename ARRAYT::value_type RType;

    RType result(a[0]);

    for(auto v: a)
        if(v>result) result = v;

    return result;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief minimum and maximum in the array

Return the minimunm and maximum values appearing in an array type. This function
will not work on arrays with complex elements as there are no order relations
for complex numbers.
\param a array object
\param min minimum value
\param max maximum value
*/
template<typename ARRAYT> void min_max(const ARRAYT &a,
                                       typename ARRAYT::value_type &min,
                                       typename ARRAYT::value_type &max)
{
    min=typename ARRAYT::value_type(a[0]);
    max=typename ARRAYT::value_type(a[0]);
    for(auto v: a)
    {
        if(v<min) min = v;
        if(v>max) max = v;
    }
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief clip the array data

Set values greater or equal maxth to maxth and those smaller or equal minth
to minth. 
\param a array which to clip
\param minth minimum threshold
\param maxth maximum threshold
*/
template<typename ARRAYT> void clip(ARRAYT &a,
                                    typename ARRAYT::value_type minth, 
                                    typename ARRAYT::value_type maxth)
{
    for(typename ARRAYT::value_type &v: a)
    {
        if(v <= minth)
        {
            v = minth;
            continue;
        }

        if(v >= maxth)
        {
            v = maxth;
            continue;
        }
    }
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief clip the array data

Set values greater or equal maxth to maxval and those smaller or equal minth
to minval. 
\param a array which to clip
\param minth minimum threshold
\param maxth maximum threshold
\param minval value to which values small minth will be set
\param maxval value to which values larger maxth will be set
*/
template<typename ARRAYT> void clip(ARRAYT &a,
                                    typename ARRAYT::value_type minth, 
                                    typename ARRAYT::value_type maxth,
                                    typename ARRAYT::value_type minval,
                                    typename ARRAYT::value_type maxval)
{
    for(typename ARRAYT::value_type &v: a)
    {
        if(v <= minth)
        {
            v = minval;
            continue;
        }

        if(v >= maxth)
        {
            v = maxval;
            continue;
        }
    }
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes 
\brief clip minimum values

Set values smaller or equal than threshold to threshold. 
\param a array which to clip
\param threshold threshold value
*/
template<typename ARRAYT>
void min_clip(ARRAYT &a,typename ARRAYT::value_type threshold)
{
    for(typename ARRAYT::value_type &v: a)
        if(v<=threshold) v = threshold;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes 
\brief clip minimum values

Set values smaller or equal than threshold to value. 
\param a array which to clip
\param threshold threshold value
\param value the value to which to set data
*/
template<typename ARRAYT>
void min_clip(ARRAYT &a,typename ARRAYT::value_type threshold,
                        typename ARRAYT::value_type value)
{
    for(typename ARRAYT::value_type &v: a)
        if(v<=threshold) v = value;
}
//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes 
\brief clip maximum values

Set values larger or equal than threshold to threshold.
\param a array to clip
\param threshold threshold value
*/
template<typename ARRAYT> 
void max_clip(ARRAYT &a,typename ARRAYT::value_type threshold)
{
    for(typename ARRAYT::value_type &v: a)
        if(v>=threshold) v = threshold;
}

//-----------------------------------------------------------------------------
/*! 
\ingroup data_classes  
\brief clip maximum values

Set values larger or equal than threshold to valuer.
\param a array to clip
\param threshold threshold value
\param value value to set 
*/
template<typename ARRAYT> 
void max_clip(ARRAYT &a,typename ARRAYT::value_type threshold,
                        typename ARRAYT::value_type value)
{
    for(typename ARRAYT::value_type &v: a)
        if(v>=threshold) v = value;
}
//-----------------------------------------------------------------------------
/*!
\ingroup data_classes
\brief get linear offset of maximum

Return the linear offset of the maximum value in the array.
\param a array object to search for
\return linear offset of maximum value
*/
template<typename ARRAYT> size_t max_offset(const ARRAYT &a)
{
    typedef typename ARRAYT::value_type value_type;
    size_t offset = 0;
    size_t index = 0;
    value_type max_value = value_type(a[0]);

    index = 0;
    for(auto v: a)
    {
        if(v > max_value)
        {
            max_value = v;
            offset  = index;
        }
        index++;
    }
    return offset;
}

//-----------------------------------------------------------------------------
/*!
\ingroup data_classes
\brief get index of maximum

Return the multidimensional index of the maximum value in the array.
\param a array where to search
\return index in a container format requested by the user
*/
template<typename CONT,typename ARRAYT> CONT max_index(const ARRAYT &a)
{
    size_t offset = max_offset(a);
    return a.shape().template index<CONT>(offset);
}

//-----------------------------------------------------------------------------
/*!
\ingroup data_classes
\brief get linear offset of minimum

Return the linear offset of the minimum value in the array.
\param a array object to search for
\return linear offset of minimum value
*/
template<typename ARRAYT> size_t min_offset(const ARRAYT &a)
{
    
    typedef typename ARRAYT::value_type value_type;
    size_t offset = 0;
    size_t index = 0;
    value_type min_value = value_type(a[0]);

    index = 0;
    for(auto v: a)
    {
        if(v < min_value)
        {
            min_value = v;
            offset  = index;
        }
        index++;
    }
    return offset;
}

//-----------------------------------------------------------------------------
/*!
\ingroup data_classes
\brief get index of minimum

Return the multidimensional index of the minimum value in the array.
\param a array where to search
\return index in a container format requested by the user
*/
template<typename CONT,typename ARRAYT> CONT min_index(const ARRAYT &a)
{
    size_t offset = min_offset(a);
    return a.shape().template index<CONT>(offset);
}


//end of namespace
}
}


#endif