//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Dec 22, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <pni/core/types/type_conversion.hpp>

using namespace pni::core;


BOOST_AUTO_TEST_SUITE(is_convertible_test)

    //=========================================================================
    void always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::BOOL));
        BOOST_CHECK(!is_convertible(sid,type_id_t::BINARY));
        BOOST_CHECK(!is_convertible(sid,type_id_t::STRING));
    }

    //=========================================================================
    void uint_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::UINT8));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UINT16));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UINT32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::UINT64));
    }

    //=========================================================================
    void int_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::INT8));
        BOOST_CHECK(!is_convertible(sid,type_id_t::INT16));
        BOOST_CHECK(!is_convertible(sid,type_id_t::INT32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::INT64));
    }

    //=========================================================================
    void float_always_fails(type_id_t sid)
    {
        BOOST_CHECK(!is_convertible(sid,type_id_t::FLOAT32));
        BOOST_CHECK(!is_convertible(sid,type_id_t::FLOAT64));
        BOOST_CHECK(!is_convertible(sid,type_id_t::FLOAT128));
    }

    //=========================================================================
    void float_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::FLOAT32));
        BOOST_CHECK(is_convertible(sid,type_id_t::FLOAT64));
        BOOST_CHECK(is_convertible(sid,type_id_t::FLOAT128));
    }

    //=========================================================================
    void complex_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::COMPLEX32));
        BOOST_CHECK(is_convertible(sid,type_id_t::COMPLEX64));
        BOOST_CHECK(is_convertible(sid,type_id_t::COMPLEX128));
    }

    //=========================================================================
    void uint_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::UINT8));
        BOOST_CHECK(is_convertible(sid,type_id_t::UINT16));
        BOOST_CHECK(is_convertible(sid,type_id_t::UINT32));
        BOOST_CHECK(is_convertible(sid,type_id_t::UINT64));
    }

    //=========================================================================
    void int_always_pass(type_id_t sid)
    {
        BOOST_CHECK(is_convertible(sid,type_id_t::INT8));
        BOOST_CHECK(is_convertible(sid,type_id_t::INT16));
        BOOST_CHECK(is_convertible(sid,type_id_t::INT32));
        BOOST_CHECK(is_convertible(sid,type_id_t::INT64));
    }

    //=========================================================================
    BOOST_AUTO_TEST_CASE(test_uint8)
    {
        uint_always_pass(type_id_t::UINT8);
        int_always_pass(type_id_t::UINT8);
        float_always_pass(type_id_t::UINT8);
        complex_always_pass(type_id_t::UINT8);
        always_fails(type_id_t::UINT8);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint16)
    {
        uint_always_pass(type_id_t::UINT16);
        int_always_pass(type_id_t::UINT16);
        float_always_pass(type_id_t::UINT16);
        complex_always_pass(type_id_t::UINT16);
        always_fails(type_id_t::UINT16);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint32)
    {
        uint_always_pass(type_id_t::UINT32);
        int_always_pass(type_id_t::UINT32);
        float_always_pass(type_id_t::UINT32);
        complex_always_pass(type_id_t::UINT32);
        always_fails(type_id_t::UINT32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_uint64)
    {
        uint_always_pass(type_id_t::UINT64);
        int_always_pass(type_id_t::UINT64);
        float_always_pass(type_id_t::UINT64);
        complex_always_pass(type_id_t::UINT64);
        always_fails(type_id_t::UINT64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int8)
    {
        uint_always_pass(type_id_t::INT64);
        int_always_pass(type_id_t::INT64);
        float_always_pass(type_id_t::INT64);
        complex_always_pass(type_id_t::INT64);
        always_fails(type_id_t::INT64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int16)
    {
        uint_always_pass(type_id_t::INT16);
        int_always_pass(type_id_t::INT16);
        float_always_pass(type_id_t::INT16);
        complex_always_pass(type_id_t::INT16);
        always_fails(type_id_t::INT16);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int32)
    {
        uint_always_pass(type_id_t::INT32);
        int_always_pass(type_id_t::INT32);
        float_always_pass(type_id_t::INT32);
        complex_always_pass(type_id_t::INT32);
        always_fails(type_id_t::INT32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_int64)
    {
        uint_always_pass(type_id_t::INT64);
        int_always_pass(type_id_t::INT64);
        float_always_pass(type_id_t::INT64);
        complex_always_pass(type_id_t::INT64);
        always_fails(type_id_t::INT64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float32)
    {
        uint_always_fails(type_id_t::FLOAT32);
        int_always_fails(type_id_t::FLOAT32);
        float_always_pass(type_id_t::FLOAT32);
        complex_always_pass(type_id_t::FLOAT32);
        always_fails(type_id_t::FLOAT32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float64)
    {
        uint_always_fails(type_id_t::FLOAT64);
        int_always_fails(type_id_t::FLOAT64);
        float_always_pass(type_id_t::FLOAT64);
        complex_always_pass(type_id_t::FLOAT64);
        always_fails(type_id_t::FLOAT64);

    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_float128)
    {
        uint_always_fails(type_id_t::FLOAT128);
        int_always_fails(type_id_t::FLOAT128);
        float_always_pass(type_id_t::FLOAT128);
        complex_always_pass(type_id_t::FLOAT128);
        always_fails(type_id_t::FLOAT128);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex32)
    {
        uint_always_fails(type_id_t::COMPLEX32);
        int_always_fails(type_id_t::COMPLEX32);
        float_always_fails(type_id_t::COMPLEX32);

        complex_always_pass(type_id_t::COMPLEX32);
        always_fails(type_id_t::COMPLEX32);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex64)
    {
        uint_always_fails(type_id_t::COMPLEX64);
        int_always_fails(type_id_t::COMPLEX64);
        float_always_fails(type_id_t::COMPLEX64);

        complex_always_pass(type_id_t::COMPLEX64);
        always_fails(type_id_t::COMPLEX64);
    }

    //=============================================================================
    BOOST_AUTO_TEST_CASE(test_complex128)
    {
        uint_always_fails(type_id_t::COMPLEX128);
        int_always_fails(type_id_t::COMPLEX128);
        float_always_fails(type_id_t::COMPLEX128);

        complex_always_pass(type_id_t::COMPLEX128);
        always_fails(type_id_t::COMPLEX128);
    }

BOOST_AUTO_TEST_SUITE_END()
