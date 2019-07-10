#pragma once
#include <vector>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

class circle_int_sting {
	friend class gauss_code;
private:
	vector<int> s;
	int size;
public:
	circle_int_sting() { size = 0; };
	circle_int_sting(int k) { s.push_back(k);  size = 1; };
	circle_int_sting(vector<int> k) { s = k; size = s.size(); };

	circle_int_sting substring(int ind_s, int ind_f) {
		vector<int> t;
		do {
			t.push_back(s[ind_s % size]);
			++ind_s;
		} while ((ind_s % size + size) % size != (ind_f % size + size) % size);
		return circle_int_sting(t);
	};

	circle_int_sting operator+(circle_int_sting x) {
		vector<int> t = s;
		for (int i = 0; i < x.size; ++i)
			t.push_back(x[i]);
			//t.push_back(x[i] + (x[i] > 0) ? size : -size);
		return circle_int_sting(t);
	}

	int operator[] (int ind) {
		return s[(ind % size + size) % size];
	}


	void print() {
		cout << "Size: " << size << endl;
		for (int i = 0; i < size; ++i)
			cout << s[i] << " ";
		cout << endl;
	}

};