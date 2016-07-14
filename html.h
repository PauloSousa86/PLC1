#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "struct.h"
using namespace std;

vector<transaccao> vec;

void make_html(map<int, vector<transaccao> >& meses, float port, float parque){
	ofstream file2;
	string mes_e[] = {"", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
	file2 << "<html><head><meta charset='UTF-8'/></head>" << endl;
	file2 << "<!DOCTYPE html>" << endl;
	file2 << "<html>" << endl;
	file2 << "<body>" << endl;
	file2 << "<center><img src='grafo.png' alt='Grafo' text-align=\"middle\"></center>" << endl;
	file2 << "<center><p><b>Total gasto em portagens: " << port << "</center></p></b>" << endl;
	file2 << "<center><p><b>Total gasto em parques de estacionamento: " << parque << "</center></p></b>" << endl;
	for(int b=1; b < 13; b++){
		float port_mes=0,parque_mes=0; 
		vec = meses[b];
		if(vec.size() != 0){
			file2 << "<p></p>" << endl;
			file2 << "<p><style>" << endl;
			file2 << "table, th, td { border: 1px solid black; border-collapse: collapse;}" << endl;
			file2 << "th, td {padding: 5px;}" << endl;
			file2 << "</style>" << endl;
			file2 << "<center><table style=\"width:80%\">" << endl;
			file2 << "<b><th bgcolor=\"#0D4074\", colspan=\"7\"><center>" << mes_e[b] << "</center></b></th>" << endl; 
			file2 << "<tr><th>Data</th><th>Hora de entrada</th><th>Local de entrada</th><th>Hora de saida</th><th>Local de saida</th><th>Tipo</th><th>Importância</th></tr>" << endl;
			for(int i=0; i < vec.size(); i++){
				file2 << "<tr><td>" << vec[i].date << "</td>";
				file2 << "<td>" << vec[i].time_in << "</td>";
				file2 << "<td>" << vec[i].in << "</td>";
				file2 << "<td>" << vec[i].time_out << "</td>";
				file2 << "<td>" << vec[i].out << "</td>";
				file2 << "<td>" << vec[i].tipe << "</td>";
				file2 << "<td>" << vec[i].cost << "</td></tr></center>" << endl;
				if(vec[i].tipe == "Portagens"){
					port_mes += vec[i].cost;
				}
				else{
					parque_mes += vec[i].cost;
				} 
			}
		
	

	file2 << "<tr><td colspan=\"6\"><b><center>Total gasto em portagens</b></center></td><td>" << port_mes << "</tr></center>" << endl;
	file2 << "<center><tr><td colspan=\"6\"><b><center>Total gasto em parques</b></center></td><td>" << parque_mes << "</tr></center></p>" << endl;
		}
	}

	file2 << "</body>" << endl;
	file2 << "</html>" << endl;

}
