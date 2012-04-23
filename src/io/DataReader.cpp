/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniutils.
 *
 * libpniutils is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniutils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniutils.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * DataReader class implementation
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include "DataReader.hpp"
#include "../Exceptions.hpp"


namespace pni{
    namespace utils{
        //===========implementation of private methods=========================
        //default implementation
        void DataReader::_open_stream()
        {
            EXCEPTION_SETUP("void DataReader::_open_stream()");
            try{
                _istream.open(filename());
            }catch(...){
                EXCEPTION_INIT(FileError,"Error opening file ["+filename()+"]!");
                EXCEPTION_THROW();
            }
        }
   
        //====================Implementation of constructors===================
        //implementation of the default constructor
        DataReader::DataReader() {}

        //implementation of the standard constructor
        DataReader::DataReader(const String &fname):
            _fname(fname)
        { }

        //implementation of the move constructor
        DataReader::DataReader(DataReader &&r):
            _fname(std::move(r._fname))
        {}

        //implementation of the destructor
        DataReader::~DataReader() {}

        //=============implementation of assignment operators==================
        DataReader &DataReader::operator=(DataReader &&r)
        {
            if(this == &r) return *this;

            _fname = std::move(r._fname);

            return *this;
        }

        //============implementation of utilty methods=========================
        String DataReader::filename() const
        {
            return _fname;
        }

        //---------------------------------------------------------------------
        void DataReader::filename(const String &fname)
        {
            _fname = fname;
        }
        
        //----------------------------------------------------------------------
        void DataReader::close()
        {
            _istream.close();
        }

    //end of namespace
    }
}
