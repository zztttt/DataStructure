#ifndef STACK_H_
#define STACK_H_

#include "Vector.h"

template<class T>
class Stack: public Vector<T> {
public:
	void push(T const& e);
	T    pop();
	T&   top();
};
#endif

template<class T>
void Stack<T>::push(T const & e) {
	insert(size(), e);
}

template<class T>
inline T Stack<T>::pop() {
	return remove(size() - 1);
}

template<class T>
inline T & Stack<T>::top() {
	return (*this)[size() - 1];
}
