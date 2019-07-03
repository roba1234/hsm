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

	virtual State* GetStates()
	{
		State* pState = nullptr;
		if (m_pCurrentState)
		{
			pState = m_pCurrentState->GetStates();
		}
		return pState;
	}


	virtual Action* Update()
	{
		Action* pActions = nullptr;

		if (m_pCurrentState == nullptr)
		{
			m_pCurrentState = m_pInitialState;
			return m_pCurrentState->GetActions();
		}


		Transition* pTriggeredTransition = nullptr;
		Transition* pTransition = m_pCurrentState->GetTransitions();
		while (pTransition)
		{
			if (pTransition->IsTriggered())
			{
				pTriggeredTransition = pTransition;
				break;
			}
		};
		

		UpdateResult* result = new UpdateResult();

		if (pTriggeredTransition)
		{
			result->pTransition = pTriggeredTransition;
			result->nLevel = pTriggeredTransition->GetLevel();
		}
		else
		{
			result = m_pCurrentState->Update();
		}


		if (result->pTransition)
		{
			if (result->nLevel == 0)
			{
				// it is on our level: honour the transitions ...
				State* pTarget = result->pTransition->GetTargetState();
				result->pActions += m_pCurrentState->GetExitActions();
				result->pActions += result->pTransition->GetActions();
				result->pActions += pTarget->GetEntryActions();

				// Set our current state
				m_pCurrentState = pTarget;


				// Add our normal actions
				result->pActions += GetActions();

				// clear transition, so nobody else does it
				result->pTransition = nullptr;
			}
			else if (result->nLevel > 0)
			{
				// Destination is for a higher level
				// Exit our current state.
				result->pActions += m_pCurrentState->GetExitActions();
				m_pCurrentState = nullptr;

				// Decrease the number of levels to go ...
				result->nLevel -= 1;
			}
			else
			{
				// it needs to be passed down
				State* pTarget = result->pTransition->GetTargetState();
				HSM* pTargetMachine = pTarget->GetParent();
				result->pActions += result->pTransition->GetActions();
				result->pActions += pTargetMachine->UpdateDown(pTarget, -result->nLevel);

				// clear the transition, so nobody else does it
				result->pTransition = nullptr;
			}
		}
		else
		{
			// if we don't have a transition ...
			result->pActions += GetActions();
		}
		return pActions;
	}


	Action* UpdateDown(State* pState, int nLevel)
	{
		Action* pAction = nullptr;
		if (nLevel > 0)
		{
			// pass ourself as the transition state to our parent
			pAction = parent->UpdateDown(this, nLevel - 1);
		}


	}


protected:
	State*		m_pStates;				// List of all states at this level of the hierarchy
	State*		m_pInitialState;		// Initial state when the machine has now current state
	State*		m_pCurrentState;
	HSM*		parent;
};