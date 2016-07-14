#ifndef TRANSACCAO
#define TRANSACCAO
#include<iostream>
#include<string>
using namespace std;

class transaccao{
	public:
	string date;
	string time_in;
	string time_out;
	string in;
	string out;
	string tipe;
	float cost;
}op;

void close_dot(){
	ofstream file;
	file.open("graph.dot", ios_base::app);
	file << "}" << endl;
	file.close();
}

#endif
