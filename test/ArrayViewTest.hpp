//Unit test for the array object

#include<cppunit/TestFixture.h>
#include<cppunit/extensions/HelperMacros.h>

#include<vector>
#include <pni/utils/ArrayView.hpp>
#include "RandomDistributions.hpp"

using namespace pni::utils;


class ArrayViewTest : public CppUnit::TestFixture{
        CPPUNIT_TEST_SUITE(ArrayViewTest);
        CPPUNIT_TEST(testConstruction);
        CPPUNIT_TEST(test_dataaccess);
        CPPUNIT_TEST(test_linearaccess);
        CPPUNIT_TEST(test_assignment);
        CPPUNIT_TEST(test_operations);
        CPPUNIT_TEST_SUITE_END();
    private:
        typedef std::vector<size_t> Shape;
        Shape s1,s2;
        size_t r1,r2;
    public:
        void setUp();
        void tearDown();
        void testConstruction();
        void test_dataaccess();
        void test_linearaccess();
        void test_assignment();
        void test_operations();
};
