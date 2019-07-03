#pragma once
#include "State.h"
#include "HSM.h"

class SubMachineState : public State, HSM
{
public:
	Action* GetActions()
	{
		return State::GetActions();
	}

	Action* Update()
	{
		return HSM::Update();
	}

	State* GetStates()
	{
		State* states;
		if (m_pCurrentState)
		{
			states = m_pCurrentState->GetStates();
			states += this;
		}
		else
		{
			return this;
		}
	}
};