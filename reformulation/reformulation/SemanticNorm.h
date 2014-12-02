#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <string>
#include <vector>
#include <map>

using namespace std;


class SemanticNorm
{
public:
  void load(string );
  unsigned int distance(string entity1,string entity2);
private:
  map<string,vector<string> > parent;
  vector< vector<string> > createpartree(string id);
};


#endif