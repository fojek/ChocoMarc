// Action.h

#ifndef _ACTION_h
#define _ACTION_h

enum Type { GoTo, INCREMENTE, DECREMENTE, CONFIRME, VIDE };

class Action {

	Type m_type;
	unsigned int m_dest;

public:
	Action(Type);
	Action(Type pType, int pDest);
	// Méthodes factory
	static Action * createGoto(int); 
	static Action * createConfirme(void);
	static Action * createInc(void);
	static Action * createDec(void);
	static Action * createNull(void);
	// Getters
	Type type(void) { return m_type; };
	int dest(void) { return m_dest; };
};

#endif

