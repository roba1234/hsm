#include "pch.h"
#include <assert.h>

#include "HSM.h"
#include "State.h"
#include "UpdateResult.h"
#include "Action.h"




State* HSM::GetStates()
{
	State* pState = nullptr;
	if (GetCurrentState())
	{
		pState = GetCurrentState()->GetStates();
	}
	return pState;
}



Action* HSM::UpdateDown(State* pState, int nLevel)
{
	Action* pAction = nullptr;
	if (nLevel > 0)
	{
		// pass ourself as the transition state to our parent
//		pAction = parent->UpdateDown(this, nLevel - 1);
	}
	return pAction;
}




Action* HSM::Update()
{
	UpdateResult result;
	UpdateResult* pResult = &result;

	Action* pActions = nullptr;

	if (GetCurrentState() == nullptr)
	{
		SetCurrentState(m_pInitialState);
		return GetCurrentState()->GetActions();
	}


	Transition* pTriggeredTransition = nullptr;
	Transition* pTransition = GetCurrentState()->GetTransitions();
	while (pTransition)
	{
		if (pTransition->IsTriggered())
		{
			pTriggeredTransition = pTransition;
			break;
		}
	};



	if (pTriggeredTransition)
	{
		pResult->pTransition = pTriggeredTransition;
		pResult->nLevel = pTriggeredTransition->GetLevel();
	}
	else
	{
		GetCurrentState()->Update(pResult);
	}


	if (pResult->pTransition)
	{
		if (pResult->nLevel == 0)
		{
			// it is on our level: honour the transitions ...
			State* pTarget = pResult->pTransition->GetTargetState();

			pResult->AddActions(GetCurrentState()->GetExitActions());
			pResult->AddActions(pResult->pTransition->GetActions());
			pResult->AddActions(pTarget->GetEntryActions());

			// Set our current state
			SetCurrentState(pTarget);

			// Add our normal actions
			pResult->AddActions(GetActions());

			// clear transition, so nobody else does it
			pResult->pTransition = nullptr;
		}
		else if (pResult->nLevel > 0)
		{
			// Destination is for a higher level
			// Exit our current state.
			pResult->AddActions(GetCurrentState()->GetExitActions());
			SetCurrentState(nullptr);

			// Decrease the number of levels to go ...
			pResult->nLevel -= 1;
		}
		else
		{
			// it needs to be passed down
			State* pTarget = pResult->pTransition->GetTargetState();
			HSM* pTargetMachine = dynamic_cast<HSM*>(pTarget->Parent());
			pResult->AddActions(pTransition->GetActions());
			pResult->AddActions(pTargetMachine->UpdateDown(pTarget, -pResult->nLevel));

			// clear the transition, so nobody else does it
			pResult->pTransition = nullptr;
		}
	}
	else
	{
		// if we don't have a transition ...
		pResult->AddActions(GetActions());
	}
	return pActions;
}