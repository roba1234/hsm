#pragma once


#include "Action.h"


class State;
class Transition;


class UpdateResult
{
public:
	UpdateResult()
		: pActions(nullptr)
		, pTransition(nullptr)
		, nLevel(0)
	{}

	~UpdateResult()
	{
		pActions = nullptr;
		pTransition = nullptr;
		nLevel = 0;
	}


	Action*		pActions;
	Transition*	pTransition;
	int			nLevel;
};



class HSMBase
{

public:
	HSMBase() 
		: m_pActions(nullptr)
	{}

	~HSMBase() {}

	Action* GetActions()
	{
		return m_pActions;
	}

	UpdateResult* Update()
	{
		UpdateResult* result = new UpdateResult();

		result->pActions = GetActions();
		result->pTransition = nullptr;
		result->nLevel = 0;

		return result;
	}

	virtual State* GetStates() = 0;

protected:
	Action*		m_pActions;
	HSMBase*	parent;
};