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
  bool initializeFromClex(string clexfile);
  //Basic operation - function names are explicit
  Request operator[](string entry);
  string findnearestSubject(Request req);
  string findnearestObject(Request req);
  string findnearestPredicate(Request req);
  bool isInDictionary(string entry);
  void translateWord(string entry,Request d);
private:
  void parseClexLine(char* line);
  void addQuotedWord(char* line);
  void addNoQuotedWord(char* line);
  void addWord(char* line);
  map<string,Request> content;
};

#endif