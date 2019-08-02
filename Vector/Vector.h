#ifndef VECTOR_H_
#define VECTOR_H_

#include<iostream>
#include<assert.h>

#define Rank int
#define DEFAULT_CAPACITY 3

template<class T>
class Vector {
public:
	/* constructor */
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0);
	Vector(T const* A, Rank n);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	Vector(Vector<T> const& V, Rank lo, Rank hi);

	/* deconstructor */
	~Vector();

	/* read-only interface */
	Rank size() const;
	bool empty() const;
	Rank find(T const& e) const;
	Rank find(T const& e, Rank lo, Rank hi) const;

	/* writable interface */
	T& operator[] (Rank r) const;
	Vector<T> & operator= (Vector<T> const&);
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	Rank insert(T const& e);
	Rank insert(Rank r, T const& e);

	/* travesing */
	void traverse(void(*visit) (T&));

	template<class VST> void traverse(VST& visit);

protected:
	Rank _size;
	int _capacity;
	T* _elem;

	void copyFrom(T const*A, Rank lo, Rank hi);
	void expand();
	void shrink();

	/*bool bubble(Rank lo, Rank hi);
	void bubbleSort(Rank lo, Rank hi);
	Rank max(Rank lo, Rank hi);
	void selectonSort();*/
};

#endif

/*
* Usage: param(int, int, T)
* no value return
*/
template<class T>
Vector<T>::Vector(int c, int s, T v) {
	_capacity = c;
	_elem = new T[_capacity];
	for (_size = 0; _size < s; _size++) {
		_elem[_size] = v;
	}
}

/*
* Usage: param(T*, Rank)
* no value return
*/
template<class T>
Vector<T>::Vector(T const * A, Rank n) {
	copyFrom(A, 0, n);
}

/*
* Usage: param(T const*, Rank, Rank)
* no value return
*/
template<class T>
Vector<T>::Vector(T const * A, Rank lo, Rank hi) {
	copyFrom(A, lo, hi);
}

/*
* Usage: param(Vector<T> const&)
* no value return
*/
template<class T>
Vector<T>::Vector(Vector<T> const & V) {
	copyFrom(V._elem, 0, V._size);
}

/*
* Usage: param(Vector<T> const&, Rank, Rank)
* no value return
*/
template<class T>
Vector<T>::Vector(Vector<T> const & V, Rank lo, Rank hi) {
	copyFrom(V._elem, lo, hi);
}

/*
* Usage: deconstructor
* no value return
*/
template<class T>
Vector<T>::~Vector() {
	assert(_elem);
	delete[] _elem;
}

/*
* Usage: get the size of Vector
* return _size
*/
template<class T>
Rank Vector<T>::size() const {
	assert(_size >= 0);
	return _size;
}

/*
* Usage: get whether this Vector is empty
* return true  if _size = 0
*        false if _size > 0
*/
template<class T>
bool Vector<T>::empty() const {
	assert(_size >= 0);
	return _size == 0;
}

/*
* Usage: find element e in Vector
* return t(V[t]=e) if succeed
*        -1        if fail
*/
template<class T>
Rank Vector<T>::find(T const & e) const {
	return find(e, 0, _size);
}

/*
* Usage: find the element from [ V[lo], V[hi] ), excluding V[hi]
* return t(V[t]=e) if succeed
*        lo-1	   if fail
*/
template<class T>
Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const {
	assert(0 <= lo < hi <= _size);
	while (lo < hi-- && e != _elem[hi]);
	return hi;
}

/*
* Usage: overload [], get V[r]
* return V[r]
*/
template<class T>
T& Vector<T>::operator[](Rank r) const {
	assert(r <= _size - 1 && r >= 0);
	return _elem[r];
}

/*
* Usage: overload =, Vdst = Vsrc
* return Vdst
*/
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const & V) {
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}

/*
* Usage: remove element V[r]
* return V[r]
*/
template<class T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

/*
* Usage: remove elements from V[lo] to V[hi-1]
* return the number of removed element
*/
template<class T>
int Vector<T>::remove(Rank lo, Rank hi) {
	assert(0 <= lo < hi <= _size - 1);
	int ret = 0;
	if (hi == lo)
		return 0;
	int num = hi - lo;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return num;
}

/*
* Usage: insert a new element at V[_size], in other words, at the tail
* return t(V[t]=e)
*/
template<class T>
Rank Vector<T>::insert(T const& e) {
	return insert(_size, e);
}

/*
* Usage: insert a new element at V[r]
* return r
*/
template<class T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();

	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	++_size;
	return r;
}

/*
* Usage: using the Function Pointer to travese the Vector
* no value return
*/
template<class T>
void Vector<T>::traverse(void(*visit)(T &)) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

/*
* Usage: using the Function Object to travese the Vector
* no value return
*/
template<class T>
template<class VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

/*
* Usage: copy T[...] from T[lo] to T[hi-1]
* no value return
*/
template<class T>
void Vector<T>::copyFrom(T const * A, Rank lo, Rank hi) {
	_capacity = 2 * (hi - lo);
	_elem = new T[_capacity];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

/*
* Usage: expand the capacity when _size = _capacity
* no value return
*/
template<class T>
void Vector<T>::expand() {
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_capacity = _capacity << 1;
	_elem = new T[_capacity];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

/*
* Usage: shrink when capacity > DEFAULT and _size * 4 < capacity
* no value return
*/
template<class T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1)
		return;
	if (_size << 2 > _capacity)
		return;
	T* oldElem = _elem;
	_capacity = _capacity >> 1;
	_elem = new T[_capacity];
	delete[] oldElem;
}
