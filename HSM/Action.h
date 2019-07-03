#pragma once
#include <iostream>
#include <vector>

class Action
{
public:
	Action()
		: m_pNext(nullptr)
		, m_nData(0)
	{
	}

	Action(int data)
		: m_pNext(nullptr)
		, m_nData(data)
	{
		m_pLast = this;
	}
	~Action() {}



	void Act();


	virtual bool IsComplete();
	virtual bool CanDoBoth(const Action* pOther) const;
	virtual void DeleteList();
	virtual bool CanInterrupt();
	Action* GetLast();


	void pushback(Action* pAction)
	{
		Action* pCurr = m_pLast;

		if (pCurr)
		{
			while (pCurr->m_pNext)
			{
				pCurr = pCurr->m_pNext;
			}
			pCurr->m_pNext = pAction;

			m_pLast = pAction->m_pLast;
		}
		else
		{
			m_pLast = pAction->m_pLast;
		}
	}



	void DisplayList()
	{
		Action* pCurr = this;
		while (pCurr)
		{
			pCurr->Act();
			pCurr = pCurr->m_pNext;
		};

		std::cout << " " << std::endl;
		std::cout << " " << std::endl;
		std::cout << " " << std::endl;

	}

public:
	Action*		m_pLast;
	Action*		m_pNext;
	int			m_nData;
	int			m_nPriority;

};



#if 0
class ActionManager
{
public:
	int		m_nActivePriority;
	Action*	m_pActionQueue;
	Action*	m_pActiveAction;

	std::vector<Action*>	m_vecActions;

protected:
	void	RunActive();
	void	CheckInterrupts();
	void	AddAllToActive();

public:
	ActionManager();
	void ScheduleAction(Action* pNewAction);
	void Execute();
};


#endif