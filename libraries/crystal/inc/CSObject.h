#ifndef CSOBJECT_H
#define CSOBJECT_H

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

#include <Crystal/include/CSTypes.h>
//	-----------------------------------------------------------------------------
//	Class:	CSObject
//		a correct implementation of CSObject will include
//		garbage collection, smart pointer access, and a proper typeinfo
//		implementation, unlike the CSTypeInfo class currently provided.
//	-----------------------------------------------------------------------------
template <typename _T>
class CSObject
{
public:
	static _T* __csobject_allocate()
	{
		return CSAllocateMemory<_T>();
	}
};

//	-----------------------------------------------------------------------------
//	Method: CSObjectAllocate
//		This function provides an easy to use API for creating CSObjects on
//		without having to worry about internal details. So long as the
//		underlying library includes a working port, the function should
//		automatically allocate and construct a new CSObject.
//	Used like so:
//
//		SomeObject* child = CSObjectAllocate<ParentObject>();
//
//	-----------------------------------------------------------------------------
template <typename _T>
_T* CSAllocateObject()
{
	return CSObject<_T>::__csobject_allocate();
}
#endif
