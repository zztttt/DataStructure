#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/Vector.h"
#include<vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

namespace UnitTest{		
	TEST_CLASS(VectorUnitTest){
	public:
		Vector<int> v;

		TEST_METHOD(Init){
			// [1, 2, 3, 4, 5]
			int* t1 = new int[5];
			for (int i = 0; i < 5; i++) {
				t1[i] = i + 1;
			}
			// [ ]
			v = Vector<int>();
			Assert::AreEqual(v.size(), 0);
			
			// [1, 2, 3]
			v = Vector<int>(t1, 3);
			Assert::AreEqual(v.size(), 3);
			Assert::AreEqual(v[0], 1);
			Assert::AreEqual(v[1], 2);
			Assert::AreEqual(v[2], 3);

			// [2, 3, 4, 5]
			v = Vector<int>(t1, 1, 5);
			Assert::AreEqual(v.size(), 4);
			Assert::AreEqual(v[0], 2);
			Assert::AreEqual(v[1], 3);
			Assert::AreEqual(v[2], 4);
			Assert::AreEqual(v[3], 5);

			// [2, 3, 4, 5]
			Vector<int> v2 = Vector<int>(v);
			Assert::AreEqual(v.size(), 4);
			Assert::AreEqual(v2[0], 2);
			Assert::AreEqual(v2[1], 3);
			Assert::AreEqual(v2[2], 4);
			Assert::AreEqual(v2[3], 5);

			// [3, 4]
			Vector<int> v3 = Vector<int>(v2, 1, 3);
			Assert::AreEqual(v3.size(), 2);
			Assert::AreEqual(v3[0], 3);
			Assert::AreEqual(v3[1], 4);

			delete[] t1;
		}
		TEST_METHOD(InsertAndRemove) {
			Assert::AreEqual(v.size(), 0);
			// init
			int* t1 = new int[5];
			for (int i = 0; i < 5; i++) {
				t1[i] = i + 1;
			}
			v = Vector<int>(t1, 5);

			// insert
			// [9, 1, 2, 3, 4, 5, 8, 6, 7]
			v.insert(6);
			v.insert(7);
			v.insert(5, 8);
			v.insert(0, 9);
			Assert::AreEqual(v.size(), 9);
			Assert::AreEqual(v[0], 9);
			Assert::AreEqual(v[6], 8);
			Assert::AreEqual(v[7], 6);
			Assert::AreEqual(v[8], 7);

			// remove
			v.remove(0, 1);
			Assert::AreEqual(v.size(), 8);
			v.remove(1, 2);
			Assert::AreEqual(v.size(), 7);
			v.remove(4, 6);
			Assert::AreEqual(v.size(), 5);

			Assert::AreEqual(v[0], 1);
			Assert::AreEqual(v[1], 3);
			Assert::AreEqual(v[2], 4);
			Assert::AreEqual(v[3], 5);
			Assert::AreEqual(v[4], 7);

			delete[] t1;
		}
		TEST_METHOD(Boolean) {
			Assert::IsTrue(v.empty());
			v.insert(5);
			Assert::IsFalse(v.empty());
		}
		TEST_METHOD(Find) {
			int* t1 = new int[5];
			for (int i = 0; i < 5; i++) {
				t1[i] = i + 1;
			}
			v = Vector<int>(t1, 5);

			// [1, 2, 3, 4, 5]
			Assert::AreEqual(v.find(1), 0);
			Assert::AreEqual(v.find(2, 1, 3), 1);
			Assert::AreEqual(v.find(3), 2);
			Assert::AreEqual(v.find(4, 3, 4), 3);
			Assert::AreEqual(v.find(5), 4);

			Assert::AreEqual(v.find(6), -1);
			Assert::AreEqual(v.find(6, 1, 3), 0);
			Assert::AreEqual(v.find(1, 2, 4), 1);
			Assert::AreEqual(v.find(5, 0, 3), -1);
		}
		TEST_METHOD(Large) {
			// check init
			v = Vector<int>();
			vector<int> mask = vector<int>();
			Assert::AreEqual(v.size(), (int)mask.size());

			// loop operation
			int loop = 10;
			int base = 10000;
			for (int i = 1; i <= loop; i++) {
				// insert
				for (int j = 0; j < i * base; j++) {
					v.insert(j);
					mask.push_back(j);
				}
				Assert::AreEqual(v.size(), (int)mask.size());
				int size = v.size();
				for (int q = 0; q < size; q++) {
					Assert::AreEqual(v[q], mask[q]);
				}
				// remove 
				for (int k = 0; k < i * base - 1; k++) {
					Assert::AreEqual(v[0], mask[0]);
					v.remove(0);
					mask.erase(mask.begin());
				}
				Assert::AreEqual(v.size(), (int)mask.size());
			}

			// check valid
			Assert::AreEqual(v.size(), (int)mask.size());
			int size = v.size();
			for (int i = 0; i < size; i++) {
				Assert::AreEqual(v[i], mask[i]);
			}
		}
	};
}