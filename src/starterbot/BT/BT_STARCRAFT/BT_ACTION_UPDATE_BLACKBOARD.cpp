#include "BT_ACTION_UPDATE_BLACKBOARD.h"
#include "Blackboard.h"

template <typename T>
BT_ACTION_UPDATE_BLACKBOARD<T>::BT_ACTION_UPDATE_BLACKBOARD(std::string name, T& ref, T value, BT_NODE* parent)
	: BT_ACTION(name, parent), m_value_to_assign(value), m_ref_to_blackboard(ref){
}

template <typename T>
BT_NODE::State BT_ACTION_UPDATE_BLACKBOARD<T>::Evaluate(void* data)
{
	//Blackboard* pData = (Blackboard*)data;
	m_ref_to_blackboard = m_value_to_assign;
	return BT_NODE::SUCCESS;
}

template <typename T>
std::string BT_ACTION_UPDATE_BLACKBOARD<T>::GetDescription()
{
	return "ACTION_UPDATE_BLACKBOARD";
}
