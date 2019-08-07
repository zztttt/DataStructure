#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/Queue.h"
#include<queue>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::queue;

namespace UnitTest {
	TEST_CLASS(QueueUnitTest) {
public:
	TEST_METHOD(Init) {
		Queue<int> q = Queue<int>();
		Assert::AreEqual(q.size(), 0);
	}
	TEST_METHOD(EnqueueAndDequeue) {
		Queue<int> q = Queue<int>();

		// [1, 2, 3, 4, 5]
		for (int i = 0; i < 5; i++) {
			q.enqueue(i + 1);
		}
		Assert::AreEqual(q.size(), 5);

		for (int i = 1; i <= 5; i++) {
			Assert::AreEqual(q.front(), i);
			q.dequeue();
		}
	}
	TEST_METHOD(Large) {
		Queue<int> q = Queue<int>();
		queue<int> mask = queue<int>();

		int loop = 10;
		int base = 10000;
		for (int i = 1; i <= loop; i++) {
			// enqueue
			for (int j = 0; j < i * base; j++) {
				q.enqueue(j);
				mask.push(j);
			}

			// check and pop
			Assert::AreEqual(q.size(), (int)mask.size());
			int size = q.size();
			for (int j = 0; j < size - 2; j++) {
				Assert::AreEqual(q.front(), mask.front());
				q.dequeue();
				mask.pop();
			}

			//check again
			Assert::AreEqual(q.size(), (int)mask.size());
		}
	}
	};
}