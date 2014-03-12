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
// ===========================================================================
//
// Created on: May 16, 2011
//     Author: Eugen Wintersberger
//
//
#pragma once

#include <complex>
#include <string>
#include <cstdint>
#include <vector>

#include "binary.hpp"

namespace pni{
namespace core{

    /*! \addtogroup type_classes
      @{
     */

    //---------------------integer types---------------------------------------
    typedef int8_t   int8;   //!< 8Bit signed integer type
    typedef uint8_t  uint8;  //!< 8Bit unsigned integer type
    typedef int16_t  int16;  //!< 16Bit signed integer type
    typedef uint16_t uint16; //!< 16Bit unsigned integer type
    typedef int32_t  int32;  //!< 32Bit signed integer type
    typedef uint32_t uint32; //!< 32Bit unsigned integer type
    typedef int64_t  int64;  //!< 64Bit signed integer type
    typedef uint64_t uint64; //!< 64Bit unsigned integer type

    //-------------------floating point types----------------------------------
    typedef double      float64;   //!< 64Bit IEEE floating point type
    typedef float       float32;   //!< 32Bit IEEE floating point type
    typedef long double float128;  //!< 128Bit IEEE floating point type

    //-----------------------complex types--------------------------------------
    //! 32Bit complex floating point type
    typedef std::complex<float>       complex32; 
    //! 64Bit complex floating point type 
    typedef std::complex<double>      complex64; 
    //! 128Bit complex floating point type
    typedef std::complex<long double> complex128; 

    //-----------------------utility types-------------------------------------
    typedef std::string     string; //!< String type
    typedef binary_t<uint8> binary; //!< data type for binary data
    typedef bool            Bool;   //!< data type for boolean expressions
    /*! @} */


    //! 
    //! \ingroup type_classes
    //! \brief type codes for PNI data types
    //! 
    //! Typed enumeration with type IDs. 
    //!
    enum class type_id_t {NONE,       //!< no data type
                          INT8,       //!< signed 8Bit integer
                          UINT8,      //!< unsigned 8Bit integer
                          INT16,      //!< signed 16Bit integer
                          UINT16,     //!< unsigned 16Bit integer
                          INT32,      //!< signed 32Bit integer
                          UINT32,     //!< unsigned 32Bit integer
                          INT64,      //!< signed 64Bit integer
                          UINT64,     //!< unsigned 64Bit integer
                          FLOAT32,    //!< 32Bit IEEE floating point
                          FLOAT64,    //!< 64Bit IEEE floating point
                          FLOAT128,   //!< 128Bit IEEE floating point
                          COMPLEX32,  //!< 32Bit IEEE floating point complex
                          COMPLEX64,  //!< 64Bit IEEE floating point complex
                          COMPLEX128, //!< 128Bit IEEE floating point complex
                          STRING,     //!< String type
                          BINARY,     //!< binary data
                          BOOL        //!< boolean data
                      };

    //! 
    //! \ingroup type_classes
    //! \brief output operator for type_id_t
    //! 
    //! Adds a string representation of a TypeID to the output stream.
    //! 
    //! \param o reference to output stream
    //! \param tid reference to the TypID 
    //! \return reference to output stream
    //!
    std::ostream &operator<<(std::ostream &o,const type_id_t &tid);


    //! classes of data types provided by the PNI utility library
    enum class type_class_t {NONE,       //!< unspecified type
                             INTEGER,    //!< integer type
                             FLOAT,      //!< floating point type
                             BINARY,     //!< binary data type
                             BOOL,       //!< boolean data type
                             COMPLEX,    //!< complex data type
                             STRING      //!< class for string types
                            };




//if the compiler does not provide comparison operators for typed enumerations
//we have to do this by ourselves
#ifdef ENUMBUG
    //!
    //! \ingroup type_classes_internal
    //! \brief < operator for type_id_t
    //!
    //! gcc 4.4 does not implement the < operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<(type_id_t a,type_id_t b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief > operator for type_id_t
    //!
    //! gcc 4.4 does not implement the > operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>(type_id_t a,type_id_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief <= operator for type_id_t
    //!
    //! gcc 4.4 does not implement the <= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<=(type_id_t a,type_id_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief >= operator for type_id_t
    //!
    //! gcc 4.4 does not implement the >= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>=(type_id_t a,type_id_t b);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief < operator for type_class_t
    //!
    //! gcc 4.4 does not implement the < operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief > operator for type_class_t
    //!
    //! gcc 4.4 does not implement the > operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief <= operator for type_class_t
    //!
    //! gcc 4.4 does not implement the <= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator<=(type_class_t a,type_class_t b);
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_classes_internal
    //! \brief >= operator for type_class_t
    //!
    //! gcc 4.4 does not implement the >= operator for scoped enums. In such 
    //! cases this overloaded version is used. This operator will only be used 
    //! if the code is compiled with \c -DENUMBUG.
    //! 
    bool operator>=(type_class_t a,type_class_t b);
#endif
    
    //! standard type for array shapes
    typedef std::vector<size_t> shape_t;

//end of namespace
}
}