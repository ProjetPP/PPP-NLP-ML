#include "SemanticNorm.h"
#include <fstream>
#include <algorithm>
#include <iostream>


void SemanticNorm::load(string f)
{
  d.clear();
  ifstream is(f);
  string s1,s2;
  while(is>>s1>>s2)
  {
    d.push_back(s1);
  }
  std::sort(d.begin(),d.end());
  unsigned int i,t;
  t=d.size();
  for(i=1;i<t;i++)
  {
    if(d[i]==d[i-1])
      cout<<d[i]<<endl;
  }
}
