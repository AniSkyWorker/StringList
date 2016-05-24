#pragma once
#include <string>
#include <memory>

class CListIterator;

class CStringList
{
	friend class CListIterator;
	struct SNode
	{
		SNode(const std::string & data, SNode * prev, std::unique_ptr<SNode> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		SNode *prev;
		std::unique_ptr<SNode> next;
	};
public:
	size_t GetSize() const;

	void PushBack(const std::string & data);
	void PushFront(const std::string & data);

	void Clear();
	bool IsEmpty() const;

	std::string & GetBackElement();
	const std::string & GetBackElement()const;
	std::string & GetFrontElement();
	const std::string & GetFrontElement()const;

	CListIterator begin();
	CListIterator end();
	const CListIterator cbegin() const;
	const CListIterator cend() const;

	CListIterator rbegin();
	CListIterator rend();
	const CListIterator crbegin() const;
	const CListIterator crend() const;

	void Insert(const CListIterator & it, const std::string & data);
	void Erase(const CListIterator & it);

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode = nullptr;
	SNode * m_lastNode = nullptr;
};