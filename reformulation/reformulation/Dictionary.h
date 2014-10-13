#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "Request.h"
#include <string>
#include <vector>
#include <map>

using namespace std;


class Dictionary
{
public:
	Dictionary(void);
	~Dictionary(void);
	//You can save and load the dictionnary
	//- important because you need to save learned request
	bool save(string file);
	bool load(string file);
	//First time you need to build the dictionnary 
	// - using CLEX see : https://github.com/Attempto/Clex/blob/master/clex_lexicon.pl
	void initializeFromClex(string clexfile);
	//Basic operation - function names are explicit
	//TODO : Choose norm 1 or 2 -> norm 2 ?
	Request operator[](string entry);
	string findnearestSubject(Request req);
	string findnearestObject(Request req);
	string findnearestPredicate(Request req);
private:
	map<string,Request> content;
};

#endif