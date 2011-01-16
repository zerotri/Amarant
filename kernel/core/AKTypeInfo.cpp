///////////////
//
// File: 
// Description:
//
///////////////

#include <kernel/AKTypeInfo.h>

// ----------------------------------------------
// ctor() - set up the class RTTI info, including
//          the name and parents' names
// ----------------------------------------------
/*AKTypeInfo::AKTypeInfo(const std::string& a_sName, int a_iNumParents, ...) :
				m_strClassName(a_sName)*/
				
AKTypeInfo::AKTypeInfo()
	: m_iNumParents(0)
	{
		m_pRTTIParents[0] = 0;
		m_pRTTIParents[1] = 0;
		m_pRTTIParents[2] = 0;
		m_pRTTIParents[3] = 0;
	}
AKTypeInfo::AKTypeInfo(AKTypeInfo* a_pParentA)
	: m_iNumParents(1)
	{
		//make sure we aren't going to cause any recursion bugs
		if(!Compare(this, a_pParentA))
			m_pRTTIParents[0] = a_pParentA;
		m_pRTTIParents[1] = 0;
		m_pRTTIParents[2] = 0;
		m_pRTTIParents[3] = 0;
	}
AKTypeInfo::AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB)
	: m_iNumParents(2)
	{
		if(!Compare(this, a_pParentA))
			m_pRTTIParents[0] = a_pParentA;
		if(!Compare(this, a_pParentB))
			m_pRTTIParents[1] = a_pParentB;
		m_pRTTIParents[2] = 0;
		m_pRTTIParents[3] = 0;
	}
AKTypeInfo::AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB, AKTypeInfo* a_pParentC)
	: m_iNumParents(3)
	{
		m_pRTTIParents[0] = a_pParentA;
		m_pRTTIParents[1] = a_pParentB;
		m_pRTTIParents[2] = a_pParentC;
		m_pRTTIParents[3] = 0;
	}
AKTypeInfo::AKTypeInfo(AKTypeInfo* a_pParentA, AKTypeInfo* a_pParentB, AKTypeInfo* a_pParentC, AKTypeInfo* a_pParentD)
	: m_iNumParents(4)
	{
		m_pRTTIParents[0] = a_pParentA;
		m_pRTTIParents[1] = a_pParentB;
		m_pRTTIParents[2] = a_pParentC;
		m_pRTTIParents[3] = a_pParentD;
	}
AKTypeInfo::~AKTypeInfo()
{
}
// ----------------------------------------------
// IsA() - return if the class is a class of type
//          [a_cOtherRTTI], or if it even derives
//			from it
// ----------------------------------------------
bool AKTypeInfo::IsA(const AKTypeInfo* a_cOtherRTTI) const
{
	const AKTypeInfo * pCompare = this;

	if(pCompare == a_cOtherRTTI)
		return true;

	//If not, let's check this class' parents
	for(int t_iRTTIIterator = 0; t_iRTTIIterator < m_iNumParents; ++t_iRTTIIterator)
	{
		//And while we're at it, all the ancestors will be taken into account as well
		if(m_pRTTIParents[t_iRTTIIterator]->IsA(a_cOtherRTTI))
			return true;
	}
	//Oops!
	//These classes are NOT the same, or even related
	//Why are you comparing them then?
	return false;
}

bool AKTypeInfo::Compare(const AKTypeInfo* a_cRTTI1, const AKTypeInfo* a_cRTTI2)
{
	return (a_cRTTI1->IsA(a_cRTTI2));
}
