#pragma once

#include "State.h"
#include "Action.h"
#include "Condition.h"



/*
	\reference:
	AI for Games 3d Edition, Millington page 218

	\Implementation
	Only one implementation of the state class should be required: it can simply hold the three lists
	of actions and the list of transitions as data members, returning them in the corresponding
	get methods.

	In the same way, we can store the target state and a list of actions in the transition class
	and have its methods return the stored values. The isTriggered method is more difficult to
	generalize. Each transition will have its own set of conditions, and much of the power in this
	approach is allowing the transition to implement any kind of tests it likes.

	Because state machines are often defined in a data file and read into the game at runtime,
	it is a common requirement to have a set of generic transitions. The state machine can then
	be constructed from the data file by using the appropriate transitions for each state.

	In the previous section on decision trees, we saw generic testing decisions that operated
	on basic data types. The same principle can be used with state machine transitions: we have
	generic transitions that trigger when data they are looking at are in a given range.

	Unlike decision trees, state machines don’t provide a simple way of combining these tests
	to make more complex queries. If we need to transition on the condition that the enemy is
	far away AND health is low, then we need some way of combining triggers together.

	In keeping with the polymorphic design for the state machine, we can accomplish this with
	the addition of another interface: the Condition interface. 


*/
class Transition
{
public:
	Transition()
		: m_pActions(nullptr)
		, m_pCondition(nullptr)
		, m_pState(nullptr)
	{}

	~Transition() {}

	int GetLevel() { return 0; }

	Action* GetActions() { return m_pActions; }
	State* GetTargetState() { return m_pState; }
	bool IsTriggered() { return m_pCondition->Test(); }

protected:
	Action*		m_pActions;
	State*		m_pState;
	Condition*	m_pCondition;

};