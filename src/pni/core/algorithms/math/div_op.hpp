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
// Created on: Jul 25,2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/algorithms/math/op_traits.hpp>
#include <pni/core/utilities/container_iterator.hpp>

namespace pni{
namespace core{
    
    template<typename ATYPE> class array_view;

    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief Division expression template
    //! 
    //! \tparam OP1T type of the left operand
    //! \tparam OP2T type of the right operand
    //!
    template<
             typename OP1T,
             typename OP2T
            > 
    class div_op
    {
        private:
            //! reference to the left operand
            typename op_trait<OP1T>::ref_type _op1;
            //! reference to the right operand
            typename op_trait<OP2T>::ref_type _op2;
        public:
            //--------------------public types---------------------------------
            //! result type of the operation
            typedef typename OP1T::value_type value_type;
            //! type of the expression template
            typedef div_op<OP1T,OP2T> array_type;
            //! storage type
            typedef void storage_type;
            //! non-const iterator - just for interface
            typedef container_iterator<array_type> iterator;
            //! const iterator type
            typedef container_iterator<const array_type> const_iterator;
            //! reverse iterator type
            typedef container_iterator<array_type> reverse_iterator;
            //! const reverse iterator type
            typedef container_iterator<const array_type> const_reverse_iterator;
            //! view type
            typedef array_view<array_type> view_type;
            //! index map type
            typedef typename array_trait<OP1T,OP2T>::map_type map_type;
            //! inplace arithmetic type
            typedef typename array_trait<OP1T,OP2T>::inplace_arithmetic
                inplace_arithmetic;

            //===================constructors==================================
            //!
            //! \brief constructor
            //!
            //! \param o1 left operand
            //! \param o2 right operand
            //!
            div_op(const OP1T &o1,const OP2T &o2):
                _op1(o1),
                _op2(o2)
            {}

            //====================public methods===============================
            //!
            //! \brief return result at i
            //!
            //! Return the result of a[i]/b[i]. 
            //!
            //! \param i index at which to perform operation
            //! \return result of the operation
            //!
            value_type operator[](size_t i) const
            {
                return this->_op1[i]/this->_op2[i];
            }

            //-----------------------------------------------------------------
            //!
            //! \brief return value at i
            //!
            //! Return the result of the operation for index i. 
            //! 
            //! \throws index_error if i exceeds size
            //! \param i index at which to perform the operation
            //! \return result of the operation
            //!
            value_type at(size_t i) const 
            { 
                if(i>=size())
                    throw index_error(EXCEPTION_RECORD,"index exceeds size");

                return (*this)[i]; 
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get size
            //!
            //! Return the maximum of a.size() and b.size(). 
            //!
            //! \return size
            //!
            size_t size() const
            {
                return _op1.size() > _op2.size() ?  _op1.size() : _op2.size();
            }

            //=====================iterators===================================
            //! get const iterator to first element
            const_iterator begin() const
            {
                return const_iterator(this,0);
            }

            //-----------------------------------------------------------------
            //! get const iterator to last+1 element
            const_iterator end() const
            {
                return const_iterator(this,this->size());
            }
    };

//end of namespace
}
}
