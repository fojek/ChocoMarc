// Action.h

#ifndef _ACTION_h
#define _ACTION_h

enum TYPE { GoTo, INCREMENTE, DECREMENTE, CONFIRME };

class ACTION {

	TYPE m_type;
	unsigned int m_dest;

public:
	ACTION(TYPE);
	ACTION(TYPE pType, int pDest);
	static ACTION * createGoto(int);
	static ACTION * createConfirme(int);
	static ACTION * createInc(void);
	static ACTION * createDec(void);
	TYPE type(void) { return m_type; };
	int dest(void) { return m_dest; };
};

#endif

