//implementation of the unit tests for arrays

#include<cppunit/extensions/HelperMacros.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "Array.hpp"
#include "Buffer.hpp"
#include "Shape.hpp"
#include "ArrayViewTest.hpp"


CPPUNIT_TEST_SUITE_REGISTRATION(ArrayViewTest);

using namespace pni::utils;

void ArrayViewTest::setUp()
{
}

void ArrayViewTest::tearDown()
{
}

void ArrayViewTest::testConstruction()
{
   Shape s{5,10};
   Float32Array a(s);

   Shape vs{1,10};
   ArrayView<Float32,Float32Array> view(a,vs,{0,0},{1,1});

   CPPUNIT_ASSERT(view.shape().rank() == 1);
}

void ArrayViewTest::test_dataaccess()
{
    std::cout<<"void ArrayViewTest::test_dataaccess()......................";
    std::cout<<std::endl;
    Shape s{5,10};
    Float32Array a(s);
    a = 1.5;

    Shape vs{1,5};
    ArrayView<Float32,Float32Array> view(a,vs,{0,2},{1,1});
    for(size_t i=0;i<vs[1];i++)
        CPPUNIT_ASSERT_NO_THROW(view({i}) = Float32(i));

    for(size_t j=0;j<s[0];j++)
    {
        for(size_t i=0;i<s[1];i++) std::cout<<a({j,i})<<" ";
        std::cout<<std::endl;
    }

    for(size_t i=0;i<10;i++)
    {
        if((i<2)||(i>6)) CPPUNIT_ASSERT_DOUBLES_EQUAL(a({0,i}),1.5,1.e-8);
        else 
            CPPUNIT_ASSERT_DOUBLES_EQUAL(a({0,i}),Float32(i-2),1.e-8);
    }

   
}
