//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Oct 24, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup benchmark_classes
    //! \brief result of a single benchmark
    //!
    //! The benchmark_result class holds all the information that is 
    //! obtained during a single benchmark. 
    //!
    //! For timing the new classes from the chrono namespace are used. 
    //! This should give bettet. 
    //!
    class benchmark_result 
    {
        private:
            //! time required for reading data
            float64 _time;  
            //! unit of time
            string _unit;
        public:
            //====================constructors and destructor===================
            //! default constructor
            benchmark_result():
                _time(0.),
                _unit("")
            {}

            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! \param time the time the function took to run
            //! \param unit the unit used to measure the time
            //!
            benchmark_result(float64 time,const string &unit):
                _time(time),
                _unit(unit)
            {}

            //==================public member functions=========================
            //! get time
            float64 time() const { return _time; }

            //------------------------------------------------------------------
            //! get the unit
            string unit() const { return _unit; }

    };

    //!
    //! \ingroup benchmark_classes
    //! \brief output operator for benchmark result
    //!
    std::ostream &operator<<(std::ostream &o,const benchmark_result &r);

//end of namespace
}
}
