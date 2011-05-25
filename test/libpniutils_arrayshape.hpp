//testing class for ArrayShape objects

#ifndef __LIBPNIUTILS_ARRAYSHAPE_HPP__
#define __LIBPNIUTILS_ARRAYSHAPE_HPP__

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>
#include "arrayshape.hpp"

class ArrayShapeTest: public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(ArrayShapeTest);
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testComparison);
	CPPUNIT_TEST_SUITE_END();
private:
	unsigned int *_s1;
	unsigned int _r1, _r2;
	unsigned int *_s2;
	pni::utils::ArrayShape _sh1, _sh2;
public:
	void setUp();
	void tearDown();

	void testConstruction();
	void testComparison();
	void testOffset();

};

#endif
