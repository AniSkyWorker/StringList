#include "stdafx.h"
#include <iostream>
#include "../StringList/StringList.h"
#include "../StringList/ListIterators.h"

using namespace std;

struct EmptyStringList
{
	CStringList list;
};

void VerifyList(CStringList & list, std::vector<string> & expectedElements)
{
	size_t counter = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedElements[counter]);
		counter++;
	}
}

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

	BOOST_AUTO_TEST_SUITE(when_created)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(list.IsEmpty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_back_a_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushBack("hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			list.PushBack("goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_push_front_a_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.GetSize();
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 1);
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetSize(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_and_GetFrontElement_method)
		{
			list.PushFront("hello");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "hello");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
			list.PushFront("goodbye");
			BOOST_CHECK_EQUAL(list.GetFrontElement(), "goodbye");
			BOOST_CHECK_EQUAL(list.GetBackElement(), "hello");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.PushBack("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.GetBackElement()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_not_empty : EmptyStringList
	{
		when_not_empty()
		{
			list.PushBack("hello");
			list.PushBack("Ho-ho-ho");
			list.PushBack("goodbye");
		}

		std::vector<std::string> expectedStrings = { "hello", "Ho-ho-ho", "goodbye" };
	};

	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, when_not_empty)

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.IsEmpty());
			list.Clear();
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(have_iterators_and_const_iterators_at_begin_and_end_of_string_list)
		{
			size_t counter = 0;
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter++;
			}

			counter = 0;
			for (auto it = list.cbegin(); it != list.cend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(have_reverse_iterators_and_const_revers_iterators_at_begin_and_end_of_string_list)
		{
			size_t counter = expectedStrings.size() - 1;
			for (auto it = list.rbegin(); it != list.rend(); ++it)
			{
				BOOST_CHECK_EQUAL(*it, expectedStrings[counter]);
				counter--;
			}
		}

		BOOST_AUTO_TEST_CASE(can_get_acsses_to_elements_from_range_based_for)
		{
			size_t counter = 0;
			for (auto str : list)
			{
				BOOST_CHECK_EQUAL(str, expectedStrings[counter]);
				counter++;
			}
		}

		BOOST_AUTO_TEST_CASE(can_insert_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			list.Insert(it, "20");
			BOOST_CHECK_EQUAL(*++list.begin(), "20");

			list.Insert(list.begin(), "11");
			BOOST_CHECK_EQUAL(*list.begin(), "11");

			list.Insert(list.end(), "30");

			std::vector<std::string> expectedStrings = {"11", "hello", "20", "Ho-ho-ho", "goodbye", "30"};
			size_t i = 0;
			for (auto str : list)
			{
				BOOST_CHECK_EQUAL(str, expectedStrings[i]);
				i++;
			}
			
		}

		BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_pos)
		{
			auto it = ++list.begin();
			BOOST_CHECK_EQUAL(*it, "Ho-ho-ho");
			list.Erase(it);
			BOOST_CHECK_EQUAL(*++list.begin(), "goodbye");

			list.Erase(list.begin());
			BOOST_CHECK_EQUAL(*list.begin(), "goodbye");

			list.Erase(list.begin());
			BOOST_CHECK(list.IsEmpty());
		}

		BOOST_AUTO_TEST_CASE(have_copy_constructor)
		{
			CStringList list1(list);
			VerifyList(list, expectedStrings);
			VerifyList(list1, expectedStrings);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()