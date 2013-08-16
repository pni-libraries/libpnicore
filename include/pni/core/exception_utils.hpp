/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpnicore.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * 
 * Exception related utility functions - declarations.
 *
 * Created on: May 23, 2012
 *     Author: Eugen Wintersberger
 *
 */
#pragma once

#include <vector>
#include <iostream>
//#include <typeinfo>
#include <algorithm>

#include "exceptions.hpp"
#include "service.hpp"

namespace pni{
namespace core{

    //=====================Exception related helper functions==================
    /*!
    \ingroup error_classes
    \brief check if two objects have different size
    
    This utilty function can be used to check for the equality of the size of
    two objects. It is typically used to compare the size of a shape and a 
    buffer or any other container object. 
    If the sizes do not match an exception is thrown.
    \throws size_mismatch_error if sizes do not match
    \param a first object
    \param b second object
    \param i exception_record for the location where to perform the check
    performed
    */
    template<typename A,typename B> 
        void check_equal_size(const A &a,const B &b,const exception_record &i)
    {
        if(a.size() != b.size())
        {
            std::stringstream ss;
            ss<<"Size of "<<demangle_cpp_name(typeid(A).name())<<" (";
            ss<<a.size()<<") ";
            ss<<"does not match size of "<<demangle_cpp_name(typeid(B).name())<<" (";
            ss<<b.size()<<")!";
            throw size_mismatch_error(i,string(ss.str()));
        }
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup error_classes
    \brief check index 

    This utilty function can be used to check if an index exeeds a particular
    value.
    \throws index_error if i exceeds imax
    \param index actual index
    \param maxindex maximum value
    \param i exception_record for the location where to perform the check
    performed
    */
    void check_index(size_t index,size_t maxindex,const exception_record &i);


    //-------------------------------------------------------------------------
    /*!
    \ingroup error_classes
    \brief check shape equality

    Checks if two Shape objects are equal and throws an exception if they are
    not.
    \tparam A container type for the first shape
    \tparam B container type for the second shape
    \throws shape_mismatch_error if shapes do not match
    \param a first shape
    \param b second shape
    \param i exception_record for the location where to perform the check
    */
    template<typename A,typename B>
    void check_equal_shape(const A &a,const B &b,const exception_record &i)
    {
        auto sa = a.template shape<std::vector<size_t> >();
        auto sb = b.template shape<std::vector<size_t> >();

        if((sa.size()!=sb.size()) ||
           (!std::equal(sa.begin(),sa.end(),sb.begin())))
        {
            //assemble error string
            std::stringstream ss;
            ss<<"Shapes ( ";
#ifdef NOFOREACH
            for(auto iter = sa.begin();iter!=sa.end();++iter)
            {
                auto v = *iter;
#else
            for(auto v: sa)
            {
#endif
                std::cout<<v<<" ";
            }
            ss<<") and ( ";
#ifdef NOFOREACH
            for(auto iter = sb.begin();iter!=sb.end();++iter)
            {
                auto v = *iter;
#else
            for(auto v: sb)
            {
#endif 
                std::cout<<v<<" ";
            }
            ss<<") do not match";

            //construct exception
            throw shape_mismatch_error(i,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief check allocation state

    Checks the allocation state of an allocateable object. If the object is not
    allocated an exception will be thrown.
    \throws memory_not_allocated_error if object not allocated
    \param o object to check
    \param i exception_record for the location where to perform the check
    */
    template<typename OTYPE> void
        check_allocation_state(const OTYPE &o,const exception_record &i)
    {
        if(!o.size())
        {
            std::stringstream ss;
            ss<<"Instance of "<<demangle_cpp_name(typeid(OTYPE).name());
            ss<<" not allocated!";
            throw memory_not_allocated_error(i,ss.str());
        }
    }

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief check pointer state

    Checks if a pointer is nullptr or not and throws an exception if it is.
    \throws memory_not_allocated_error if pointer is a nullptr
    \param ptr pointer to check
    \param i exception_record for the location where to perform the check
    */
    template<typename T> 
        void check_ptr_state(const T *ptr,const exception_record &i)
    {
        if(!ptr)
        {
            std::stringstream ss;
            ss<<"Pointer is nullptr!";
            throw memory_not_allocated_error(i,ss.str());
        }
    }



//end of namespace
}
}