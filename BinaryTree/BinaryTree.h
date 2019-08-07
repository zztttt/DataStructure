#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include<assert.h>

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
	             (IsLChild(x)? (x).parent->lc:(x)->parent->lc) )

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
#endif
/*-------------------------------------------------------*/
/*----------------------TreeNode-------------------------*/


template<class T>
inline int TreeNode<T>::size() {
	assert(0);
	//TODO
	return 0;
}

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