///////////////
//
// File: 
// Description:
//
///////////////

#ifndef AKTypeInfo_H
#define AKTypeInfo_H

#include <stdarg.h>
//#include <string>

//class: WSRTTI
//	A custom Run Time Type Identification class.
//	Used quite a bit throughout the WS engine.
//	By adding a few macros into your class, you can give it
//	RTTI properties.
//	To use, create a new class, based on imaginary classes 'A' and 'C':
//
//		class BaseClass : public A, public C{
//			RTTI_DECLARE();
//		};
//
//	Then, in that classes' implementation file, place the following macro:
//
//		RTTI_IMPLEMENTATION(BaseClass,0);
//
//	But WAIT! RTTI doesn't know anything about BaseClass' parents!
//
//	NOTE: if the class being given RTTI properties derives from any classes,
//	you must add class info to the end of the RTTI_IMPLEMENTATION macro
//	as follows:
//
//		RTTI_IMPLEMENTATION(BaseClass, 2, CLASS(A), CLASS(C));
//
//	And now you have a fully functioning class with RTTI properties.
//	To check the classes type, you can now do the following:
//
//		if(a_class->RTTI().IsA(CLASS(BaseClass)))
//		{
//			//Do something since we know 'a_class' IS a BaseClass
//		}

class AKTypeInfo
{
public:
	//ctor
	AKTypeInfo();
	AKTypeInfo(AKTypeInfo* a_pParentA);
	AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB);
	AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB, AKTypeInfo* a_pParentC);
	AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB, AKTypeInfo* a_pParentC, AKTypeInfo* a_pParentD);
	~AKTypeInfo();
	//WSRTTI(const std::string& a_sName, int a_iNumParents, ...);

	//Used to return a std::string with the class' name
	//const std::string& GetClassName() const;

	//Used to compare a class' RTTI to this class' RTTI and see if they are the same
	bool IsA(const AKTypeInfo* a_cOtherRTTI) const;
	static bool Compare(const AKTypeInfo* a_cRTTI1, const AKTypeInfo* a_cRTTI2);
private:
	//const std::string m_strClassName;
	int m_iNumParents;
	const AKTypeInfo* m_pRTTIParents[4]; //max parents: 4
};

template <typename _ClassType>
AKTypeInfo* Base()
{
	return &(_ClassType::m_typeInfo);
};
/*template <ARTTI* _Class>
ARTTI* BaseP()
{
	return&(class->m_rtti);
};*/


#define RunType(object) \
	&(object.getTypeInfo())
#define RunTypeP(object) \
	&(object->getTypeInfo())

#define CLASS(class) \
	&(class::m_typeInfo)
#define PCLASS(class) \
	&(class->m_typeInfo)

#define DeclareTypeInfo() \
	public: \
		static const AKTypeInfo m_typeInfo; \
		virtual const AKTypeInfo& getTypeInfo() const { return m_typeInfo; }; \
	private:

#define DefineTypeInfo0(name) \
const AKTypeInfo name::m_typeInfo;
#define DefineTypeInfoX(name, ...) \
const AKTypeInfo name::m_typeInfo(__VA_ARGS__);

/*#define RTTI_IMPLEMENTATION(name, ...) \
const ARTTI name::m_rtti(std::string(#name), __VA_ARGS__);*/
#endif
