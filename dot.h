#include <map>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void make_dot(map<string, map<string, int> >& trajeto){
	map<string, int> traj;
	ofstream file;
        file.open ("graph.dot");
       	file << "digraph G {" << endl;
        for(map<string, map<string, int> >::iterator it=trajeto.begin(); it !=trajeto.end(); ++it){
                traj = it->second;
                for(map<string, int>::iterator it2=traj.begin(); it2 !=traj.end(); ++it2){
                        file <<"\"" <<it->first << "\""<< "->" << "\""<< it2->first << "\""<< " [label=" << it2->second << "];"  << endl;
                }
        }
        file << "}" << endl;
        file.close();
}
