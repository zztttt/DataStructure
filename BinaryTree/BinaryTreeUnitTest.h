#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DataStructure/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(BinaryTreeUnitTest) {
	public:
		TEST_METHOD(InitNode) {
			/*
			*          Root
			*         /    \
			*        1      2
			*/
			TreeNode<int> node = TreeNode<int>();
			node.insertAsLeftChild(1);
			node.insertAsRightChild(2);

			Assert::IsTrue(IsRoot(node));
			Assert::IsTrue(HasLChild(node));
			Assert::IsTrue(HasRChild(node));
			Assert::IsTrue(HasChild(node));
			Assert::IsTrue(HasBothChild(node));
			Assert::IsFalse(HasParent(node));
			Assert::IsFalse(IsLeaf(node));

			TreeNode<int>* lc = node.lc;
			TreeNode<int>* rc = node.rc;

			Assert::IsTrue(IsLChild(*lc));
			Assert::IsTrue(IsRChild(*rc));
			Assert::IsTrue(IsLeaf(*lc) && IsLeaf(*rc));

			Assert::AreEqual(sibling(lc)->data, 2);
			Assert::AreEqual(sibling(rc)->data, 1);
			// TODO: how to use FromParentTo
		}

	};
}