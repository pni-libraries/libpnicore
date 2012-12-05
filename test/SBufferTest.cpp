/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jul 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "SBufferTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<UInt8>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Int8>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<UInt16>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Int16>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<UInt32>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Int32>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<UInt64>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Int64>);

CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Float32>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Float64>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Float128>);

CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Complex32>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Complex64>);
CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Complex128>);

CPPUNIT_TEST_SUITE_REGISTRATION(SBufferTest<Binary>);
