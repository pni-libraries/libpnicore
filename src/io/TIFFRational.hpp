/*
 * Implementation of class TIFFRational
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
 * Declaration of class TIFFRational.
 *
 * Created on: Jun 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#ifndef __TIFFRATIONAL_HPP_
#define __TIFFRATIONAL_HPP_

#include <iostream>

#include "../Types.hpp"

namespace pni{
    namespace utils{


        /*! \ingroup io_classes
        \brief rational type for TIFF IFD entries

        IFD entries in TIFF files can consist of a rational number. This class
        implements such a type as a template.
        */
        template<typename T> class Rational{
            protected:
                T _numerator;    //!< numerator of the rational number
                T _denominator;  //!< denominator of the rational number
            public:
                //=================constructors and destructor=================
                //! default constructor
                Rational();
                //! copy constructor
                Rational(const Rational &o);
                //! standard constructor
                Rational(const T &,const T&);
                //! destructor
                ~Rational(){}

                //================assignment operator===========================
                //! copy assignment operator
                virtual Rational<T> &operator=(const Rational<T> &r);

                //! set the numerator
                void numerator(const T &v) { _numerator = v; }
                //! get the numerator
                T numerator() const { return _numerator; } 

                //! set the denominator
                void denominator(T &v) { _denominator = v; }
                //! get the denominator
                T denominator() const { return _denominator; }

        };

        //=============implementation of template methods======================
        //implementation of the default constructor
        template<typename T> Rational<T>::Rational():
            _numerator(0),
            _denominator(0)
        { }

        //implementation of the copy constructor
        template<typename T> Rational<T>::Rational(const Rational<T> &r):
            _numerator(r._numerator),
            _denominator(r._denominator)
        { }

        //implementation of the standard constructor
        template<typename T> Rational<T>::Rational(const T &n,const T &d):
            _numerator(n),
            _denominator(d)
        { }

        //implementation of the copy assignment operator
        template<typename T> 
            Rational<T> &Rational<T>::operator=(const Rational<T> &r)
        {
            if(this != &r){
                _numerator = r._numerator;
                _denominator = r._denominator;
            }
            return *this;
        }
        
        //implementation of the output operator
        template<typename T> 
            std::ostream &operator<<(std::ostream &o,const Rational<T> &r)
        {
            o<<r.numerator()<<"/"<<r.denominator();
            return o;
        }


        //some default types 
        typedef Rational<UInt32> URational;
        typedef Rational<Int32> SRational;

    //end namespaces
    }
}


#endif /* TIFFRATIONAL_HPP_ */
