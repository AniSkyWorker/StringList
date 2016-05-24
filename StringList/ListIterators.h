#pragma once
#include <iterator>
#include "StringList.h"
#include "ListIterators.h"

class CListIterator : public std::iterator <std::random_access_iterator_tag, CStringList::SNode>
{
	friend class CStringList;
public:
	CListIterator(const CListIterator &it);
	CListIterator(CStringList::SNode* value, bool isReverse = false);
public:
	bool operator!=(CListIterator const& other) const;
	bool operator==(CListIterator const& other) const;
	std::string & operator*() const;
	CListIterator& operator++();
	CListIterator& operator--();
private:
	CStringList::SNode * operator->()const;

	CStringList::SNode* m_node = nullptr;
	bool m_isReverse = false;
};