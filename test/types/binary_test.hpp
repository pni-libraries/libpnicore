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
// ============================================================================
//
//  Created on: Feb 08, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>


using namespace pni::core;

class binary_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(binary_test);
    CPPUNIT_TEST(test_construction);
    CPPUNIT_TEST(test_comparison);
    CPPUNIT_TEST(test_assignment);
    CPPUNIT_TEST(test_compatability);
    CPPUNIT_TEST(test_io_operator);
    CPPUNIT_TEST(test_io);
	CPPUNIT_TEST_SUITE_END();
public:
    typedef binary_t<uint8> binary_type;
	void setUp();
	void tearDown();
    void test_construction();
    void test_comparison();
    void test_assignment();
    void test_compatability();
    void test_io_operator();
    void test_io();

};
