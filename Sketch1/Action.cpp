#include "Action.h"

Action::Action(Type pType) : m_type(pType)
{
	m_dest = 0;
}

Action::Action(Type pType, int pDest) : m_type(pType), m_dest(pDest) 
{}

Action * Action::createGoto(int pDest)
{
	return new Action(Type::GoTo, pDest);
}

Action * Action::createConfirme()
{
	return new Action(Type::CONFIRME);
}

Action * Action::createInc()
{
	return new Action(Type::INCREMENTE);
}
Action * Action::createDec()
{
	return new Action(Type::DECREMENTE);
}

Action * Action::createNull(void)
{
	return new Action(Type::VIDE);
}
