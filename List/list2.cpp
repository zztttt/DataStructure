#include <iostream>
#include<list>
#include<assert.h>

using namespace std;
class ListNode {
public:
	int val;
	ListNode* next;
	ListNode(int v) :val(v), next(nullptr) {}
};
class List {
private:
	ListNode* head;
	ListNode* tail;
	int _size;
public:
	List() {
		head = new ListNode(-1);
		tail = head;
		_size = 0;
	}
	int get(int index) {
		if (index > _size - 1)
			return -1;
		ListNode* p = head->next;
		for (int i = 0; i < index; ++i) {
			p = p->next;
		}
		return p->val;
	}
	void insertAsHead(int v) {
		ListNode* cur = new ListNode(v);
		if (_size == 0) {
			head->next = cur;
			tail = cur;
		}
		else {
			cur->next = head->next;
			head->next = cur;
		}
		_size++;
	}
	void insertAsTail(int v) {
		ListNode* cur = new ListNode(v);
		tail->next = cur;
		tail = cur;
		_size++;
	}
	// insert before list[index]
	void insertAtIndex(int index, int v) {
		if (index > _size)
			return;
		else if (index == 0) {
			insertAsHead(v);
			return;
		}
		else if (index == _size) {
			insertAsTail(v);
			return;
		}

		ListNode *p = head->next, *last = head;
		for (int i = 0; i < index; ++i) {
			p = p->next;
			last = last->next;
		}
		ListNode* cur = new ListNode(v);
		last->next = cur;
		cur->next = p;
		_size++;
	}
	void deleteAtIndex(int index) {
		if (index > _size - 1 || index < 0)
			return;
		if (index == _size - 1) {
			ListNode* p = head;
			for (int i = 0; i < index; ++i) {
				p = p->next;
			}
			delete tail;
			tail = p;
			tail->next = nullptr;
		}
		else {
			ListNode *p = head->next, *last = head;
			for (int i = 0; i < index; ++i) {
				p = p->next;
				last = last->next;
			}
			ListNode* del = p;
			last->next = p->next;
			delete del;
		}
		_size--;
	}
	int size() { 
		return _size; 
	}
	ListNode* getHead() { 
		return head; 
	}
};

void check(list<int> a, List b) {
	assert(a.size() == b.size());
	list<int>::iterator it = a.begin();
	ListNode* p = b.getHead()->next;
	while (it != a.end() && p != nullptr) {
		assert(*it == p->val);
		it++;
		p = p->next;
	}
	
	assert(it == a.end());
	assert(p == nullptr);
}
int main(){	
	// init
	list<int> a; a.insert(a.begin(), 1); a.insert(a.end(), 2);
	List b; b.insertAsHead(1); b.insertAsTail(2);
	check(a, b);

	// large
	for (int i = 0; i < 100; ++i) {
		a.insert(a.begin(), i);
		b.insertAtIndex(0, i);

		list<int>::iterator it = a.begin();
		it++;
		a.insert(it, i + 1);
		b.insertAtIndex(1, i + 1);

		it = a.begin();
		it++; it++;
		a.insert(it, i + 2);
		b.insertAtIndex(2, i + 2);

		a.erase(a.begin());
		b.deleteAtIndex(0);
		check(a, b);
	}
	int len = a.size();
	for (int i = 0; i < len; ++i) {
		if (a.size() > 3) {
			list<int>::iterator it = a.begin(); it++; it++;
			a.erase(it);
			b.deleteAtIndex(2);
		}
		else {
			a.erase(a.begin());
			b.deleteAtIndex(0);
		}
		check(a, b);
	}

	cout << "success";
	return 0;
}
