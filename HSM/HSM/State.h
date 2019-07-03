#pragma once

#include "HSMBase.h"

class State : public HSMBase
{
public:
	State() {}
	~State() {}

	virtual State* GetStates() { return this; }
	Action* GetActions() { return m_pActions; }

	Action* GetEntryActions() { return m_pEntryActions; }
	Action* GetExitActions() { return m_pExitActions; }
	Transition* GetTransitions() { return m_pTransitions; }

protected:
	Action* m_pEntryActions;
	Action* m_pExitActions;
	Transition* m_pTransitions;
};