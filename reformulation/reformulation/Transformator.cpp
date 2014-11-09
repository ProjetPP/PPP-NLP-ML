#include "Transformator.h"
#include <exception>

SimplifiedRequestTree::SimplifiedRequestTree(SimplifiedRequestTree::Type type,SimplifiedRequestTree* subjectReq, SimplifiedRequestTree* objectReq):
mytype(type),subject(subjectReq),object(objectReq)
{
  if(type!=Type::PREDICATE)
    throw std::exception();//bad constructor
}

SimplifiedRequestTree::SimplifiedRequestTree(SimplifiedRequestTree::Type type)
{
  mytype=type;
  if(type==Type::PREDICATE)
    throw std::exception();//bad constructor
  
}

SimplifiedRequestTree::~SimplifiedRequestTree()
{
  if(mytype==Type::PREDICATE)
  {
    delete subject;
    delete object;
  }
}


RequestTree::RequestTree(RequestTree::Type type, Request data):
mytype(type),data(data),realword("")
{
  if(type==Type::PREDICATE)
    throw std::exception();//bad constructor
  
}

RequestTree::RequestTree(RequestTree::Type type, Request predicate, RequestTree* subjectReq, RequestTree* objectReq):
mytype(type),data(predicate),subject(subjectReq),object(objectReq),realword("")
{
  if(type!=Type::PREDICATE)
    throw std::exception();//bad constructor
}

RequestTree::~RequestTree()
{
  if(this->mytype==Type::PREDICATE)
  {
    delete subject;
    delete object;
  }
}

RequestTree::RequestTree(word data,Functions* func,Dictionary* dico,float delta):
realword("")
{
  mytype=Type::PREDICATE;
  Request req=func->uncompact(data);
  this->data=(*dico)[dico->findnearestPredicate(req)];
  Request subjectFound=(*dico)[dico->findnearestSubject(req)];
  Request objectFound=(*dico)[dico->findnearestObject(req)];
  
  if(subjectFound.getDistance2subject(req)>delta)
    subject=new RequestTree(req.getSubject(),func,dico,delta*NOTINFINITERECONSTRUCTIONFACTOR);
  else
    subject=new RequestTree(Type::SUBJECT,subjectFound);
  
  if(objectFound.getDistance2object(req)>delta)
    object=new RequestTree(req.getObject(),func,dico,delta*NOTINFINITERECONSTRUCTIONFACTOR);
  else
    object=new RequestTree(Type::SUBJECT,objectFound);
    
}

word RequestTree::compact(Functions* func)
{
  if(mytype==Type::SUBJECT)return data.getSubject();
  if(mytype==Type::OBJECT)return data.getObject();
  return func->compact(Request(this->subject->compact(func),this->data.getPredicate(),this->object->compact(func)));
}


string RequestTree::stringify(Dictionary* dico)
{
  //TODO Add extra string to save real word/
  string res;
  switch(this->mytype)
  {
    case Type::PREDICATE:
      res="(";
      res+=subject->stringify(dico);
      res+=",";
      if(realword!="")res+=realword;
      else
	res+=dico->findnearestPredicate(this->data);
      res+=",";
      res+=object->stringify(dico);
      res+=")";
      return res;
    case Type::OBJECT:
      if(realword!="")return realword;
      return dico->findnearestObject(this->data);
    case Type::SUBJECT:
      if(realword!="")return realword;
      return dico->findnearestSubject(this->data);
  }
}

SimplifiedRequestTree* RequestTree::getSimplifiedRequestTree()
{
  if(mytype==Type::OBJECT)return new SimplifiedRequestTree(SimplifiedRequestTree::OBJECT);
  if(mytype==Type::SUBJECT)return new SimplifiedRequestTree(SimplifiedRequestTree::SUBJECT);
  return new SimplifiedRequestTree(SimplifiedRequestTree::PREDICATE,subject->getSimplifiedRequestTree(),object->getSimplifiedRequestTree());
}


Transformator::Transformator(Functions* functions, Dictionary* dictionary,float precision):
func(functions),dico(dictionary),delta(precision)
{
}

string Transformator::reformulation(RequestTree rt)
{
    word cmp =rt.compact(this->func);
    RequestTree result(cmp,this->func,this->dico,this->delta);
    return this->stringify(result);
}

string Transformator::reformulation(string req)
{
  //parse and add tags (save tag)
  //build request
  //call reformulation
}


string Transformator::stringify(RequestTree rt)
{
  string prefinal=rt.stringify(this->dico);
  unsigned int t=prefinal.size();
  for(unsigned int i=0;i<t;i++)
  {
    if(prefinal[i]=='#')
    {
      string tag;
      unsigned int j=i;
      j++;
      while((prefinal[j]!=',')||(prefinal[j]!=')'))
      {
	tag+=prefinal[j];
	j++;
      }
    //replace tag here  
    }
  }
  //parse and remove tags
}

