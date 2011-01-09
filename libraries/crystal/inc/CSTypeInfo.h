#ifndef CSRTTI_H
#define CSRTTI_H

#include <stdarg.h>
#include <string>
#include <Crystal/include/CSTypes.h>

template < typename T > struct type_information;

#define REGISTER_TYPE( type )                  \
template <> struct type_information< type > {  \
    static const char * name() throw() {       \
        return #type;                          \
    }                                          \
}

REGISTER_TYPE( int );
REGISTER_TYPE( char );
//	-----------------------------------------------------------------------------
//	Class: CSTypeInfo
//	A custom Run Time Type Identification class.
//	By adding a few macros into your class, you can give it
//	TypeInfo properties.
//	To use, create a new class, based on imaginary classes 'A' and 'C':
//
//		class BaseClass : public A, public C{
//			TYPEINFO_DECLARE();
//		};
//
//	Then, in that classes' implementation file, place the following macro:
//
//		TYPEINFO_IMPLEMENTATION(BaseClass,0);
//
//	But WAIT! TypeInfo doesn't know anything about BaseClass' parents!
//
//	NOTE: if the class being given TypeInfo properties derives from any classes,
//	you must add class info to the end of the TYPEINFO_IMPLEMENTATION macro
//	as follows:
//
//		TYPEINFO_IMPLEMENTATION(BaseClass, 2, CLASS(A), CLASS(C));
//
//	And now you have a fully functioning class with TypeInfo properties.
//	To check the classes type, you can now do the following:
//
//		if(a_class->RTTI().isOfType(CLASS(BaseClass)))
//		{
//			//Do something since we know 'a_class' IS a BaseClass
//		}
//
//class TypeInfo
//	-----------------------------------------------------------------------------
template<typename _T>
class CSTypeInfo
{
public:
	// ----------------------------------------------
	// ctor() - set up the class RTTI info, including
	//          the name and parents' names
	// ----------------------------------------------
	CSTypeInfo(const CSString& a_sName, int32_t a_iNumParents, ...)
	:	m_strClassName(a_sName)
	{
		//Check if this class has any parents.
		if(a_iNumParents < 1)
		{
			//If not, not much needs to be done
			m_iNumParents = 0;
			m_pTypeInfoParents = nil;
		}
		else
		{
			//If it does though, load the parent info into this RTTI class
			m_iNumParents = a_iNumParents;
			m_pTypeInfoParents = new const CSTypeInfo*[a_iNumParents];

			//Since we're using a variable arguments contructor, we get to
			//have fun with va_lists
			va_list v;
			va_start(v, a_iNumParents);

			//Iterate over va_list
			for(int32_t t_iParentalIterator = 0; t_iParentalIterator < a_iNumParents; ++t_iParentalIterator)
			{
				//Loading parent info into 'm_pTypeInfoParents' array
				m_pTypeInfoParents[t_iParentalIterator] = va_arg(v, const CSTypeInfo*);
			}
		}
	};

	// ----------------------------------------------
	// GetClassName() - return the name of the class
	// ----------------------------------------------
	const CSString& getClassName() const
	{
		return m_strClassName;
	};

	// ----------------------------------------------
	// IsA() - return if the class is a class of type
	//          [a_cOtherRTTI], or if it even derives
	//			from it
	// ----------------------------------------------
	bool isOfType(const CSTypeInfo& a_cOtherTypeInfo) const
	{
		const CSTypeInfo& pCompare = self;

		if(&pCompare == &a_cOtherTypeInfo)
			return true;

		//If not, let's check this class' parents
		for(int32_t t_iTypeInfoIterator = 0; t_iTypeInfoIterator < m_iNumParents; ++t_iTypeInfoIterator)
		{
			//And while we're at it, all the ancestors will be taken into account as well
			if(m_pTypeInfoParents[t_iTypeInfoIterator]->isOfType(a_cOtherTypeInfo))
				return true;
		}
		//Oops!
		//These classes are NOT the same, or even related
		//Why are you comparing them then?
		return false;
	}
	static bool compareClasses(const CSTypeInfo& a_cTypeInfo1, const CSTypeInfo& a_cTypeInfo2)
	{
		return (a_cTypeInfo1.isOfType(a_cTypeInfo2));
	}
private:
	const CSString m_strClassName;
	int32_t m_iNumParents;
	const CSTypeInfo** m_pTypeInfoParents;
};

/*template <typename _T, typename _U>
_T* runTypeConversion(_U* object)
{
   if(object->getTypeInfo().isOfType(_T::m_typeInfo))
   {
      return dynamic_cast<_T>(object);
   }
   else
   {
      return NULL;
   }
}*/

/*template <typename _T>
_T* runtype_cast(void* object)
{
   return (_T*)object;
}*/
template <typename _T>
_T& runtype_cast(void* object)
{
   return (*(_T*)object);
}
#define compareTypes(a, b) \
 (CSTypeInfo::compareClasses(&a->getTypeInfo(),b))
#define runType(object) \
 (object.m_typeInfo)
#define runTypeP(object) \
 (object->m_typeInfo)

#define CLASS(class) (class::m_typeInfo)
#define PCLASS(class) (class->m_typeInfo)

#define TYPEINFO_DECLARE() \
public: \
static const CSTypeInfo m_typeInfo; \
virtual const CSTypeInfo& getTypeInfo() const { return m_typeInfo; };

#define TYPEINFO_IMPLEMENTATION(name, ...) \
const CSTypeInfo name::m_typeInfo(CSString(#name), __VA_ARGS__);
#endif

