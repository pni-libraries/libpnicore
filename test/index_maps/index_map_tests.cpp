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
//  Created on: Nov 2, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

extern int cindex_implementation_test_init();


bool init_function()
{
    cindex_implementation_test_init(); 
    return true;
}

int main(int argc,char **argv)
{
    return boost::unit_test::unit_test_main(&init_function,argc,argv);
}
