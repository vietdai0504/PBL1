#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
class Points {
private:
	double gt,av,vlbd,oop,vl2,pbl;
	int tc;
public:
	void getFull(ifstream &fin) {
		string str, x;
		getline(fin,str);
		stringstream ss(str);
		getline(ss,x,',');
		stringstream(x) >> gt;
		getline(ss,x,',');
		stringstream(x) >> av;
		getline(ss,x,',');
		stringstream(x) >> vlbd;
		getline(ss,x,',');
		stringstream(x) >> oop;
		getline(ss,x,',');
		stringstream(x) >> vl2;
		getline(ss,x,',');
		stringstream(x) >> pbl;
		getline(ss,x,',');
		stringstream(x) >> tc;
	}
	double getGt() {
		return gt;
	}
	double getAv() {
		return av;
	}
	double getVlbd() {
		return vlbd;
	}
	double getoop() {
		return oop;
	}
	double getVl2() {
		return vl2;
	}
	double getPbl() {
		return pbl;
	}
	double getgpa() {
		return (gt + av + vlbd + oop + vl2 + pbl)/6;
	}
	int gettc() {
		return tc;
	}
};
