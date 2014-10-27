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
mytype(type),data(data)
{
  if(type==Type::PREDICATE)
    throw std::exception();//bad constructor
  
}

RequestTree::RequestTree(RequestTree::Type type, Request predicate, RequestTree* subjectReq, RequestTree* objectReq):
mytype(type),data(predicate),subject(subjectReq),object(objectReq)
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

RequestTree::RequestTree(word data,Functions* func,Dictionary* dico,float delta)
{
  mytype=Type::PREDICATE;
  Request req=func->uncompact(data);
  this->data=(*dico)[dico->findnearestPredicate(req)];
  Request subjectFound=(*dico)[dico->findnearestSubject(req)];
  Request objectFound=(*dico)[dico->findnearestObject(req)];
  
  if(subjectFound.getDistance2subject(req)>delta)
    subject=new RequestTree(req.getSubject(),func,dico,delta);
  else
    subject=new RequestTree(Type::SUBJECT,subjectFound);
  
  if(objectFound.getDistance2object(req)>delta)
    object=new RequestTree(req.getObject(),func,dico,delta);
  else
    object=new RequestTree(Type::SUBJECT,objectFound);
    
}

word RequestTree::compact(Functions* func)
{
  if(mytype==Type::SUBJECT)return data.getSubject();
  if(mytype==Type::OBJECT)return data.getObject();
  return func->compact(Request(this->subject->compact(func),this->data.getPredicate(),this->object->compact(func)));
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

void Transformator::reformulation(RequestTree rt)
{
  
}
