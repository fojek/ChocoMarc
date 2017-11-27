#include "Action.h"

ACTION::ACTION(TYPE pType) : m_type(pType)
{
	m_dest = 0;
}

ACTION::ACTION(TYPE pType, int pDest) : m_type(pType), m_dest(pDest) 
{}

ACTION * ACTION::createGoto(int pDest)
{
	return new ACTION(TYPE::GoTo, pDest);
}

ACTION * ACTION::createConfirme(int pDest)
{
	return new ACTION(TYPE::CONFIRME, pDest);
}

ACTION * ACTION::createInc()
{
	return new ACTION(TYPE::INCREMENTE);
}
ACTION * ACTION::createDec()
{
	return new ACTION(TYPE::DECREMENTE);
}