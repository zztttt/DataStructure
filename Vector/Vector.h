#ifndef VECTOR_H_
#define VECTOR_H_

#define Rank int
#define DEFAULT_CAPACITY 3

template<class T>
class Vector{
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
	Rank insert(T const& e);
	Rank insert(Rank r, T const& e);

	/* travesing */
	void traverse();

	template<class VST>
	void traverse(VST&);//using function object, can be modified globally

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

template<class T>
template<class VST>
inline void Vector<T>::traverse(VST &)
{
}
