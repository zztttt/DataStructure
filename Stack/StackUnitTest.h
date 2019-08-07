#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/Stack.h"
#include<stack>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::stack;

namespace UnitTest {
	TEST_CLASS(StackUnitTest) {
	public:
		TEST_METHOD(Init) {
			Stack<int> s = Stack<int>();
			Assert::AreEqual(s.size(), 0);
		}
		TEST_METHOD(PushAndPop) {
			Stack<int> s = Stack<int>();

			// [1, 2, 3, 4, 5]
			for (int i = 0; i < 5; i++) {
				s.push(i + 1);
			}
			Assert::AreEqual(s.size(), 5);

			for (int i = 5; i > 0; i--) {
				Assert::AreEqual(s.top(), i);
				s.pop();
			}
		}
		TEST_METHOD(Large) {
			Stack<int> s = Stack<int>();
			stack<int> mask = stack<int>();

			int loop = 10;
			int base = 10000;
			for (int i = 1; i <= loop; i++) {
				// push
				for (int j = 0; j < i * base; j++) {
					s.push(j);
					mask.push(j);
				}

				// check and pop
				Assert::AreEqual(s.size(), (int)mask.size());
				int size = s.size();
				for (int j = 0; j < size - 2; j++) {
					Assert::AreEqual(s.top(), mask.top());
					s.pop();
					mask.pop();
				}

				//check again
				Assert::AreEqual(s.size(), (int)mask.size());
			}
		}
	};
}