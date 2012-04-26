/*
 * Declaration of class CBFReader
 *
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
 * Definition of class TIFFIFDEntry
 *
 * Created on: Apr 24, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#ifndef __TIFFIFDENTRY_HPP__
#define __TIFFIFDENTRY_HPP__


#include <iostream>
#include <fstream>
#include <map>

#include "../../Types.hpp"
#include "Rational.hpp"
#include "IFDEntryReader.hpp"

using namespace pni::utils;

namespace pni{
namespace io{
namespace tiff{
    
    enum class IFDEntryTypeID { BYTE, ASCII,SHORT,LONG,RATIONAL,SBYTE,UNDEFINED,
                                  SSHORT,SLONG,SRATIONAL,FLOAT,DOUBLE};

    class IFDEntry
    {
        private:
            UInt16 _tag;            //!< ID of the entry
            IFDEntryTypeID _tid;   //!< type id of the entry
            size_t _size;          //!< number of elements of the entry
            std::streampos _data;  //!< marks data position

            //===============private methods==============================
            template<typename T> void _read_entry_data(std::vector<T>
                    &r,std::ifstream &stream);
            void _read_entry_data(std::vector<String> &r,std::ifstream &stream);
            
        public:
            //=============constructors and destructor====================
            //! default constructor
            IFDEntry();

            //! copy constructor
            IFDEntry(const IFDEntry &e);

            //! move constructor
            IFDEntry(IFDEntry &&e);

            /*! \brief standard constructor

            Standard constructor to create a IFDEntry.
            \param tag TIFF tag of the entry
            \param tid type ID of the entry
            \param size number of elements stored in this entry
            \param data starting position of data in the stream
            */
            IFDEntry(UInt16 tag,IFDEntryTypeID tid,size_t size,std::streampos
                    data);

            //! destructor
            ~IFDEntry();

            //=====================assignment operators====================
            //! copy assignment operator
            IFDEntry &operator=(const IFDEntry &e);

            //! move assignment operator
            IFDEntry &operator=(IFDEntry &&e);

            //===============static methods================================
            static IFDEntry create_from_stream(std::ifstream &stream);

            //==================class methods==============================
            /*! \brief number of elements

            Returns the number of elements that make up the entry.
            \return number of elements
            */
            size_t size() const;

            String name() const;

            TypeID type_id() const;

            template<typename T> std::vector<T> value(std::ifstream &stream);
            //template<> std::vector<String> value<String>(std::ifstream &stream);
            //std::vector<String> value(std::ifstream &stream);

            friend std::ostream &operator<<(std::ostream &o,const IFDEntry &e);

    };


    //==============implementation of public template methods==================
    template<typename T> std::vector<T> IFDEntry::value(std::ifstream &stream)
    {
        EXCEPTION_SETUP("template<typename T> std::vector<T> IFDEntry::"
                        "value(std::ifstream &stream)");

        //create a vector of appropriate length
        std::vector<T> result(this->size());
        //save the original stream position
        std::streampos orig_stream_pos = stream.tellg();

        //set the stream to the begining of the data section
        stream.seekg(this->_data,std::ios::beg);

        //here comes the tricky part. Though the user defines the type T he
        //wants to have the IFD entry not all entry types can be converted to T
        //without loss of information. Thus wee need a selection function that
        //picks for each T all acceptable types and throws an exception if the
        //entry is of an incompatible type. 
        //
        //This operation is carried out by the next function which cann choose
        //the proper version by argument type deduction.
        try{
            this->_read_entry_data(result,stream);
        }
        catch(TypeError &e)
        {
            //reset the stream to its original position
            stream.seekg(orig_stream_pos,std::ios::beg);
            throw e;
        }
            
       
        //reset stream to its original position
        stream.seekg(orig_stream_pos,std::ios::beg);

        return result;
    }

    template<typename T> void IFDEntry::_read_entry_data(std::vector<T> &r,std::ifstream
            &stream)
    {
        EXCEPTION_SETUP("template<typename T> void IFDEntry::_read_entry_data"
                "(std::vector<T> &r,std::ifstream &stream)");

        if(this->_tid == IFDEntryTypeID::BYTE) 
            IFDEntryReader<T,UInt8>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::SHORT)
            IFDEntryReader<T,UInt16>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::LONG)
            IFDEntryReader<T,UInt32>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::RATIONAL)
            IFDEntryReader<T,Rational<UInt16> >::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::SBYTE)
            IFDEntryReader<T,Int8>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::SSHORT)
            IFDEntryReader<T,Int16>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::SLONG)
            IFDEntryReader<T,Int32>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::SRATIONAL)
            IFDEntryReader<T,Rational<Int32> >::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::FLOAT)
            IFDEntryReader<T,Float32>::read(r,stream);
        else if(this->_tid == IFDEntryTypeID::DOUBLE)
            IFDEntryReader<T,Float64>::read(r,stream);
        else
        {
            //reset stream position
            EXCEPTION_INIT(TypeError,"IFD entry ["+this->name()+
                    "] contains unknown data!");
            EXCEPTION_THROW();
        }
    }


//end of namespace
}
}
}


#endif