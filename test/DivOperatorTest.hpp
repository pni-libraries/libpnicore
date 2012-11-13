//test case for the IndexMapBase base class

#ifndef __DIVOPERATORTEST_HPP__
#define __DIVOPERATORTEST_HPP__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <algorithm>

#include <pni/utils/NumArray.hpp>
#include <pni/utils/DArray.hpp>
#include <pni/utils/Scalar.hpp>

#include "EqualityCheck.hpp"

using namespace pni::utils;

/*!
 Do testing only for DArray - all array types provide the same interface and
 thus can be considered as equivalent. However, we have to check ArrayView
 wether or not it works.
 */
template<typename T> class DivOperatorTest: public CppUnit::TestFixture 
{
        CPPUNIT_TEST_SUITE(DivOperatorTest<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_access);
        CPPUNIT_TEST(test_iterator);
        CPPUNIT_TEST(test_operator);
        CPPUNIT_TEST_SUITE_END();
    private:
        //==========private types==============================================
        typedef DArray<T> atype;
        typedef NumArray<atype> na_type;
        typedef Scalar<T> s_type;


        //===================private memebers==================================
        na_type a1;
        na_type a2;
        std::vector<size_t> shape;

    public:
        void setUp();
        void tearDown();
        
        void test_construction();
        void test_access();
        void test_iterator();
        void test_operator();

};

template<typename T> void DivOperatorTest<T>::setUp()
{
    shape = std::vector<size_t>(3);
    shape[0] = 2; shape[1] = 3; shape[2] = 4;
    a1 = na_type(shape);
    a2 = na_type(shape);
    
    std::fill(a1.begin(),a1.end(),T(10));
    std::fill(a2.begin(),a2.end(),T(5));
}

template<typename T> void DivOperatorTest<T>::tearDown()
{
    
}

template<typename T> void DivOperatorTest<T>::test_construction()
{
    Div<na_type,na_type> op(a1,a2);
    CPPUNIT_ASSERT(a1.size() == op.size());
   
    s_type s(10);
    Div<na_type,s_type> op2(a1,s);
    CPPUNIT_ASSERT(op2.size() == a1.size());

    Div<s_type,s_type> op3(s,s);
    CPPUNIT_ASSERT(s.size() == op3.size());

}

template<typename T> void DivOperatorTest<T>::test_access()
{
    Div<na_type,na_type> op1(a1,a2);

    for(size_t i=0;i<op1.size();i++)
        check_equality(op1[i],T(2));

    s_type s(2);
    Div<na_type,s_type> op2(a1,s);

    for(size_t i=0;i<op2.size();i++)
        check_equality(op2[i],T(5));
}

template<typename T> void DivOperatorTest<T>::test_iterator()
{
    Div<na_type,na_type> op1(a1,a2);
#ifdef NOFOREACH
    for(auto iter = op1.begin();iter!=op1.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op1) 
    {
#endif
        check_equality(v,T(2));
    }

    s_type s(2);
    Div<na_type,s_type> op2(a1,s);
#ifdef NOFOREACH
    for(auto iter = op2.begin();iter!=op2.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: op2) 
    {
#endif 
        check_equality(v,T(5));
    }
}

template<typename T> void DivOperatorTest<T>::test_operator()
{
    na_type r = atype(shape);
    r = a1/a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(2));
    }

    r = a1/T(2);
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,T(5));
    }

    r = T(100)/a1;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif
        check_equality(v,T(10));
    }

    //put it all together

    r = T(100)/a1/a2;
#ifdef NOFOREACH
    for(auto iter = r.begin();iter!=r.end();++iter)
    {
        auto v = *iter;
#else
    for(auto v: r) 
    {
#endif 
        check_equality(v,T(2));
    }

}
#endif
