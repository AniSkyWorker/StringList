#include "stdafx.h"
#include "ListIterators.h"

CListIterator::CListIterator(CStringList::SNode *value, bool isReverse)
	: m_node(value)
	, m_isReverse(isReverse)
{
}

CListIterator::CListIterator(const CListIterator& it)
	: m_node(it.m_node)
{
}

bool CListIterator::operator!=(const CListIterator & other)const
{
	return m_node != other.m_node;
}

bool CListIterator::operator==(const CListIterator & other)const
{
	return m_node == other.m_node;
}

std::string & CListIterator::operator*() const
{
	return m_node->data;
}

CListIterator & CListIterator::operator++()
{
	if (m_isReverse)
	{ 
		m_node = m_node->prev;
	}
	else
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CListIterator & CListIterator::operator--()
{
	if (m_isReverse)
	{
		m_node = m_node->next.get();
	}
	else
	{
		m_node = m_node->prev;
	}
	return *this;
}

CStringList::SNode * CListIterator::operator->() const
{
	return m_node;
}
