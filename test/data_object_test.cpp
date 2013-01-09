/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Jan 9, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <pni/core/Array.hpp>
#include <pni/core/Scalar.hpp>
#include "data_object_test.hpp"
typedef SArray<UInt32,4,5> sarray_t;
typedef NumArray<DArray<Float64> > narray_t;
typedef Scalar<Int64> scalar_t;

CPPUNIT_TEST_SUITE_REGISTRATION(data_object_test<DArray<Float32> >);
CPPUNIT_TEST_SUITE_REGISTRATION(data_object_test<sarray_t> );
CPPUNIT_TEST_SUITE_REGISTRATION(data_object_test<narray_t> );
CPPUNIT_TEST_SUITE_REGISTRATION(data_object_test<scalar_t>);
