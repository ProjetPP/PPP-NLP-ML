#include "Transformator.h"
#include <exception>
#include <regex>

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
  realword=dico->findnearestPredicate(req);
  this->data=(*dico)[realword];
  string supposedsubject=dico->findnearestSubject(req);
  Request subjectFound=(*dico)[supposedsubject];
  string supposedobject=dico->findnearestObject(req);
  Request objectFound=(*dico)[supposedobject];
  
  if(subjectFound.getDistance2subject(req)>delta)
    subject=new RequestTree(req.getSubject(),func,dico,delta*NOTINFINITERECONSTRUCTIONFACTOR);
  else
  {
    subject=new RequestTree(Type::SUBJECT,subjectFound);
    subject->realword=supposedsubject;
  }
  
  if(objectFound.getDistance2object(req)>delta)
    object=new RequestTree(req.getObject(),func,dico,delta*NOTINFINITERECONSTRUCTIONFACTOR);
  else
  {
    object=new RequestTree(Type::SUBJECT,objectFound);
    object->realword=supposedobject;
  }
    
}

word RequestTree::compact(Functions* func)
{
  if(mytype==Type::SUBJECT)return data.getSubject();
  if(mytype==Type::OBJECT)return data.getObject();
  return func->compact(Request(this->subject->compact(func),this->data.getPredicate(),this->object->compact(func)));
}


string RequestTree::stringify(Dictionary* dico)
{
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
  //TODO check req is valid?
  string prepare;
  unsigned int t=req.size();
  string ent;
  for(unsigned int i=0;i<t;i++)
  {
    switch(req[i])
    {
      case '(':
      case ',':
      case ')':
	prepare+=req[i];
	break;
      default:
	ent=req[i];
	while((req[i+1]!=',')||(req[i+1]!=')'))
	{
	  i++;
	  ent+=req[i];
	}
	prepare+=this->wordToTagOrWord(ent);
    }
  }
  //TODO build request
  //TODO call reformulation
}


string Transformator::stringify(RequestTree rt)
{
  string prefinal=rt.stringify(this->dico);
  string final;
  unsigned int t=prefinal.size();
  for(unsigned int i=0;i<t;i++)
  {
    if(prefinal[i]=='#')
    {
      string tag;
      while((prefinal[i+1]!=',')||(prefinal[i+1]!=')'))
      {
	i++;
	tag+=prefinal[i];
      }
      final+=this->tagToWord(tag);
      this->tags[tag];
    }
    else final+=prefinal[i];
  }
}

string Transformator::wordToTagOrWord(string entity)
{
  if(entity=="?")return "#UNKOWN1";
  for(unsigned short loop=0;loop < entity.size();loop++)
    entity[loop]=tolower(entity[loop]);
  if(dico->isInDictionary(entity))return entity;
  regex isNumber("\\d*(\\.(\\d)*)?");
  if(regex_match(entity,isNumber))
  {
    if(tags["VALUE1"]==""||tags["VALUE1"]==entity)
    {
      tags["VALUE1"]=entity;
      return "#VALUE1";
    }
    if(tags["VALUE2"]==""||tags["VALUE2"]==entity)
    {
      tags["VALUE2"]=entity;
      return "#VALUE2";
    }
    tags["VALUE3"]=entity;
    return "#VALUE3";
  }
  if(tags["NAME1"]==""||tags["NAME1"]==entity)
    {
      tags["NAME1"]=entity;
      return "#NAME1";
    }
    if(tags["NAME2"]==""||tags["NAME2"]==entity)
    {
      tags["NAME2"]=entity;
      return "#NAME2";
    }
    tags["NAME3"]=entity;
    return "#NAME3";
}

string Transformator::tagToWord(string tag)
{
  if(tags[tag]!="")return tags[tag];
  if(tag.find("UNKOWN")!=string::npos)return "?";
  if(tag.find("NAME")!=string::npos)return "NAME";
  if(tag.find("VALUE")!=string::npos)return "VALUE";
}
