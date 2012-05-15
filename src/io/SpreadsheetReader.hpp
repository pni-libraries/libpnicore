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
 * SpreadsheetReader class definition
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __SPREADSHEETREADER_HPP__
#define __SPREADSHEETREADER_HPP__

#include <vector>
#include "../Types.hpp"
#include "../Exceptions.hpp"
#include "DataReader.hpp"
#include "ColumnInfo.hpp"

namespace pni{
namespace io{

    /*! \ingroup io_classes
    \brief base class for spreadsheet reader

    This class is the basement for all readers dealing with spreadsheet like
    data files. Most of the ASCII formats written following this storage
    convention.
    */
    class SpreadsheetReader:public DataReader
    {
        private:
            std::vector<ColumnInfo> _columns_info; //!< column information
            size_t _nrec;    //!< number of records in the sheet

        protected:
            //============constructors and destructor==========================
            //! default constructor
            SpreadsheetReader();

            //! copy constructor is deleted
            SpreadsheetReader(const SpreadsheetReader &) = delete;

            //! move constructor
            SpreadsheetReader(SpreadsheetReader &&o);

            //! standard constructor
            SpreadsheetReader(const String &n);

            //==================protected member functions======================
            /*! \brief append a column

            Protected method used by child classes to add a new column to the
            reader.
            \param i column info to add
            */
            virtual void _append_column(const ColumnInfo &i)
            {
                _columns_info.push_back(i);
            }

            //-----------------------------------------------------------------
            /*! \brief get column information

            Protected method used by child classes to retriev the info object
            for column i in the file.
            \param i index of the column in the file
            \return ColumnInfo instance for this column
            */
            virtual ColumnInfo _get_column(size_t i) const
            {
                return _columns_info.at(i);
            }

            /*! \brief get column information 

            Protected method used by child classes to obtain column information
            by using the name of the column. 
            \throws KeyError if the name of the column does not exist
            \param n name of the column
            \return ColumnInfo instance for this column
            */
            virtual ColumnInfo _get_column(const String &n) const
            {
                EXCEPTION_SETUP("virtual ColumnInfo SpreadsheetReader::"
                        "_get_column(const String &n) const");

                size_t i=0;
                for(auto c: _columns_info)
                {
                    if(c.name() == n)
                        return _get_column(i); 

                    //increment column counter
                    i++;
                }
                
                EXCEPTION_INIT(KeyError,"Column ["+n+"] not found!");
                EXCEPTION_THROW();
                return ColumnInfo(); //just to get rid of compiler warning
            }

            /*! \brief set number of records

            Child classes can use this method to set the number of records in
            the spreadsheet. 
            \param n number of records
            */
            void _nrecords(size_t n) { _nrec = n; }


        public:
            //========================public type==============================
            typedef std::vector<ColumnInfo>::iterator iterator; //!< iterator type
            typedef std::vector<ColumnInfo>::const_iterator const_iterator; //!< const iterator type
            //=======================destructor================================
            //! destructor
            virtual ~SpreadsheetReader();

            //===================assignment operators==========================
            //! copy assignment operator is deleted
            SpreadsheetReader &operator=(const SpreadsheetReader &) = delete;

            //! move assignment operator
            SpreadsheetReader &operator=(SpreadsheetReader &&r);

            //===============public memeber methods============================
            /*! \brief get column number 

            Returns the number of columns. 
            \return number of columns
            */
            size_t ncolumns() const
            {
                return _columns_info.size();
            }

            /*! \brief get record number

            Return the number of records in the spreadsheet.
            \return number of records
            */
            size_t nrecords() const { return _nrec; }

            /*! \brief get iterator to first column

            Return an iterator pointing to the first column in the file.
            \return iterator
            */
            iterator begin() { return _columns_info.begin(); }

            /*! \brief get const first iterator

            Return a const iterator to the first column in the file.
            \return const iterator
            */
            const_iterator begin() const { return _columns_info.begin(); }

            /*! \brief get last iterator

            Return an iterator to the last column in the file.
            \return iterator
            */
            iterator end() { return _columns_info.end(); }

            /*! \brief get const last iterator

            Returns a const iterator to the last column in the file.
            \return const iterator
            */
            const_iterator end() const { return _columns_info.end(); }

    };


//end of namespace
}
}

#endif
