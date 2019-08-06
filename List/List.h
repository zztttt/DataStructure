#ifndef LIST_H_
#define LIST_H_
#include<assert.h>
#define Rank int

template<class T>
class ListNode {
public:
	T data;
	ListNode<T>* pred;
	ListNode<T>* succ;

	ListNode() {};
	ListNode(T e, ListNode<T>* p = NULL, ListNode<T>* s = NULL):
		 data(e), pred(p), succ(s){}

	/* interface */
	ListNode<T>* insertAsPred(T const& e);
	ListNode<T>* insertAsSucc(T const& e);
};

template<class T>
class List {
private:
	int _size;
	ListNode<T>* head;
	ListNode<T>* tail;
protected:
	void init();
	int clear();
	void copyNodes(ListNode<T>* p, int n);
	void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int);
public:
	/* constructor */
	List();
	List(List<T> const& L);
	List(List<T> const& L, Rank r, int n);
	List(ListNode<T>* p, int n);

	/* deconstructor */
	~List();

	/* read-only interface */
	Rank size() const;
	bool empty() const;
	T& operator[](Rank r)const;
	ListNode<T>* first() const;
	ListNode<T>* last() const;
	bool valid(ListNode<T>* p);
	ListNode<T>* find(T const& e) const;
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;

	/* writable interface */
	ListNode<T>* insertAsFirst(T const& e);
	ListNode<T>* insertAsLast(T const& e);
	ListNode<T>* insertAsPred(ListNode<T>* p, T const& e);
	ListNode<T>* insertAsSucc(ListNode<T>* p, T const& e);
	T remove(ListNode<T>* p);

	/* traverse */
	void traverse(void(*) (T&));
	template<class VST>
	void traverse(VST&);
};
#endif

//=============================================
//----------------ListNode---------------------
template<class T>
ListNode<T>* ListNode<T>::insertAsPred(T const & e) {
	ListNode<T>* cur = new ListNode(e, pred, this);
	pred->succ = cur;
	//(pred = cur) == (this->pred = cur)
	pred = cur;
	return cur;
}

template<class T>
ListNode<T>* ListNode<T>::insertAsSucc(T const & e) {
	ListNode<T>* cur = new ListNode(e, this, succ);
	succ->pred = cur;
	succ = cur;
	return cur;
}

//==============================================
//---------------------List---------------------
template<class T>
inline void List<T>::init() {
	head = new ListNode<T>;
	tail = new ListNode<T>;
	head->pred = NULL;
	head->succ = tail;
	tail->pred = head;
	tail->succ = NULL;
	_size = 0;
}

/*
* Usage: clear the list
* return _size
*/
template<class T>
inline int List<T>::clear() {
	int oldSize = _size;
	for (int i = 0; i < _size; i++) {
		remove(head->succ);
	}
	return oldSize;
}

/*
* Usage: copy [ List2[p], List2[p+n] ] in current List
* no return 
*/
template<class T>
void List<T>::copyNodes(ListNode<T>* p, int n) {
	assert(n > 0);
	init();
	for (int i = 0; i < n; i++) {
		insertAsLast(p->data);
		p = p->succ;
	}
}

/*
* Usage: param()
* no return
*/
template<class T>
List<T>::List() {
	init();
}

/*
* Usage: param(List<T>& L)
* no return
*/
template<class T>
List<T>::List(List<T> const & L) {
	copyNodes(L.first(), L.size());
}

/*
* WARNING: BUG! 
* L[r] equals to the value stored in Rank r p, but not the pointer
*/
template<class T>
List<T>::List(List<T> const & L, Rank r, int n) {
	// the wrong code provided by original book
	// copyNodes(L[r], n);

	// my correct code
	assert(0 <= r);
	assert(0 < n);
	assert(r < L.size());
	assert(n <= L.size() - r);
	ListNode<T>* p = L.first();
	for (int i = 0; i < r; i++) {
		p = p->succ;
	}
	copyNodes(p, n);
}

template<class T>
List<T>::List(ListNode<T>* p, int n) {
	copyNodes(p, n);
}

template<class T>
inline List<T>::~List() {
	clear();
	delete head;
	delete tail;
}

template<class T>
inline Rank List<T>::size() const {
	assert(_size >= 0);
	return _size;
}

template<class T>
inline bool List<T>::empty() const {
	assert(_size >= 0);
	return _size == 0;
}

/*
* Usage: get the i.th element from List
* return List[i]
*/
template<class T>
T & List<T>::operator[](Rank r) const {
	assert(0 <= r);
	assert(r < _size);
	ListNode<T>* p = first();
	for (int i = 0; i < r; i++) {
		p = p->succ;
	}
	return p->data;
}

template<class T>
inline ListNode<T>* List<T>::first() const {

	return head->succ;
}

template<class T>
inline ListNode<T>* List<T>::last() const {
	return tail->pred;
}

template<class T>
inline bool List<T>::valid(ListNode<T>* p) {
	return p && (tail != p) && (head != p);
}

template<class T>
inline ListNode<T>* List<T>::find(T const & e) const {
	return find(e, _size, tail);
}

/*
* Usage: find e in [p - n, p)
* return 
*/
template<class T>
ListNode<T>* List<T>::find(T const & e, int n, ListNode<T>* p) const {
	assert(0 <= n);
	assert(n <= _size);
	for (int i = 0; i < n; i++) {
		p = p->pred;
		if (e == p->data)
			return p;
	}
	return NULL;
}

/*
* Usage: insert e as the first element in List
* return &List[0]
*/
template<class T>
ListNode<T>* List<T>::insertAsFirst(T const & e) {
	_size++;
	return head->insertAsSucc(e);
}

/*
* Usage: insert e as the last element in List
* return &List[size() - 1]
*/
template<class T>
ListNode<T>* List<T>::insertAsLast(T const & e) {
	_size++;
	return tail->insertAsPred(e);
}

/*
* Usage: insert e as the pred of p
* return inserted ListNode*
*/
template<class T>
ListNode<T>* List<T>::insertAsPred(ListNode<T>* p, T const & e) {
	_size++;
	return p->insertAsPred(e);
}

/*
* Usage: insert e as the succ of p
* return inserted ListNode*
*/
template<class T>
ListNode<T>* List<T>::insertAsSucc(ListNode<T>* p, T const & e) {
	_size++;
	return p->insertAsSucc(e);
}

/*
* Usage: remove ListNode p
* return *p
*/
template<class T>
T List<T>::remove(ListNode<T>* p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}
