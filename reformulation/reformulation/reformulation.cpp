// reformulation.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"

using namespace std;





int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;
	Dictionary dico;
	//dico.initializeFromClex("clex_lexicon.pl");
	//dico.save("dictionnary.txt");
	dico.load("dictionnary.txt");
	//system("pause");
	return 0;
}

