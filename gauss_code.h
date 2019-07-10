#pragma once
#include "circle_int_string.h"


using namespace std;

class gauss_code {
private:
	circle_int_sting gc;
	string knot_name;
	int m; //The bigest simple part
	set <int> simple_part;
	int start_ind;
public:
	gauss_code() { m = 0; start_ind = 0; };
	gauss_code(vector<int> str_i, string _name) { circle_int_sting x(str_i); gc = x; find_m(); knot_name = _name; };
	gauss_code(circle_int_sting x) { gc = x; find_m(); };
	
	void find_m() {
		m = 0;
		vector<set<int>> x(gc.size);
		for (int i = 0; i < gc.size; ++i)
			for (int j = 0; j < gc.size; ++j) 
				if ((x[i].find(gc[i + j]) == x[i].end()) && (x[i].find(-gc[i + j]) == x[i].end()))
					x[i].insert(gc[ i + j]);
				else
					break;
		for (int i = 0; i < gc.size; ++i)
			if (x[i].size() > m) {
				start_ind = i;
				m = x[i].size();
				simple_part = x[i];
			}
	}

	pair<vector<int>, pair<int, bool>> find_closest() {
		vector<int> dist;
		bool to_the_end = true;
		int crossing_point = start_ind;
		for (int i = start_ind + m; i < start_ind + m + gc.size; ++i) {
			if ((simple_part.find(gc[i]) == simple_part.end()) && (simple_part.find(-gc[i]) == simple_part.end())) {
				for (int j = start_ind + m; j < i; ++j)
					dist.push_back(gc[j]);
				crossing_point = gc[i];
				break;
			}
		}
		for (int i = start_ind - 1; i > start_ind - gc.size; --i) {
			if ((simple_part.find(gc[i]) == simple_part.end()) && (simple_part.find(-gc[i]) == simple_part.end())) {
				if (dist.size() > start_ind - i) {
					dist.clear();
					for (int j = start_ind - 1; j > i; --j)
						dist.push_back(gc[j]);
					crossing_point = gc[i];
					to_the_end = false;
					break;
				}
			}
		}
		pair < vector<int>, pair<int, bool>> temp{ dist, {crossing_point, to_the_end}};
		return temp;
	}

	void expand_point(vector<int> right_part, int point, vector<int> left_part) {
		int i = 0;
		while (gc[i] != point) { ++i; };
		if (i % gc.size == 0) 
			gc = (circle_int_sting)right_part + point + left_part + gc.substring(i + 1, gc.size);
		else{ if (i % gc.size == gc.size - 1)
				gc = gc.substring(0, i) + right_part + point + left_part;
			else{
				gc = gc.substring(0, i) + right_part + point + left_part + gc.substring(i+1, gc.size);
			}
		}
	}

	void move_point(int ind_from, int ind_to){
		vector <int> x;
		for (int i = 0; i < gc.size; ++i) {
			if (i == (ind_from % gc.size + gc.size) % gc.size)
				continue;
			if (i == (ind_to % gc.size + gc.size) % gc.size)
				x.push_back(gc[ind_from]);
			x.push_back(gc[i]);
		}
		gc.s = x;
}
		
	void procedure() {
		int n = gc.size / 2;
		while (m != n) {
			auto j = find_closest();
			/*cout << "\t" << j.first.size() << endl << "\t" << j.second.first << endl << "\t";
			for (auto e : j.first) {
				cout <<  e << " ";
			}
			cout << endl;*/
			int ind_c = 0;
			while (gc[ind_c] != j.second.first) { ++ind_c; };
			int sgn_j = j.second.first / abs(j.second.first);
			if (j.second.second)
				move_point(ind_c, start_ind + m);
			else
				move_point(ind_c, start_ind);
			//print();
			for (int i = 0; i < j.first.size(); ++i) {
				expand_point({ sgn_j *( n + 2 * i + 1 )}, -j.first[i], { sgn_j *( n + 2 * i + 2 )});
			}
			//print();
			vector <int> right_border, left_border;
			for (int i = 0; i < j.first.size(); ++i) {
				right_border.push_back(-sgn_j*(2 * (j.first.size() - i - 1) + 1 + i % 2 + n));
				left_border.push_back(-sgn_j*(2 * (i) + 1 + (i+1) % 2 + n));

			}
			expand_point(right_border, -j.second.first, left_border);
			find_m();
			//print();
			n = gc.size / 2;
		}
	}

	int get_size() {
		return gc.size;
	}

	void print() {
		cout << "##############################\n";
		cout << "m = " << m << endl;
		cout << "Start index = " << start_ind << endl;
		cout << "Simple part:\n\t";
		for (auto e : simple_part) {
			cout << e << " ";
		}
		cout << endl;
		gc.print();
		cout << "##############################\n";
	}

};