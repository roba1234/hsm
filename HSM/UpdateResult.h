#pragma once
#include <vector>

class Action;
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


	void AddActions(Action* pAction) { m_vecActions.push_back(pAction); }
	void AddTransitions(Transition* pTransition) { m_vecTrans.push_back(pTransition); }

	void ClearActions() { m_vecActions.clear(); pActions = nullptr; }
	void ClearTransition() { m_vecTrans.clear(); pTransition = nullptr; }



	Action*		pActions;
	Transition*	pTransition;
	int			nLevel;

	std::vector<Action*>		m_vecActions;
	std::vector<Transition*>	m_vecTrans;
};