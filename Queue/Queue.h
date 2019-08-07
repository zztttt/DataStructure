#ifndef QUEUE_H_
#define QUEUE_H_

#include "List.h"

template<class T>
class Queue: public List<T> {
public:
	void enqueue(T const& e);
	T    dequeue();
	T&   front();
};
#endif

template<class T>
void Queue<T>::enqueue(T const & e) {
	insertAsLast(e);
}

template<class T>
T Queue<T>::dequeue() {
	return remove(first());
}

template<class T>
inline T & Queue<T>::front() {
	return first()->data;
}
