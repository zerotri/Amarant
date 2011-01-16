#ifndef ARRAY_H
#define ARRAY_H
#include <stdint.h>
#include <memory.h>

template <typename _Type> struct less
{
	_Type arg1;
	_Type arg2;
  bool compare (const _Type x, const _Type y) const
    {
		return x < y;
	}
};

template <typename _Type, typename _IndexType = uint32_t, typename _Compare = less<_Type> >
class OrderedArray
{
public:
	typedef _Compare less_than;
	typedef _IndexType index_t;
public:
	OrderedArray(_IndexType max_size)
	{
	    m_array = (_Type*)malloc(max_size*sizeof(_Type));
	    memset((uint8_t*)m_array, 0, max_size*sizeof(_Type));
	    m_size = 0;
	    m_max_size = max_size;
	}
	OrderedArray(void *addr, _IndexType max_size)
	{
	    m_array = (_Type*)addr;
	    memset((uint8_t*)m_array, 0, max_size*sizeof(_Type));
	    m_size = 0;
	    m_max_size = max_size;
	}
	~OrderedArray()
	{
		free(m_array);
	}
	void insert(_Type& item)
	{
	    _IndexType iterator = 0;
	    while ((iterator < m_size) && less_than::compare(lookup(iterator), item))
	        iterator++;
	    if (iterator == m_size) // just add at the end of the array.
	        m_array[m_size++] = item;
	    else
	    {
	        _Type tmp = m_array[iterator];
	        m_array[iterator] = item;
	        while (iterator < m_size)
	        {
	            iterator++;
	            _Type tmp2 = m_array[iterator];
	            m_array[iterator] = tmp;
	            tmp = tmp2;
	        }
	        m_size++;
	    }
	}
	_Type& lookup(_IndexType index)
	{
		return m_array[index];
	}
	void remove(_IndexType index)
	{
		while (index < m_size)
	    {
	        m_array[index] = m_array[index+1];
	        index++;
	    }
	    m_size--;
	}
	_IndexType size()
	{
		return m_size;
	}
private:
protected:
	_Type *m_array;
    _IndexType m_size;
    _IndexType m_max_size;
};
#endif