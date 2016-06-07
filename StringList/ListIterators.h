#pragma once
#include <iterator>
#include "StringList.h"
#include "ListIterators.h"

class CListIterator : public std::iterator <std::random_access_iterator_tag, CStringList::SNode>
{
public:
	// TODO: don't make isReverse default.
	CListIterator(const CListIterator& it);
	CListIterator(CStringList::SNode* value, bool isReverse);

	bool operator!=(CListIterator const& other) const;
	bool operator==(CListIterator const& other) const;
	std::string & operator*() const;
	CListIterator& operator++();
	CListIterator& operator--();

private:
	friend class CStringList;

	CStringList::SNode * operator->()const;

	CStringList::SNode* m_node = nullptr;
	bool m_isReverse = false;
};