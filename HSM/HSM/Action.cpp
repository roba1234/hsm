#include "Action.h"

Action* Action::GetLast()
{
	if (m_pNext == nullptr)
		return this;

	// Find the end iteratively
	Action* pCurr = this;
	Action* pNext = m_pNext;

	while (pNext)
	{
		pCurr = pNext;
		pNext = pNext->m_pNext;
	}

	return pCurr;
}



void Action::DeleteList()
{
	if (m_pNext == nullptr)
	{
		m_pNext->DeleteList();
	}
	delete this;
}


void Action::Act()
{
	// Do nothing ...
}


bool Action::CanInterrupt()
{
	return false;
}


bool Action::CanDoBoth(const Action* pOther) const
{
	return false;
}


bool Action::IsComplete()
{
	return true;
}


ActionManager::ActionManager()
	: m_nActivePriority(0)
	, m_pActionQueue(nullptr)
	, m_pActiveAction(nullptr)
{
}

void ActionManager::ScheduleAction(Action* pNewAction)
{
	Action** pPrev = &m_pActionQueue;
	Action*	pNext = m_pActionQueue;

	while (pNext != nullptr)
	{

		// if we found a lower priority, we go here.  
		//
		// Note that this will be much quicker with a >=, but
		// it means in the absence of priority ordering the queue
		// defaults to FIFO, which isn't very useful.

		if (pNewAction->m_nPriority > pNext->m_nPriority)
		{
			break;
		}


		// When we get here, we have either found the location mid-list
		// or reached the end of the list, so add it on.
		pPrev = &pNext->m_pNext;
		pNext = pNext->m_pNext;
	}
}


void ActionManager::Execute()
{
	// check if we need to interrupt the currently active actions
	CheckInterrupts();
	AddAllToActive();
	RunActive();
}


void ActionManager::CheckInterrupts()
{
	Action** previous = &m_pActionQueue;
	Action* next = m_pActionQueue;
	while (next != nullptr)
	{
		// If we drop below the active priority, give up
		if (next->m_nPriority < m_nActivePriority)
		{
			break;
		}

		// Otherwise we're beating for priority, so check if we
		// need to interrupt.
		if (next->CanInterrupt()) 
		{

			// So we have to interrupt. Initially just replace the
			// active set.

			// Delete the previous active list
			if (m_pActiveAction != nullptr) m_pActiveAction->DeleteList();

			// Add the new one
			m_pActiveAction = next;
			m_nActivePriority = m_pActiveAction->m_nPriority;

			// Rewire the queue to extract our action
			*previous = next->m_pNext;
			next->m_pNext = nullptr;

			// And stop looking (the highest priority interrupter wins).
			break;
		}

		// Check the next one
		previous = &next->m_pNext;
		next = next->m_pNext;
	}