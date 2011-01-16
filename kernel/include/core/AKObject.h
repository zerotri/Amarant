#ifndef AKOBJECT_H
#define AKOBJECT_H
#include <stdint.h>

template <typename _T>
class AKObject
{
public:
	AKObject()
	{
		__pAKObject_Object = new _T();
		AddRef();
	}
	~AKObject()
	{
		Destroy();
	}
	AKObject(AKObject<_T>& copy)
	:__pAKObject_Object(*copy)
	{
		AddRef();
	}
	AKObject(_T* copy)
	:__pAKObject_Object(*copy)
	{
		AddRef();
	}
	_T& operator*() const
    {
		return *__pAKObject_Object;
    }
	_T* operator-> ()
	{
		return __pAKObject_Object;
	};
private:
	uint32_t __iAKObject_Reference_Count__;
	_T*		 __pAKObject_Object;
protected:	
	void AddRef()
	{
		__iAKObject_Reference_Count__++;
	}
	void Destroy()
	{
		if(--__iAKObject_Reference_Count__ == 0)
		{
			delete __pAKObject_Object;
		}
	}
	
};
template <typename _T>
AKObject<_T>* AKAllocate()
{
	return new AKObject<_T>();
};
#endif