/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Dec 27, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include "../Types.hpp"
#include "../Exceptions.hpp"
#include "config_option.hpp"
#include "config_argument.hpp"

//set an abriviation for the namespace
namespace popts = boost::program_options;

namespace pni{
namespace utils{

    /*!
    \brief configuration class

    This class holds the configuration of a program or library that has been
    extracted from various sources.
    */
    class configuration 
    {
        private:
            //! stores the program options
            popts::variables_map _vmap;

            //! options visible in the help
            popts::options_description _visible_opts;

            //! options hidden in the help output
            popts::options_description _hidden_opts;

            //! positional arguments description
            popts::positional_options_description _oargs;
        protected:
            /*!
            \brief print options

            Append options string representation to an output stream. Only the
            visible options are appended to the output stream.
            \param o reference to the output stream
            \return reference to output stream
            */
            std::ostream &print(std::ostream &o) const;
        public:
            //===================constructors and destructor====================
            //! default constructor
            configuration();

            //! copy constructor - deleted
            configuration(const configuration &c) = delete;

            //------------------------------------------------------------------
            //! destructor
            ~configuration() {}

            //=====================public member functions====================== 
            /*!
            \brief get hidden options

            */
            const popts::options_description &visible_options() const
            {
                return _visible_opts;
            }

            //-----------------------------------------------------------------
            /*!
            \brief get hidden options

            */
            const popts::options_description &hidden_options() const
            {
                return _hidden_opts;
            }

            //-----------------------------------------------------------------
            /*!
            \brief get arguments

            Return reference to the arguments of the configuration.
            */
            const popts::positional_options_description &arguments() const
            {
                return _oargs;
            }

            //-----------------------------------------------------------------
            const popts::variables_map &map() const
            {
                return  _vmap;
            }

            //-----------------------------------------------------------------
            /*!
            \brief check if option is there

            Return true if a particular option has been passed by the user.
            If the option is present true is returned otherwise false.
            \param name long name of the option
            \return true if option exists
            */
            bool has_option(const String &name) const;

            //------------------------------------------------------------------
            /*! 
            \brief return the value of an option

            Template method returning the value of an option as instance of type
            T.  If the option was created with a default value this value will
            be returned. If the option was created without default value an
            exception will be thrown.
            \tparam T return type of the method
            \throws MissingCommandLineOption if option is not present and has no
            default value
            \param name long name of the option
            \return value of the option as instance of type T
            */
            template<typename T> T value(const String &name) const
            {
                if(has_option(name)) return _vmap[name].as<T>();
                throw cli_option_error(EXCEPTION_RECORD,
                        "Program option ["+name+"] not passed or "
                        "inappropriate value!");
            }

            //------------------------------------------------------------------
            /*!
            \brief add a program option


            */
            template<typename T>
            void add_option(const config_option<T> &opt,bool visible=true)
            {
                typedef boost::shared_ptr<popts::option_description> option_sptr;
                //assemble the name of the option
                String oname = opt.long_name();

                if(!opt.short_name().empty())
                    oname += ","+opt.short_name();

                //assemble the sematnic value
                auto value =
                    popts::value<T>(const_cast<T*>(opt.external_reference()));
                if(opt.has_default())
                    value->default_value(opt.default_value());

                option_sptr option_ptr (new popts::option_description(oname.c_str(),
                                        value,opt.description().c_str()));

                //finally we cann add the option
                if(visible)
                    _visible_opts.add(option_ptr);
                else
                    _hidden_opts.add(option_ptr);
                
            }

            //------------------------------------------------------------------
            void add_option(const config_option<Bool> &opt,bool visible=true);

            template<typename T> void add_argument(const config_argument<T> &arg)
            {
                typedef boost::shared_ptr<popts::option_description> option_sptr;
                //assemble the name of the option
                String oname = arg.long_name();

                //assemble the sematnic value
                auto value =
                    popts::value<T>(const_cast<T*>(arg.external_reference()));

                option_sptr option_ptr (new popts::option_description(oname.c_str(),
                                        value,arg.description().c_str()));

                //finally we cann add the option
                _hidden_opts.add(option_ptr);

                _oargs.add(arg.long_name().c_str(),arg.position());
            }


            friend std::ostream &operator<<(std::ostream &o,const configuration &c);

    };

//end of namespace
}
}
