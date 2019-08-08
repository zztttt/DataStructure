#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include<assert.h>
#include<algorithm>

using std::max;

#define stature(p) ((p)? (p)->height : -1)

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lc ) )
#define IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rc ) )
#define HasParent(x) ( !IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLeaf(x) ( !HasChild(x) )

#define sibling(p) \
	( IsLChild( *(p) )? (p)->parent->rc:(p)->parent->lc )
#define uncle(x) \
	( IsLChild( *((x)->parent))? \
		(x)->parent->parent->rc: \
		(x)->parent->parent->lc )
#define FromParentTo(x)\
	( IsRoot(x)? _root: \
	             (IsLChild(x)? (x).parent->lc: \
                               (x).parent->rc) )

enum RBColor {
	RB_RED, 
	RB_BLACK
};

template<class T>
class TreeNode {
public:
	T data;
	TreeNode<T>* parent;
	TreeNode<T>* lc;
	TreeNode<T>* rc;
	int height;
	int npl;// null path length
	RBColor color;

	/* constructor */
	TreeNode():
		parent(NULL), lc(NULL), rc(NULL), 
		height(0), npl(1), color(RB_RED) {}

	TreeNode(T e, TreeNode<T>* p = NULL, 
			TreeNode<T>* lc = NULL, TreeNode<T>* rc = NULL,
			int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	
	/* interface */
	int size();
	TreeNode<T>* insertAsLeftChild(T const& e);
	TreeNode<T>* insertAsRightChild(T const& e);
	TreeNode<T>* succ();
	
	/* overload */
	bool operator< (TreeNode const& node);
	bool operator== (TreeNode const& node);
};

template<class T>
class Tree {
protected:
	int _size;
	TreeNode<T>* _root;
	virtual int updateHeight(TreeNode<T>* x);
	void updateHeightAbove(TreeNode<T>* x);
public:
	Tree();
	~Tree();
	int size() const;
	bool empty() const;
	TreeNode<T>* getRoot() const;

	TreeNode<T>* insertAsRoot(T const& e);
	TreeNode<T>* insertAsLeftChild(TreeNode<T>* x, T const& e);
	TreeNode<T>* insertAsRightChild(TreeNode<T>* x, T const& e);
	TreeNode<T>* attachAsLeftChild(TreeNode<T>* x, Tree<T>* &T);
	TreeNode<T>* attachAsRightChild(TreeNode<T>* x, Tree<T>* &T);
	int remove(TreeNode<T>* x);

	Tree<T>* secede(TreeNode<T>* x);
};
#endif
/*-------------------------------------------------------*/
/*----------------------TreeNode-------------------------*/

template<class T>
TreeNode<T>* TreeNode<T>::insertAsLeftChild(T const & e) {
	return lc = new TreeNode(e, this);
}

template<class T>
TreeNode<T>* TreeNode<T>::insertAsRightChild(T const & e) {
	return rc = new TreeNode(e, this);
}

template<class T>
bool TreeNode<T>::operator<(TreeNode const & node) {
	return data < node.data;
}

template<class T>
bool TreeNode<T>::operator==(TreeNode const & node) {
	return data == node.data;
}

/*--------------------------------------------------------*/
/*-----------------------Tree-----------------------------*/

template<class T>
inline int Tree<T>::updateHeight(TreeNode<T>* x) {
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<class T>
inline void Tree<T>::updateHeightAbove(TreeNode<T>* x) {
	while (x) {
		updateHeight(x);
		x = x->parent;
	}
}

template<class T>
inline Tree<T>::Tree() {
	_size = 0;
	_root = NULL;
}

template<class T>
inline Tree<T>::~Tree() {
	if (0 < _size)
		remove(_root);
}

template<class T>
inline int Tree<T>::size() const {
	return _size;;
}

template<class T>
inline bool Tree<T>::empty() const {
	return !_root;
}

template<class T>
inline TreeNode<T>* Tree<T>::getRoot() const {
	return _root;
}

template<class T>
inline TreeNode<T>* Tree<T>::insertAsRoot(T const & e) {
	_size = 1;
	_root = new TreeNode<T>(e);
	return _root;
}

template<class T>
inline TreeNode<T>* Tree<T>::insertAsLeftChild(TreeNode<T>* x, T const & e) {
	
	_size++;
	x->insertAsLeftChild(e);
	updateHeightAbove(x);
	return x->lc;
}

template<class T>
inline TreeNode<T>* Tree<T>::insertAsRightChild(TreeNode<T>* x, T const & e) {
	_size++;
	x->insertAsRightChild(e);
	updateHeightAbove(x);
	return x->rc;
}

/*
* Usage: add tree t as the node x's left child.
*        it requires x->lc == NULL
* return 
*/
template<class T>
inline TreeNode<T>* Tree<T>::attachAsLeftChild(TreeNode<T>* x, Tree<T>*& t) {
	// 不懂为啥要这么写。。。 TODO
	if (x->lc = t->_root)
		x->lc->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	t->_root = NULL;
	t->_size = 0;
	//release(t);
	// avoid wild pointer
	t = NULL;
	return x;
}

template<class T>
inline TreeNode<T>* Tree<T>::attachAsRightChild(TreeNode<T>* x, Tree<T>*& t) {
	if (x->rc = t->_root)
		x->rc->parent = x;
	_size += t->_size;
	updateHeightAbove(x);
	t->_root = NULL;
	t->_size = 0;
	//release(t);
	t = NULL;
	return x;
}

/*
* Usage: remove TreeNode* x in the tree
* return the number of node of the subtree
*/
template<class T>
inline int Tree<T>::remove(TreeNode<T>* x) {
	// (*x).parent->l/rc = NULL
	// cut the line: parent->lc = x
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size = _size - n;
	return n;
}

/*-----------------------------------------------*/
/*-------------------Untility--------------------*/

/*
* Usage: remove TreeNode x and its heirs
* return the number of deleted nodes
*/
template<class T>
static int removeAt(TreeNode<T>* x) {
	if (!x)
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	//release(x->data);
	//release(x);
	return n;
}
