// reformulation.cpp : definit le point d'entrée pour l'application console.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"
#include "Functions.h"
#include <pthread.h>
#include <ctime>


using namespace std;





int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
	Dictionary dico;
	dico.initializeFromClex("clex_lexicon.pl");
	//dico.save("dictionnary.txt");
	//dico.load("dictionnary.txt");
	Functions functions;
	//functions.load("functions.txt");
	 clock_t begin = clock();
	for(int i=0;i<10000;i++)
	{
	Request r1(0),r2(0);
	r1=dico["monkey"];
	r2=dico["lives"];
	
	Request r3=functions.merge(r1,r2);
	}
	clock_t end = clock();
	cout<<difftime(end,begin)<<endl;
	
	pthread_exit(0);
	return 0;
}

