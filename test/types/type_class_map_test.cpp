//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Sep 27, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/types/type_class_map.hpp>
#include <iostream>

using namespace pni::core;

namespace std
{
    ostream& operator<<(ostream &stream,const pni::core::type_class_t &tcid)
    {
        using namespace pni::core;
        switch(tcid)
        {
            case type_class_t::NONE: return stream<<"NONE";
            case type_class_t::INTEGER: return stream<<"INTEGER";
            case type_class_t::FLOAT: return stream<<"FLOAT";
            case type_class_t::BINARY: return stream<<"BINARY";
            case type_class_t::BOOL:   return stream<<"BOOL";
            case type_class_t::COMPLEX: return stream<<"COMPLEX";
            case type_class_t::STRING:  return stream<<"STRING";
            default:
                return stream;
        }
    }
}

BOOST_AUTO_TEST_SUITE(type_class_map_test)

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_integer)
    {
        BOOST_CHECK(type_class_map<uint8>::type_class  == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<int8>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<uint16>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<int16>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<uint32>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<int32>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<uint64>::type_class == type_class_t::INTEGER);
        BOOST_CHECK(type_class_map<int64>::type_class == type_class_t::INTEGER);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_float)
    {
        BOOST_CHECK(type_class_map<float32>::type_class == type_class_t::FLOAT);
        BOOST_CHECK(type_class_map<float64>::type_class == type_class_t::FLOAT);
        BOOST_CHECK(type_class_map<float128>::type_class == type_class_t::FLOAT);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_complex)
    {
        BOOST_CHECK(type_class_map<complex32>::type_class == type_class_t::COMPLEX);
        BOOST_CHECK(type_class_map<complex64>::type_class == type_class_t::COMPLEX);
        BOOST_CHECK(type_class_map<complex128>::type_class == type_class_t::COMPLEX);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE(test_type_class_map_others)
    {
        BOOST_CHECK(type_class_map<string>::type_class == type_class_t::STRING);
        BOOST_CHECK(type_class_map<binary>::type_class == type_class_t::BINARY);
        BOOST_CHECK(type_class_map<bool_t>::type_class == type_class_t::BOOL);

        BOOST_CHECK(type_class_map<none>::type_class == type_class_t::NONE);
    }

BOOST_AUTO_TEST_SUITE_END()