// reformulation.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;




void solve(ifstream& is)
{
	char buffer[128];
	while(is.getline(buffer,127))
	{
		//deux(buffer);
	}
}

int main(int argc, char* argv[])
{
	ifstream is("clex_lexicon.pl");
	//ofstream os("stats.txt");
	//list_nature(is,os);
	solve(is);
	/*for(int i=0;i<50000;i++)
	{
		char buffer[128];
		is.getline(buffer,127);
	}
	for(int i=0;i<100;i++)
	{
		char buffer[128];
		is.getline(buffer,127);
		cout<<buffer<<endl;
	}*/
	//system("pause");
	return 0;
}

