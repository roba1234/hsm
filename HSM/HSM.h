#pragma once

#include "HSMBase.h"
#include "State.h"
#include "Action.h"
#include "Transition.h"


class HSM : public HSMBase
{
public:
	HSM() {}
	~HSM() {}

	virtual State* GetStates();
	virtual Action* Update();
	Action* UpdateDown(State* pState, int nLevel);

	State* GetCurrentState() { return m_pCurrentState; }
	void SetCurrentState(State* pState) { m_pCurrentState = pState; }

	State* GetInitialState() { return m_pInitialState; }

protected:
	State*		m_pStates;				// List of all states at this level of the hierarchy
	State*		m_pInitialState;		// Initial state when the machine has now current state
	State*		m_pCurrentState;
	HSM*		parent;
};