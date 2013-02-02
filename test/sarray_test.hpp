/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *  Created on: Jul 19, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <boost/current_function.hpp>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <pni/core/sarray.hpp>

#include "data_generator.hpp"
#include "uniform_distribution.hpp"
#include "EqualityCheck.hpp"

using namespace pni::core;

template<typename T> class sarray_test : public CppUnit::TestFixture
{
        CPPUNIT_TEST_SUITE(sarray_test<T>);
        CPPUNIT_TEST(test_construction);
        CPPUNIT_TEST(test_linear_access);
        CPPUNIT_TEST(test_iterators);
        CPPUNIT_TEST(test_multiindex_access);
        CPPUNIT_TEST(test_multiindex_access_const);
        CPPUNIT_TEST(test_typeinfo);
        CPPUNIT_TEST(test_view);
        CPPUNIT_TEST_SUITE_END();
    public:
        void setUp();
        void tearDown();
        void test_construction();
        void test_linear_access();
        void test_iterators();
        void test_multiindex_access();
        void test_multiindex_access_const();
        void test_typeinfo();
        void test_stl();
        void test_view();
};

//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::setUp(){ }

//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::tearDown(){ }

//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    //testing the default constructor
    sarray<T,2,3> a1;
    CPPUNIT_ASSERT(a1.rank() == 2);
    CPPUNIT_ASSERT(a1.size() == 6);

    //testing initializer list constructor
    uniform_distribution<T> dist;
    T v1 = dist(), v2=dist(),v3=dist(),v4=dist(),v5=dist(),v6=dist();
    sarray<T,2,3> a2{v1,v2,v3,v4,v5,v6};
    CPPUNIT_ASSERT(a2.rank() == 2);
    CPPUNIT_ASSERT(a2.size() == 6);

    //testing copy constructor
    sarray<T,2,3> a3(a2);
    CPPUNIT_ASSERT(a3.rank() == a2.rank());
    CPPUNIT_ASSERT(a3.size() == a2.size());
}

//------------------------------------------------------------------------------ 
template<typename T> void sarray_test<T>::test_linear_access()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    sarray<T,2,3> a1;
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
   
    //--------------------check operators without index checking----------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1[i] = data[i];

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(data[i],a1[i]);

    //-------------------check with index checking-----------------------------
	//access via [] operator
	for(size_t i=0;i<a1.size();i++) 
        a1.at(i) = data[i];

	//check if data values have been transfered correctly
	for(size_t i=0;i<a1.size();i++) 
        check_equality(data[i],a1.at(i));

    CPPUNIT_ASSERT_THROW(a1.at(a1.size()+10),index_error);

}

//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_iterators()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    sarray<T,2,3> a1;

    //--------------------check standard iterator----------------
	//access via [] operator
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //----------------------testing write data---------------------------------
    auto diter = data.begin();
    for(auto iter = a1.begin(); iter!=a1.end();iter++)
        *iter = *diter++;
   
    //-----------------------test reading data---------------------------------
    diter = data.begin();
    for(auto iter=a1.begin();iter!=a1.end();iter++)
        check_equality(*iter,*diter++);
}

//-----------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_multiindex_access()
{   
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    sarray<T,2,3> a1;
    std::vector<T> data(a1.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            a1(i,j) = data[i*3+j];

    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            check_equality(a1(i,j),data[i*3+j]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            a1(index) = data[i*3+j];
        }
    }

    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[i*3+j]);
        }
    }
}

//-----------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_multiindex_access_const()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
   
    std::vector<T> data(6);
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());
    const sarray<T,2,3> a1(data);

    //----------------use variadic tempaltes to access data--------------
    for(size_t i=0;i<2;i++)
        for(size_t j=0;j<3;j++)
            check_equality(a1(i,j),data[i*3+j]);

    //----------using a container to hold the index----------------------
    for(size_t i=0;i<2;i++)
    {
        for(size_t j=0;j<3;j++)
        {
            std::vector<size_t> index{i,j};
            check_equality(a1(index),data[i*3+j]);
        }
    }
}


//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_view()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    sarray<T,10,3> v;
    std::vector<T> data(v.size());
    data_generator::fill(data.begin(),data.end(),uniform_distribution<T>());

    for(size_t i=0;i<10;i++)
    {
        auto view = v(std::vector<slice>{slice(i),slice(0,3,1)});
        std::copy(data.begin()+i*3,data.begin()+(i+1)*3,view.begin());
    }
    
    for(size_t i=0;i<10;i++)
    {
        //for reading we use a different construction here
        auto view = v(i,slice(0,3,1));
        CPPUNIT_ASSERT(std::equal(view.begin(),view.end(),data.begin()+i*3));
    }

    //check construction of a static array from a view
    auto view = v(2,slice(0,3));
    sarray<T,3> c(view);

    CPPUNIT_ASSERT(std::equal(c.begin(),c.end(),data.begin()+2*3));

}
//------------------------------------------------------------------------------
template<typename T> void sarray_test<T>::test_typeinfo()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    type_id_t id1 = sarray<T,2,3>::type_id;
    type_id_t id2 = type_id_map<T>::type_id;
    CPPUNIT_ASSERT(id1 == id2);
}