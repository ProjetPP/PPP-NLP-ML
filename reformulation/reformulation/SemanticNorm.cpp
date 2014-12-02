#include "SemanticNorm.h"
#include "definitions.h"
#include <fstream>
#include <algorithm>
#include <iostream>


void SemanticNorm::load(string f)
{
  parent.clear();
  ifstream is(f);
  string s1,s2;
  while(is>>s1>>s2)
  {
    parent[s1].push_back(s2);
  }
}

vector< vector< string > > SemanticNorm::createpartree(string id)
{
  vector< vector<string> > branch;
  branch.push_back(parent[id]);
  int i =0;
  while(i<100)
  {
    branch.push_back(vector<string>());
    if(branch[i].size()==0)
    {
      branch.pop_back();
      break;
    }
    for(unsigned int j=0;j<branch[i].size();j++)
    {
      for(unsigned int z=0;z<parent[branch[i][j]].size();z++)
      branch[i+1].push_back(parent[branch[i][j]][z]);
    }
    i++;
  }
  return branch;
}


unsigned int findin(vector< vector< string > > & branch,string s)
{
  unsigned int i,t;
  t=branch.size();
  for(i=0;i<t;i++)
  {
    if(find(branch[i].begin(),branch[i].end(),s)!=branch[i].end())
      return i+1;
  }
  return static_cast<unsigned int>( MAXINSTANCEOFDEEP );
}

unsigned int SemanticNorm::distance(string entity1, string entity2)
{
 // MAXINSTANCEOFDEEP 
  if(entity1==entity2)return 0;
  vector< vector< string > > branch1=createpartree(entity1);
  vector< vector< string > > branch2=createpartree(entity2);
  unsigned int i,t,z;
  
  t=branch2.size();
  if(t==0) return 2*static_cast<unsigned int>( MAXINSTANCEOFDEEP );
  
  for(i=0;i<t;i++)
  {
    for(unsigned int j=0;j<branch2[i].size();j++)
    {
      z=findin(branch1,branch2[i][j]);
      if(z<static_cast<unsigned int>( MAXINSTANCEOFDEEP ))
	return z+i;
    }
  }
  
  return 2*static_cast<unsigned int>( MAXINSTANCEOFDEEP );
}
