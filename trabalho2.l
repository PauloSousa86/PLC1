%{
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "dot.h"
#include "html.h"
#include "struct.h"
using namespace std;


float conta=0;
float conta2=0;
float port=0, parque=0;

string origem;
string destino;
map<string, map<string, int> > trajeto;
map<int, vector<transaccao> > meses;

%}

Decimal [0-9]*\,[0-9]+
%x ACCAO
%x TIPO ENTRADA SAIDA DATA HORA_IN HORA_OUT 

%%

                        int i,j;
			string mes;
                        float a=0,b=0;
			
 

(?i:<data_entrada>)						BEGIN(DATA);
(?i:<hora_entrada>)       					BEGIN(HORA_IN);
(?i:<hora_saida>)       					BEGIN(HORA_OUT);
(?i:<entrada>)          					BEGIN(ENTRADA);
(?i:<saida>)            					BEGIN(SAIDA);
(?i:<importancia>)						BEGIN(ACCAO);
(?i:<tipo>)             					BEGIN(TIPO);

.|\n                   						 { ; }


<DATA>[0-9]{2}\-[0-9]{2}\-[0-9]{4} 				{op.date = yytext;  mes.push_back(yytext[3]); mes.push_back(yytext[4]) ; istringstream(mes) >> j;}
<DATA>"</DATA_ENTRADA>"   					{BEGIN(INITIAL);}

<HORA_IN>[0-9]{2}\:[0-9]{2}					{op.time_in = yytext;}
<HORA_IN>"</HORA_ENTRADA>"					{BEGIN(INITIAL);}

<HORA_OUT>[0-9]{2}\:[0-9]{2}         			  	{op.time_out = yytext;}
<HORA_OUT>"</HORA_SAIDA>"              				{BEGIN(INITIAL);}


<ENTRADA>[a-zA-Z][a-zA-Z" "\-]+ 	 					{origem= yytext;op.in = origem;}
<ENTRADA>"</ENTRADA>"   					{BEGIN(INITIAL);}

<SAIDA>\n							{;}
<SAIDA>[a-zA-Z][a-zA-Z" "\-]+						{destino = yytext; if(origem == "\0"){origem = yytext;};
					 						if(trajeto[origem][destino] != '\0'){
												trajeto[origem][destino]+=1;}
					   						else{
												trajeto[origem][destino] = 1;}
				 				; origem = "\0"; op.out = destino;}
<SAIDA>"</SAIDA>"						{ BEGIN(INITIAL);}

<ACCAO>{Decimal}        					{
                       						 for(i=0;i<yyleng - 1;i++){
                              						  if (yytext[i] == ','){
                                      						  yytext[i]='.';}
                                      				 };
                        					 conta = atof(yytext);op.cost = conta; }

<ACCAO>"</IMPORTANCIA>"						 {BEGIN(INITIAL);}
<ACCAO>.|\n            						 { ; }


<TIPO>"Portagens"                      				 {op.tipe = yytext; port += conta;}
<TIPO>"Parques de estacionamento"      				 {op.tipe = yytext; parque += conta;}
<TIPO>"</TIPO>"                        				 { meses[j].push_back(op);  mes.erase(); BEGIN(INITIAL);}



%%

int yywrap()
{return(1);}

int main(int argc,char *argv[]){
	yylex();
	make_dot(trajeto);
	system("dot -Tpng graph.dot -o grafo.png");
	make_html(meses,port,parque);
	return 0;
}





