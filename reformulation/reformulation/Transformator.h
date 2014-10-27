#ifndef TRANSFORMATOR_H
#define TRANSFORMATOR_H
#include "Request.h"
#include "Dictionary.h"
#include "Functions.h"
#include <limits>

class SimplifiedRequestTree
{
  public:
  enum Type{SUBJECT,OBJECT,PREDICATE};
  SimplifiedRequestTree(SimplifiedRequestTree::Type type);
  SimplifiedRequestTree(SimplifiedRequestTree::Type type,SimplifiedRequestTree* subjectReq,SimplifiedRequestTree* objectReq);
  ~SimplifiedRequestTree();
  
private:
  Type mytype;
  SimplifiedRequestTree* subject;
  SimplifiedRequestTree* object;
};

class RequestTree
{
public:
  enum Type{SUBJECT,OBJECT,PREDICATE};
  RequestTree(RequestTree::Type, Request data);
  RequestTree(RequestTree::Type, Request predicate,RequestTree* subjectReq,RequestTree * objectReq);
  RequestTree(word data,Functions* func,Dictionary* dico,float delta);
  ~RequestTree();
  
  word compact(Functions* func);
  SimplifiedRequestTree* getSimplifiedRequestTree();
private:
  Type mytype;
  Request data;
  RequestTree* subject;
  RequestTree* object;
};

class Transformator
{
public:
  Transformator(Functions* functions, Dictionary* dictionary, float precision=numeric_limits<float>::infinity());
  
  void reformulation(RequestTree rt);
  
private:
  Functions* func;
  Dictionary* dico;
  float delta;
};

#endif