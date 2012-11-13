#ifndef __BUFFERHELPER_HPP__
#define __BUFFERHELPER_HPP__

#include <pni/utils/DBuffer.hpp>
#include <pni/utils/RBuffer.hpp>
#include <pni/utils/NewAllocator.hpp>

using namespace pni::utils;

template<typename T,typename Allocator>
    void allocate_buffer(DBuffer<T,Allocator> &b,size_t n)
{
    b =  DBuffer<T,Allocator>(n);
}


//-------------------------------------------------------------------------
template<typename T>
    void allocate_buffer(RBuffer<T> &b,size_t n)
{
    b = RBuffer<T>(n,new T[n]);
}
#endif
