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
		}
		TEST_METHOD(InitTree) {
			/*              1
			*            2      3
			*          4   5  6   7
			*
			*/
			Tree<int> tree = Tree<int>();
			Assert::AreEqual(tree.size(), 0);
			Assert::IsTrue(tree.empty());

			tree.insertAsRoot(1);
			Assert::IsFalse(tree.empty());

			TreeNode<int>* root = tree.getRoot();
			tree.insertAsLeftChild(root, 2);
			tree.insertAsRightChild(root, 3);
			Assert::AreEqual(tree.size(), 3);
			tree.insertAsLeftChild(root->lc, 4);
			tree.insertAsRightChild(root->lc, 5);
			tree.insertAsLeftChild(root->rc, 6);
			tree.insertAsRightChild(root->rc, 7);

			// check size and height
			Assert::AreEqual(tree.size(), 7);
			Assert::AreEqual(root->height, 2);
			Assert::AreEqual(root->lc->height, 1);
			Assert::AreEqual(root->rc->height, 1);
			Assert::AreEqual(root->lc->rc->height, 0);
			Assert::AreEqual(root->rc->lc->height, 0);

			// check value
			TreeNode<int> mask1 = TreeNode<int>(1);
			TreeNode<int> mask2 = TreeNode<int>(2);
			TreeNode<int> mask3 = TreeNode<int>(3);
			TreeNode<int> mask4 = TreeNode<int>(4);
			TreeNode<int> mask5 = TreeNode<int>(5);
			TreeNode<int> mask6 = TreeNode<int>(6);
			TreeNode<int> mask7 = TreeNode<int>(7);
			Assert::IsTrue(*root == mask1);
			Assert::IsTrue(*root->lc == mask2);
			Assert::IsTrue(*root->rc == mask3);
			Assert::IsTrue(*root->lc->lc == mask4);
			Assert::IsTrue(*root->lc->rc == mask5);
			Assert::IsTrue(*root->rc->lc == mask6);
			Assert::IsTrue(*root->rc->rc == mask7);
		}
		TEST_METHOD(InsertAndRemove) {
			/*              1
			*            2      3
			*          4   5  6   7
			*
			*/
			// init
			Tree<int> tree = Tree<int>();
			tree.insertAsRoot(1);
			TreeNode<int>* root = tree.getRoot();
			tree.insertAsLeftChild(root, 2);
			tree.insertAsRightChild(root, 3);
			Assert::AreEqual(tree.size(), 3);
			tree.insertAsLeftChild(root->lc, 4);
			tree.insertAsRightChild(root->lc, 5);
			tree.insertAsLeftChild(root->rc, 6);
			tree.insertAsRightChild(root->rc, 7);

			// remove
			/* after remove
			*              1
			*            2
			*/
			Assert::AreEqual(tree.remove(root->lc->lc), 1);
			Assert::AreEqual(tree.remove(root->lc->rc), 1);
			Assert::AreEqual(tree.remove(root->rc), 3);
			Assert::AreEqual(root->height, 1);
			Assert::AreEqual(root->lc->height, 0);
			Assert::IsNull(root->rc);
			Assert::AreEqual(tree.size(), 2);

			// insert again
			tree.insertAsRightChild(root, 3);
			tree.insertAsLeftChild(root->lc, 4);
			tree.insertAsRightChild(root->lc, 5);
			tree.insertAsLeftChild(root->rc, 6);
			tree.insertAsRightChild(root->rc, 7);

			// check again
			// check size and height
			Assert::AreEqual(tree.size(), 7);
			Assert::AreEqual(root->height, 2);
			Assert::AreEqual(root->lc->height, 1);
			Assert::AreEqual(root->rc->height, 1);
			Assert::AreEqual(root->lc->rc->height, 0);
			Assert::AreEqual(root->rc->lc->height, 0);

			// check value
			TreeNode<int> mask1 = TreeNode<int>(1);
			TreeNode<int> mask2 = TreeNode<int>(2);
			TreeNode<int> mask3 = TreeNode<int>(3);
			TreeNode<int> mask4 = TreeNode<int>(4);
			TreeNode<int> mask5 = TreeNode<int>(5);
			TreeNode<int> mask6 = TreeNode<int>(6);
			TreeNode<int> mask7 = TreeNode<int>(7);
			Assert::IsTrue(*root == mask1);
			Assert::IsTrue(*root->lc == mask2);
			Assert::IsTrue(*root->rc == mask3);
			Assert::IsTrue(*root->lc->lc == mask4);
			Assert::IsTrue(*root->lc->rc == mask5);
			Assert::IsTrue(*root->rc->lc == mask6);
			Assert::IsTrue(*root->rc->rc == mask7);
		}
		TEST_METHOD(Large) {
			Tree<int> tree = Tree<int>();
			tree.insertAsRoot(1);
			TreeNode<int>* root = tree.getRoot();
			TreeNode<int>* p = root;

			int loop = 10;
			int base = 1000;
			for (int i = 1; i <= loop; i++) {
				// insert
				for (int j = 0; j < i*base; j++) {
					while (!IsLeaf(*p)) {
						p = HasLChild(*p) ? p->lc : p->rc;
					}
					tree.insertAsLeftChild(p, j);
				}

				// check
				Assert::AreEqual(tree.size(), i*base + 1);

				// remove
				p = root;
				for (int j = 0; j < i*base; j++) {
					while (!IsLeaf(*p)) {
						p = HasLChild(*p) ? p->lc : p->rc;
					}
					tree.remove(p);
				}

				// check again
				Assert::AreEqual(tree.size(), 1);
			}
		}
	};
}