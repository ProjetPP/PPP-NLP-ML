#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include "definitions.h"
#include <limits>


Dictionary::Dictionary(void) :
content(map<string,Request>())
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

Request Dictionary::operator[](string entry)
{
  return content[entry];
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
  int i=0;
  while(is>>s>>req)
  {
    i++;
    content[s]=req;
  }
  cout<<"Dictionary loaded: "<<i<<" entries found"<<endl;
   return true;
}

bool Dictionary::initializeFromClex(string clexfile)
{
  content.clear();
  ifstream is(clexfile);
  if(is.fail())
  {
    cout<<"clex file "<<clexfile<<" could not be opened"<<endl;
  }
  char buffer[128];
  while(is.getline(buffer,127))
  {
    parseClexLine(buffer);
  }
  content["UNKOWN1"]=Request();
  content["UNKOWN2"]=Request();
  content["NAME1"]=Request();
  content["NAME2"]=Request();
  content["NAME3"]=Request();
  content["VALUE1"]=Request();
  content["VALUE2"]=Request();
  content["VALUE3"]=Request();

  return true;
}

void Dictionary::addWord(char* line)
{
  if(line[1]=='\'')
    addQuotedWord(line);
  else addNoQuotedWord(line);
}

void Dictionary::addQuotedWord(char* line)
{
  line++;
  line++;
  string word;
  while(line[0]!='\'')
  {
    word+=line[0];
    line++;
  }
  content[word]=Request();
}

void Dictionary::addNoQuotedWord(char* line)
{
  line++;
  string word;
  while(line[0]!=',')
  {
    word+=line[0];
    line++;
  }
  content[word]=Request();
}


void Dictionary::parseClexLine(char* line)
{
  if(line[0]==0)return;//line empty
  if(line[0]=='%')return;//commentary
  string nature;
  while(line[0]!='(')
  {
    nature+=line[0];
    line++;
  }
  if(nature=="pn_sg"||nature=="pn_pl"||nature=="pndef_sg"||nature=="pndef_pl")
    return;//propers names are unsed in dictionary
  addWord(line);
}


string Dictionary::findnearestObject(Request req)
{
  float dmin=numeric_limits<float>::infinity();
  float d;
  string res;
  for (std::map<string,Request>::iterator it=content.begin(); it!=content.end(); ++it)
  {
    d=it->second.getTransformedDistanceObject(req,dmin);
    if(d<dmin)
    {
      dmin=d;
      res=it->first;
    }
  }
  return res;
}

string Dictionary::findnearestPredicate(Request req)
{
float dmin=numeric_limits<float>::infinity();
  float d;
  string res;
  for (std::map<string,Request>::iterator it=content.begin(); it!=content.end(); ++it)
  {
    d=it->second.getTransformedDistancePredicate(req,dmin);
    if(d<dmin)
    {
      dmin=d;
      res=it->first;
    }
  }
  return res;
}

string Dictionary::findnearestSubject(Request req)
{
float dmin=numeric_limits<float>::infinity();
  float d;
  string res;
  for (std::map<string,Request>::iterator it=content.begin(); it!=content.end(); ++it)
  {
    d=it->second.getTransformedDistanceSubject(req,dmin);
    if(d<dmin)
    {
      dmin=d;
      res=it->first;
    }
  }
  return res;
}
