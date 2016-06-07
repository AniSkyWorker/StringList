#include "stdafx.h"
#include "StringList.h"
#include <cassert>
#include "ListIterators.h"

using namespace std;

CStringList::CStringList()
{
}

CStringList::CStringList(CStringList & list)
{
	CStringList toCopy;
	for (auto element : list)
	{
		toCopy.PushBack(element);
	}
	std::swap(m_firstNode, toCopy.m_firstNode);
	std::swap(m_lastNode, toCopy.m_lastNode);
	m_size = toCopy.m_size;
}

CStringList::~CStringList()
{
	Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::PushBack(const std::string & data)
{
	auto newNode = make_unique<SNode>(data, m_lastNode, nullptr);
	SNode *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	m_lastNode->next = nullptr;
	++m_size;
}

void CStringList::PushFront(const std::string & data)
{
	auto newNode = make_unique<SNode>(data, nullptr, move(m_firstNode));
	if (newNode->next)
	{
		newNode->next->prev = newNode.get();
	}
	else
	{
		m_lastNode = newNode.get();
	}
	m_firstNode = move(newNode);
	m_firstNode->prev = nullptr;
	m_size++;
}

CListIterator CStringList::begin()
{
	return CListIterator(m_firstNode.get(), false);
}

CListIterator CStringList::end()
{
	return CListIterator(m_lastNode->next.get(), false);
}

const CListIterator CStringList::cbegin() const
{
	return CListIterator(m_firstNode.get(), false);
}

const CListIterator CStringList::cend() const
{
	return CListIterator(m_lastNode->next.get(), false);
}

CListIterator CStringList::rbegin()
{
	return CListIterator(m_lastNode, true);
}

CListIterator CStringList::rend()
{
	return CListIterator(m_firstNode->prev, true);
}

const CListIterator CStringList::crbegin() const
{
	return CListIterator(m_lastNode, true);
}

const CListIterator CStringList::crend() const
{
	return CListIterator(m_firstNode->prev, true);
}

void CStringList::Insert(const CListIterator & it, const std::string & data)
{
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		PushBack(data);
	}
	else
	{
		auto node = make_unique<SNode>(data, it->prev, move(it->prev->next));
		it->prev = move(node.get());
		node->prev->next = move(node);
	}
}

void CStringList::Erase(const CListIterator & it)
{
	if (m_size == 1)
	{
		Clear();
		return;
	}

	if (it == begin())
	{
		it->next->prev = nullptr;
		m_firstNode = move(it->next);
	}
	else if (it->data == GetBackElement())
	{
		it->prev->next = nullptr;
		m_lastNode = move(it->prev);
	}
	else
	{
		it->next->prev = move(it->prev);
		it->prev->next = move(it->next);
	}

	if (m_size > 0)
	{
		m_size--;
	}
}

void CStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0u;
}

std::string & CStringList::GetBackElement()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

const std::string & CStringList::GetBackElement() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string & CStringList::GetFrontElement()
{
	assert(m_firstNode);
	return m_firstNode->data;
}
const std::string & CStringList::GetFrontElement() const
{
	assert(m_firstNode);
	return m_firstNode->data;
}
