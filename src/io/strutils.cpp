/*
 * strutils.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

#include<string>

#include "strutils.hpp"

std::string strip(std::string &s,const char *begrem,const char *endrem){
    size_t start,stop;

    start = s.find_first_not_of(begrem);
    stop = s.find_last_not_of(endrem);

    return s.substr(start,(stop-start));
}

int get_key_value(std::string &s,const char *del,std::string &key,std::string &value){
    size_t start;

    start = s.find_first_of(del);

    key = s.substr(0,start);
    value = s.substr(start);

    start = value.find_first_not_of(del);
    value = value.substr(start);

    return 0;
}
