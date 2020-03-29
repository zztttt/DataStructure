#include<iostream>
#include<fstream>
#include <sstream>
#include <string>
#include<map>
#include<vector>
#include<assert.h>

using namespace std;

template<class T>
class ListNode {
public:
	T val;
	ListNode* next;
	ListNode(T v) :val(v), next(nullptr) {}
};

// bucket hash
class Hash {
public:
	int _size;
	int _capacity = 8;
	vector<ListNode<pair<int, int>>*> bucket;
	Hash() {
		_size = 0;
		bucket = vector<ListNode<pair<int, int>>*>(_capacity, new ListNode<pair<int, int>>(pair<int, int>(-1, -1)));
	}
	int hashFunc(int key) {
		return key % _capacity;
	}
	int get(int key) {
		int hashCode = hashFunc(key);
		ListNode<pair<int, int>>* p = bucket[hashCode]->next;

		while (p) {
			pair<int, int> cur = p->val;
			if (cur.first == key) {
				return cur.second;
			}

			p = p->next;
		}
		return -1;
	}
	void put(int key, int val) {
		int hashCode = hashFunc(key);
		ListNode<pair<int, int>> *p = bucket[hashCode]->next, *last = bucket[hashCode];
		while (p) {
			pair<int, int> cur = p->val;
			// update
			if (cur.first == key) {
				p->val.second = val;
				return;
			}
			p = p->next;
			last = last->next;
		}
		// new node
		ListNode<pair<int, int>> *cur = new ListNode<pair<int, int>>(pair<int, int>(key, val));
		last->next = cur;
	}
	void del(int key) {
		int hashCode = hashFunc(key);
		ListNode<pair<int, int>> *p = bucket[hashCode]->next, *last = bucket[hashCode];
		while (p) {
			pair<int, int> cur = p->val;
			// delete
			if (cur.first == key) {
				last->next = p->next;
				delete p;
				return;
			}
			p = p->next;
			last = last->next;
		}
	}

};

void check(string mode) {
	ifstream infile1, infile2;
	infile1.open("data/" + mode + ".ans", ios::in);
	infile2.open("data/" + mode + "res.ans", ios::in);
	assert(infile1.is_open()); 
	assert(infile2.is_open());
	string s1, s2;
	int line = 0;
	while (getline(infile1, s1) && getline(infile2, s2)) {
		line++;
		if (s1 != s2) {
			cout << "line:" << line << endl;
			cout << "s1:" << s1 << " | " << "s2:" << s2 << endl;
			return;
		}
	}
	infile1.close();
	infile2.close();
	cout << mode << " success" << endl;
}
void operate(string mode) {
	//fstream iofile;
//iofile.open("small.in", ios::in | ios::out);
	ifstream infile;
	infile.open("data/" + mode + ".in", ios::in);

	ofstream outfile;
	outfile.open("data/" + mode + "res.ans", ios::out);
	assert(infile.is_open());

	Hash hash;
	map<int, int> m;

	string s;
	while (getline(infile, s)) {
		//cout << s << endl;
		istringstream is(s);
		string type;
		int key, val;
		is >> type;
		if (type == "Set") {
			is >> key >> val;
			hash.put(key, val);
			m[key] = val;
		}
		else if (type == "Get") {
			is >> key;
			val = hash.get(key);
			map<int, int>::iterator it = m.find(key);
			if (val == -1) {
				if (it != m.end()) {
					cout << "line:" << s << endl;
					cout << "expect:" << it->second << ", but get null" << endl;
					return;
				}
			}
			else {
				if (it == m.end()) {
					cout << "line:" << s << endl;
					cout << "expect: null" << ", but get:" << val << endl;
					return;
				}
				if (val != it->second) {
					cout << "line:" << s << endl;
					cout << "expect:" << it->second << ", but get:" << val << endl;
					return;
				}
			}

			if (val == -1)
				outfile << "null" << endl;
			else
				outfile << val << endl;
		}
		else if (type == "Del") {
			is >> key;
			hash.del(key);
			map<int, int>::iterator it = m.find(key);
			if(it != m.end())
				m.erase(it);
		}
	}
	infile.close();
	outfile.close();

	check(mode);
	cout << mode << " finished" << endl;
}
int main() {
	operate("small");
	operate("large");
	return 0;
}