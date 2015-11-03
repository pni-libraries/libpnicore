//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jan 7, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing the value type earsure
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
#include <boost/test/floating_point_comparison.hpp>
#include <pni/core/type_erasures.hpp>

#include "../../data_generator.hpp"
#include "types.hpp"
#include "fixture.hpp"

using namespace pni::core;


BOOST_AUTO_TEST_SUITE(value_construction_test)

    BOOST_AUTO_TEST_CASE(test_default_construction)
    {
        value v;
        BOOST_CHECK_EQUAL(v.type_id(),type_id_t::NONE);
    }
    
    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_make_construction,T,all_types)
    {
        value v = make_value<T>();
        BOOST_CHECK(v.type_id()==type_id_map<T>::type_id);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_from_value,T,all_types)
    {
        fixture<T> f;

        value v(f.value_1);
        BOOST_CHECK(v.type_id() == type_id_map<T>::type_id);
        BOOST_CHECK_EQUAL(v.as<T>(),f.value_1); 
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_copy_construction,T,all_types)
    {
        fixture<T> f;    
        value v1(f.value_1);
        value v2(v1);

        BOOST_CHECK_EQUAL(v1.type_id(),v2.type_id());
        BOOST_CHECK_EQUAL(v1.as<T>(),v2.as<T>());
        BOOST_CHECK_EQUAL(v2.as<T>(),f.value_1);
    }

    //========================================================================
    BOOST_AUTO_TEST_CASE_TEMPLATE(test_move_construction,T,all_types)
    {
        fixture<T> f;
        value v1(f.value_1);
        value v2 = std::move(v1);

        BOOST_CHECK_EQUAL(v1.type_id(),type_id_t::NONE);
        BOOST_CHECK(v2.type_id()==type_id_map<T>::type_id);
        BOOST_CHECK_EQUAL(f.value_1,v2.as<T>());
    }

BOOST_AUTO_TEST_SUITE_END()


