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
//  Created on: Oct 22, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <iostream>
#include <pni/core/types.hpp>
#include "number_ranges.hpp"

using namespace pni::core;

template<typename T> void show_range(const T &r,char op)
{
    std::cout<<"["<<r.lhs_min()<<":"<<r.lhs_max()<<"]"<<op;
    std::cout<<"["<<r.rhs_min()<<":"<<r.rhs_max()<<"]"<<std::endl;
}

template<typename T> void show_ranges()
{
    type_id_t tid = type_id_map<T>::type_id;
    string tname = str_from_type_id(tid);

    std::cout<<tname<<"\t";
    show_range(add_ranges<T>(),'+');
    std::cout<<tname<<"\t";
    show_range(div_ranges<T>(),'/');
    std::cout<<tname<<"\t";
    show_range(mult_ranges<T>(),'*');
    std::cout<<std::endl;
}

int main(int,char **)
{
    show_ranges<uint16>();
    show_ranges<uint32>();
    show_ranges<uint64>();

    show_ranges<int16>();
    show_ranges<int32>();
    show_ranges<int64>();

    show_ranges<float32>();
    show_ranges<float64>();
    show_ranges<float128>();

    show_ranges<complex32>();
    show_ranges<complex64>();
    show_ranges<complex128>();

    return 0;
}
