#pragma once
#include "BT_NODE.h"

template<class T, T value>
class BT_UNIT_NODE :
	public BT_NODE
{
public:
	BT_UNIT_NODE(std::string name, size_t childrenMaxCount);

	BT_UNIT_NODE(std::string name, BT_NODE* parent, size_t childrenMaxCount);
};

#include "BT_UNIT_NODE.cpp"