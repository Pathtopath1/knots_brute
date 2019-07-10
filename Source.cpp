#include "circle_int_string.h"
#include "gauss_code.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	ifstream f_in("knots_gc.txt");
	ofstream f_out("semimeander_cr.txt");	
	//Temp objects
	string knot_name;
	vector<int> knot_gc;
	char c;
	int t;
	gauss_code knot;
	//Main cycle
	while (!f_in.eof()) {		
		f_in >> knot_name;		
		f_in.get(c);
		knot_gc.clear();
		while (c != '\n') {
			f_in >> t;
			knot_gc.push_back(t);
			f_in.get(c);
		}
		knot = gauss_code(knot_gc, knot_name);
		f_out << knot_name << " " << knot.get_size() / 2;
		knot.procedure();
		cout << knot_name << " " << knot.get_size() / 2 << endl;
		f_out << " " << knot.get_size() / 2 << endl;
	}
	f_in.close();
	f_out.close();
	return 0;
}
