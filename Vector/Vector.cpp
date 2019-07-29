#include "Vector.h"
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
Vector<T>::Vector(int c, int s, T v){
	_capacity = c;
	_elem = new T[_capacity];
	for (_size = 0; _size < s; _size++) {
		_elem[_size] = v;
	}
}

template<class T>
Vector<T>::Vector(T const * A, Rank n){
	copyFrom(A, 0, n);
}

template<class T>
Vector<T>::Vector(T const * A, Rank lo, Rank hi){
	copyFrom(A, lo, hi);
}

template<class T>
Vector<T>::Vector(Vector<T> const & V){
	copyFrom(V._elem, 0, V._size);
}

template<class T>
Vector<T>::Vector(Vector<T> const & V, Rank lo, Rank hi){
	copyFrom(V._elem, lo, hi);
}

template<class T>
Vector<T>::~Vector(){
	assert(_elem);
	delete[] _elem;
}

template<class T>
Rank Vector<T>::size() const{
	assert(_size >= 0);
	return _size;
}

template<class T>
bool Vector<T>::empty() const{
	assert(_size >= 0);
	return _size == 0;
}

template<class T>
Rank Vector<T>::find(T const & e) const{
	return find(e, 0, _size);
}

template<class T>
Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const{
	// TODO
}

template<class T>
T& Vector<T>::operator[](Rank r) const{
	// TODO
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const & V){
	// delete original data
	if (_elem)
		delete [] _elem;
	// copy from right Vector
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<class T>
T Vector<T>::remove(Rank r){
	// TODO
}

template<class T>
Rank Vector<T>::insert(T const & e){
	return insert(_size, e);
}

template<class T>
Rank Vector<T>::insert(Rank r, T const & e){
	// TODO
}

template<class T>
void Vector<T>::traverse(){
	// TODO
}


template<class T>
void Vector<T>::copyFrom(T const * A, Rank lo, Rank hi) {
	_capacity = 2 * (hi - lo);
	_elem = new T[_capacity];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template<class T>
void Vector<T>::expand() {
	// TODO
}

template<class T>
void Vector<T>::shrink() {
	// TODO
}
