#ifndef CSMEMORY_H
#define CSMEMORY_H
#include <memory>
#include <CSTypes.h>

//	Copyright (C) 2010 by Wynter Woods <zerotri@gmail.com>
//	This software is distributed under the MIT license. The one thing I ask is
//	that if you use this software for anything, let me know. It's always good
//	to hear that someone else is making use of something you created.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.

//	-----------------------------------------------------------------------------
//	Method:	CSAllocateMemory
//	-----------------------------------------------------------------------------
template <typename _T>
_T* CSAllocateMemory(uint32_t size = 1)
{
	if(size == 0)
		return nil;
    return new _T[size];
}

//	-----------------------------------------------------------------------------
//	Method:	CSCopyBlock
//	-----------------------------------------------------------------------------
template <typename _T>
void CSCopyBlock(_T* src, _T* dst, const uint32_t blockSize)
{
    memcpy(dst, src, blockSize);
}
template <typename _T>
_T* CSCopyRegion2D(_T* src, const uint32_t width, const uint32_t height, const uint32_t stride)
{
    _T* newPtr = CSAllocateMemory<_T>[width*height];
    uint8_t* srcPtr = (uint8_t*)src;
    uint8_t* dstPtr = (uint8_t*)newPtr;
    for(uint32_t i = 0; i < height; i++, srcPtr += stride*sizeof(_T), dstPtr += width*sizeof(_T))
    {
        CSCopyBlock<u8_t>(srcPtr, dstPtr, width*sizeof(_T));
    }
    return newPtr;
}
//	-----------------------------------------------------------------------------
//	Method:	CSMemoryZero
//	Provides a fast and easy way to zero a region of memory, such as an array or
//	struct. Should NOT be used on C++ classes if the class requires a constructor
//	to initialize it. Another function has been created to allow zero and
//	reinitialization of object memory.
//
//	NOTE: Should not be used on classes objects.
//	-----------------------------------------------------------------------------
template <typename _T>
void CSZeroMemory(_T& object)
{
	memset(&object, nil, sizeof(_T));
}

//	-----------------------------------------------------------------------------
//	Method:	CSCopyMemory
//	Provides a fast and easy way to make a copy of memory. It can be used like
//	either of the following examples:
//		u8_t* somePointer = CSCopyMemory<u8_t>(oldPointer, 32);
//
//		Vertex* newVertex = CSCopyMemory<Vertex>(oldVertex);
//
//	Where in the first example a size is specified, in the second it is taken as
//	the size of the type provided because no size was specified
//	-----------------------------------------------------------------------------
template <typename _T>
_T* CSCopyMemory(_T* ptr, uint32_t size = 1)
{
    _T* newPtr = 0;
	//cannot allocate memory with 0 size, so we shall return nil
	if(size == 0)
	{
		return nil;
	}

    if(size == 1)
    {
        newPtr = CSAllocateMemory<_T>[_T];
        memcpy(newPtr, ptr, sizeof(_T));
    }
    else
    {
        newPtr = CSAllocateMemory<uint8_t>[size];
        memcpy(newPtr, ptr, size);
    }
    return newPtr;
}
//	-----------------------------------------------------------------------------
//	Method:	CSClassZero
//		 Provides a fast and easy way to zero an object. Useful only if the
//		 object being zero'ed contains a public constructor, otherwise this is
//		 rather useless.
//	-----------------------------------------------------------------------------
template <typename _object>
void CSZeroInstance(_object& instance)
{
	instance._object::~_object();
	memset(&instance, nil, sizeof(_object));
	instance._object::_object();
}

#endif