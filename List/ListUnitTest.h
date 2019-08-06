#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/List.h"
#include<list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::list;

namespace UnitTest{
	TEST_CLASS(ListUnitTest) {
	public:
		TEST_METHOD(Init) {
			List<int> l = List<int>();
			Assert::AreEqual(l.size(), 0);

			// [1, 3, 4, 2]
			l.insertAsFirst(1);
			l.insertAsLast(2);
			ListNode<int>* p = l.first();
			l.insertAsSucc(p, 3);
			p = l.last();
			l.insertAsPred(p, 4);
			Assert::AreEqual(l.size(), 4);
			Assert::AreEqual(l[0], 1);
			Assert::AreEqual(l[1], 3);
			Assert::AreEqual(l[2], 4);
			Assert::AreEqual(l[l.size() - 1], 2);

			// [1, 3, 4, 2]
			List<int> l2 = List<int>(l);
			Assert::AreEqual(l2.size(), 4);
			Assert::AreEqual(l2[0], 1);
			Assert::AreEqual(l2[1], 3);
			Assert::AreEqual(l2[2], 4);
			Assert::AreEqual(l2[3], 2);

			// [3, 4]
			List<int> l3 = List<int>(l, 1, 2);
			Assert::AreEqual(l3.size(), 2);
			Assert::AreEqual(l3[0], 3);
			Assert::AreEqual(l3[1], 4);

			// [1, 3, 4]
			p = l.first();
			List<int> l4 = List<int>(p, 3);
			Assert::AreEqual(l4.size(), 3);
			Assert::AreEqual(l4[0], 1);
			Assert::AreEqual(l4[1], 3);
			Assert::AreEqual(l4[2], 4);
		}
		TEST_METHOD(InsertAndRemove) {
			List<int> l = List<int>();

			for (int i = 1; i <= 5; i++) {
				l.insertAsLast(i);
			}
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(l[i], i + 1);
			}
			
			for (int i = 0; i < 4; i++) {
				l.remove(l.first());
			}
			
			Assert::AreEqual(l.size(), 1);
			Assert::AreEqual(l[0], 5);
		}
		TEST_METHOD(Find) {
			// [1, 2, 3, 4, 5]
			List<int> l = List<int>();
			for (int i = 1; i <= 5; i++) {
				l.insertAsLast(i);
			}

			/* basic find */
			// find 1
			Assert::IsNotNull(l.find(1));
			Assert::AreEqual(l.find(1)->data, 1);
			// find 5
			Assert::IsNotNull(l.find(5));
			Assert::AreEqual(l.find(5)->data, 5);
			// find 3
			Assert::IsNotNull(l.find(3));
			Assert::AreEqual(l.find(3)->data, 3);
			// can;t find 6
			Assert::IsNull(l.find(6));

			/* advanced find */
			// 1) find 2
			Assert::IsNull(l.find(2, 0, l.first()));
			// 2) find 1
			Assert::IsNotNull(l.find(1, 4, l.last()));
			Assert::AreEqual(l.find(1, 4, l.last())->data, 1);
			// 3) can't find 1
			Assert::IsNull(l.find(1, 3, l.last()));
		}
		TEST_METHOD(Boolean) {
			List<int> l = List<int>();
			Assert::IsTrue(l.empty());
			l.insertAsLast(1);
			Assert::IsFalse(l.empty());
		}
		TEST_METHOD(Large) {
			List<int> l = List<int>();
			list<int> mask = list<int>();
			int loop = 10;
			int base = 10000;
			for (int i = 1; i <= loop; i++) {
				// insert
				for (int j = 0; j < i * base; j++) {
					l.insertAsLast(j);
					mask.push_back(j);
				}
				// test
				Assert::AreEqual(l.size(), (int)mask.size());
				int size = l.size();
				list<int>::iterator it = mask.begin();
				for (int t = 0; t < size; ) {
					Assert::AreEqual(l[t++], *(it++));
				}
				// remove
				for (int t = 0; t < size - 2; t++) {
					l.remove(l.first());
					mask.erase(mask.begin());
				}

				// test again
				Assert::AreEqual(l.size(), (int)mask.size());
				size = l.size();
				it = mask.begin();
				for (int t = 0; t < size; ) {
					Assert::AreEqual(l[t++], *(it++));
				}
			}
		}
	};
}