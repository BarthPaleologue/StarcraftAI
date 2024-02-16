#pragma once
#include "BT_UNIT_NODE.h"

template<class T, T value>
BT_UNIT_NODE<T, value>::BT_UNIT_NODE(std::string name, size_t childrenMaxCount) : BT_NODE(name, childrenMaxCount) {};

template<class T, T value>
BT_UNIT_NODE<T, value>::BT_UNIT_NODE(std::string name, BT_NODE* parent, size_t childrenMaxCount) : BT_NODE(name, parent, childrenMaxCount) {};