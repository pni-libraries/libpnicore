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
 *  Created on: Jul 13, 2012
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include<cppunit/extensions/HelperMacros.h>
#include<boost/current_function.hpp>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

#include <list>

#include "array_selection_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(array_selection_test);

//-----------------------------------------------------------------------------
void array_selection_test::setUp() { }

//-----------------------------------------------------------------------------
void array_selection_test::tearDown() { }

//-----------------------------------------------------------------------------
void array_selection_test::test_construction()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    typedef std::vector<size_t> itype;
    //testing default constructor
    array_selection<itype> sel1;
    CPPUNIT_ASSERT(sel1.rank() == 0);
    CPPUNIT_ASSERT(sel1.shape<shape_t>() == shape_t());
    CPPUNIT_ASSERT(sel1.size() == 0);
    auto sel1_shape = sel1.shape<shape_t>();

    //testing standard constructor
    itype shape({1,100,100}); itype offset({0,0,0}); itype stride({1,1,1});
    array_selection<itype> sel2(shape,offset,stride);
    CPPUNIT_ASSERT(sel2.rank() == 2);
    CPPUNIT_ASSERT(sel2.size() == 100*100);
    itype s{100,100};
    auto sel2_shape = sel2.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sel2_shape.begin()));

    //check full parameters
    CPPUNIT_ASSERT(std::equal(sel2.full_shape().begin(),
                              sel2.full_shape().end(),
                              shape.begin()));
    CPPUNIT_ASSERT(std::equal(sel2.offset().begin(),
                              sel2.offset().end(),
                              offset.begin()));
    CPPUNIT_ASSERT(std::equal(sel2.stride().begin(),
                              sel2.stride().end(),
                              stride.begin()));
    typedef std::list<size_t> ltype;
    auto lshape = sel2.full_shape<ltype>();
    auto loffset = sel2.offset<ltype>();
    auto lstride = sel2.stride<ltype>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),lshape.begin()));
    CPPUNIT_ASSERT(std::equal(offset.begin(),offset.end(),loffset.begin()));
    CPPUNIT_ASSERT(std::equal(stride.begin(),stride.end(),lstride.begin()));

    //! copy constructor
    array_selection<itype> sel3(sel2);
    CPPUNIT_ASSERT(sel3.rank() == sel2.rank());
    CPPUNIT_ASSERT(sel3.size() == sel2.size());
    s = sel3.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sel2_shape.begin()));

    //! move construction
    array_selection<itype> sel4(std::move(sel3));
    CPPUNIT_ASSERT(sel4.rank() == sel2.rank());
    CPPUNIT_ASSERT(sel4.size() == sel2.size());
    s = sel4.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sel2_shape.begin()));

    CPPUNIT_ASSERT(sel3.size() == 0);
    CPPUNIT_ASSERT(sel3.rank() == 0);
    CPPUNIT_ASSERT(sel3.shape<itype>() == itype());

}

//------------------------------------------------------------------------------
void array_selection_test::test_create()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    typedef std::vector<size_t> index_type;
    
    std::vector<slice> slices{slice(0,10),slice(1,30,2),slice(2)};
    array_selection<index_type> s = array_selection<index_type>::create(slices);

    CPPUNIT_ASSERT(s.size() == 10*15);
    CPPUNIT_ASSERT(s.rank() == 2);
    itype ref_shape{10,15};
    auto shape = s.shape<itype>();
    CPPUNIT_ASSERT(std::equal(shape.begin(),shape.end(),ref_shape.begin()));

}

//-----------------------------------------------------------------------------
void array_selection_test::test_assignment()
{
    typedef std::vector<size_t> index_type;

    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    array_selection<index_type> sel(itype({100,1,200}),itype({1,1,1}),itype({1,1,2}));
    CPPUNIT_ASSERT(sel.rank() == 2);
    itype s{100,200};
    auto sel_shape = sel.shape<itype>();

    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sel_shape.begin()));
    CPPUNIT_ASSERT(sel.size() == 100*200);

    //------------------------test copy assignment------------------------------
    array_selection<index_type> s1;

    s1 = sel;
    CPPUNIT_ASSERT(s1.rank() == sel.rank());
    CPPUNIT_ASSERT(s1.size() == sel.size());
    auto s1_shape = s1.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s1_shape.begin(),s1_shape.end(),
                              sel_shape.begin()));

    //-----------------test move assignment------------------------------------
    array_selection<index_type> s2;
    s2 = std::move(s1);
    CPPUNIT_ASSERT(s2.rank() == sel.rank());
    CPPUNIT_ASSERT(s2.size() == sel.size());
    auto s2_shape  = s2.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s2_shape.begin(),s2_shape.end(),
                              sel_shape.begin()));

    CPPUNIT_ASSERT(s1.size() == 0);
    CPPUNIT_ASSERT(s1.rank() == 0);
    CPPUNIT_ASSERT(s1.shape<itype>() == itype());

}

//-----------------------------------------------------------------------------
void array_selection_test::test_index()
{
    typedef std::vector<size_t> index_type;

    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    array_selection<index_type> sel(itype({10,20}),itype({1,2}),itype({3,2}));
    itype s{10,20};
    auto sshape = sel.shape<itype>();
    CPPUNIT_ASSERT(std::equal(s.begin(),s.end(),sshape.begin()));
    CPPUNIT_ASSERT(sel.rank()==2);
    CPPUNIT_ASSERT(sel.size() == 10*20);
        
    itype i(sel.rank());
    sel.index(itype({1,3}),i);
    itype r{4,8};
    CPPUNIT_ASSERT(std::equal(r.begin(),r.end(),i.begin()));

    array_selection<index_type> sel2(itype({10,1,20}),itype({1,1,2}),itype({3,1,2}));
    i = itype(3);
    sel2.index(itype({1,3}),i);
    r = itype{4,1,8};
    CPPUNIT_ASSERT(std::equal(r.begin(),r.end(),i.begin()));
}

