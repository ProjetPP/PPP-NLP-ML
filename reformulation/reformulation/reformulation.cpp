// reformulation.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"

using namespace std;





int main(int argc, char* argv[])
{
	Dictionary dico;
	dico.initializeFromClex("clex_lexicon.pl");
	//system("pause");
	return 0;
}

