#pragma once

#include "UpdateResult.h"
#include "Action.h"


class State;

/** ---------------------------------------------------------------------------
	\brief
	All classes, aside from Transition, inherit HSMBase class which will 
	simplify the algorithm by allowing functions to treat anything in the
	hierarchy in the same way.


	I have updated the Update method to return a status of the call in
	order to have better error protection.  Results are passed in as
	parameters to be returned.

	This is an abstract class that has one pure virtual function 
	called GetStates()



---------------------------------------------------------------------------- */
class HSMBase
{
public:
	HSMBase() 
		: m_pActions(nullptr)
		, parent(nullptr)
	{}

	HSMBase(HSMBase* pParent)
		: m_pActions(nullptr)
		, parent(pParent)
	{}

	~HSMBase() {}

	Action* GetActions() { return m_pActions; }
	HSMBase* Parent() { return parent; }

	int Update(UpdateResult* pResult)
	{
		pResult->pActions = GetActions();
		pResult->pTransition = nullptr;
		pResult->nLevel = 0;
		return 1;
	}

	virtual State* GetStates() = 0;


protected:
	Action*		m_pActions;
	HSMBase*	parent;
};