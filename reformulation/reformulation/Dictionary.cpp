#include "Dictionary.h"
#include <fstream>


Dictionary::Dictionary(void)
{
}


Dictionary::~Dictionary(void)
{
}


bool Dictionary::save(string file)
{
	ofstream os(file);
	if(os.fail())
	{
		cout<<"Could not save dictionary, file not openable"<<endl;
		return false;
	}
	for (std::map<string,Request>::iterator it=content.begin(); it!=content.end(); ++it)
	{
		os << it->first << " " << it->second << endl;
	}
	cout<<"Dictionary saved"<<endl;
	return true;
}
	
bool Dictionary::load(string file)
{
	ifstream is(file);
	if(is.fail())
	{
		cout<<"Could not load dictionary, file not openable"<<endl;
		return false;
	}
	content.clear();
	string s;
	Request req;
	int i;
	while(is>>s>>req)
	{
		i++;
		content[s]=req;
	}
	cout<<"Dictionary loaded: "<<i<<" entries found"<<endl;
	 return true;
}